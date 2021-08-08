# epoll事件模型LT、ET

EPOLL 事件有两种模型：

Edge Triggered (ET) **边缘触发**==只有数据到来才触发，不管缓存区中是否还有数据。==

Level Triggered (LT) **水平触发**==只要有数据都会触发。==

思考如下步骤：

1. 假定我们已经把一个用来从管道中读取数据的文件描述符(RFD)添加到 epoll 描述符。

2. 管道的另一端写入了 2 KB 的数据

3. 调用 epoll_wait，并且它会返回 RFD，说明它已经准备好读取操作

4. 读取 1KB 的数据

5. 调用 epoll_wait……

在这个过程中，有两种工作模式：

## ET模式

ET 模式即 Edge Triggered 工作模式。

如果我们在第 1 步将 RFD 添加到 epoll 描述符的时候使用了 EPOLLET 标志，那么在第 5 步调用 epoll_wait 之后将有可能会挂起，因为剩余的数据还存在于文件的输入缓冲区内，而且数据发出端还在等待一个针对已经发出数据的反馈信息。只有在监视的文件句柄上发生了某个事件的时候 ET 工作模式才会汇报事件。因此在第 5 步的时候，调用者可能会放弃等待仍在存在于文件输入缓冲区内的剩余数据。**epoll 工作在 ET 模式的时候，必须使用非阻塞套接口，以避免由于一个文件句柄的阻塞读/阻塞写操作把处理多个文件描述符的任务饿死**。最好以下面的方式调用 ET 模式的 epoll 接口，在后面会介绍避免可能的缺陷。

​	1)    基于非阻塞文件句柄

​	2)    只有当 read 或者 write 返回 EAGAIN (非阻塞读，暂时无数据)时才需要挂起、等待。但这并不是说每次 read 时都需要循环读，直到读到产生一个 EAGAIN 才认为此次事件处理完成，当 read 返回的读到的数据长度小于请求的数据长度时，就可以确定此时缓冲中已没有数据了，也就可以认为此事读事件已处理完成。

## LT模式

LT 模式即 Level Triggered 工作模式。

与 ET 模式不同的是，以 LT 方式调用 epoll 接口的时候，它就相当于一个速度比较快的 poll，无论后面的数据是否被使用。

LT (level triggered)：LT 是缺省的工作方式，并且同时支持 block 和 no-block socket。在这种做法中，内核告诉你一个文件描述符是否就绪了，然后你可以对这个就绪的 fd 进行 IO 操作。如果你不作任何操作，内核还是会继续通知你的，所以，这种模式编程出错误可能性要小一点。传统的 select/poll 都是这种模型的代表。

ET (edge-triggered)：ET 是高速工作方式，只支持 no-block socket。在这种模式下，当描述符从未就绪变为就绪时，内核通过 epoll 告诉你。然后它会假设你知道文件描述符已经就绪，并且不会再为那个文件描述符发送更多的就绪通知。请注意，如果一直不对这个 fd 作 IO 操作(从而导致它再次变成未就绪)，内核不会发送更多的通知 (only once)。

## 实例：基于网络 C/S 非阻塞模型的 epoll ET触发模式

### server：

```cpp
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 10
#define SERV_PORT 8080

int main(void)
{
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int listenfd, connfd;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int i, efd, flag;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, 20);

	struct epoll_event event;
	struct epoll_event resevent[10];
	int res, len;
	efd = epoll_create(10);
	// event.events = EPOLLIN; 
	event.events = EPOLLIN | EPOLLET;		// ET 边沿触发 ，默认是水平触发

	printf("Accepting connections ...\n");
    
	cliaddr_len = sizeof(cliaddr);
	connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
    
	printf("received from %s at PORT %d\n",
			inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
			ntohs(cliaddr.sin_port));

	flag = fcntl(connfd, F_GETFL);		// 设置非阻塞
	flag |= O_NONBLOCK;
	fcntl(connfd, F_SETFL, flag);
    
	event.data.fd = connfd;
	epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &event);

	while (1) {
		printf("epoll_wait begin\n");
		res = epoll_wait(efd, resevent, 10, -1);
		printf("epoll_wait end res %d\n", res);

		if (resevent[0].data.fd == connfd) {
			while ((len = read(connfd, buf, MAXLINE/2)) > 0)
				write(STDOUT_FILENO, buf, len);
		}
	}
	return 0;
}
```

### client

```cpp
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAXLINE 10
#define SERV_PORT 8080

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int sockfd, i;
	char ch = 'a';

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	while (1) {
		for (i = 0; i < MAXLINE/2; i++)
        {
			buf[i] = ch;
        }
		buf[i-1] = '\n';
		ch++;

		for (; i < MAXLINE; i++)
        {
			buf[i] = ch;
        }
		buf[i-1] = '\n';
		ch++;

		write(sockfd, buf, sizeof(buf));
		sleep(10);
	}
	close(sockfd);
	return 0;
}
```

