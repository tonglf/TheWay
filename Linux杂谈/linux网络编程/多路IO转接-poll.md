# 多路 IO 转接 - poll

## 优缺点

**优点：**

- 自带数组结构。 可以将 **监听事件集合** 和 **返回事件集合** 分离。
- 拓展 监听上限。 超出 1024 限制。

**缺点：**

- 不能跨平台。 Linux
- 无法直接定位满足监听事件的文件描述符， 编码难度较大。

## 代码实现

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>

#define MAXLINE 80
#define SERV_PORT 6666
#define OPEN_MAX 1024

int main(int argc, char *argv[])
{
	int i, j, maxi, listenfd, connfd, sockfd;
	int nready;
	ssize_t n;
	char buf[MAXLINE], str[INET_ADDRSTRLEN];
	socklen_t clilen;
	struct pollfd client[OPEN_MAX];
	struct sockaddr_in cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, 20);

	client[0].fd = listenfd;
	client[0].events = POLLRDNORM; 					// listenfd 监听普通读事件

	for (i = 1; i < OPEN_MAX; i++)
		client[i].fd = -1; 							// 用 -1 初始化 client[] 里剩下元素 
	maxi = 0; 										// client[] 数组有效元素中最大元素下标 

	while (1) 
    {
		nready = poll(client, maxi + 1, -1); 		// 阻塞 
		if (client[0].revents & POLLRDNORM) 		// 有客户端链接请求 
        { 		
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
            
			printf("received from %s at PORT %d\n",
					inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
					ntohs(cliaddr.sin_port));
            
			for (i = 1; i < OPEN_MAX; i++) 
            {
				if (client[i].fd < 0) 
                {
					client[i].fd = connfd; 	// 找到 client[] 中空闲的位置，存放 accept 返回的 connfd
					break;
				}
			}

			if (i == OPEN_MAX)
				perr_exit("too many clients");

			client[i].events = POLLRDNORM; 		// 设置刚刚返回的 connfd，监控读事件
			if (i > maxi)
				maxi = i; 						// 更新 client[] 中最大元素下标 
			if (--nready <= 0)
				continue; 						// 没有更多就绪事件时,继续回到 poll 阻塞 
		}
		for (i = 1; i <= maxi; i++) 			// 检测 client[]
        { 			
			if ((sockfd = client[i].fd) < 0)
				continue;
			if (client[i].revents & (POLLRDNORM | POLLERR)) 
            {
				if ((n = Read(sockfd, buf, MAXLINE)) < 0) 
                {
					if (errno == ECONNRESET) 	// 当收到 RST标志时 
                    { 
						// connection reset by client 
						printf("client[%d] aborted connection\n", i);
						close(sockfd);
						client[i].fd = -1;
					} 
                    else 
                    {
						perr_exit("read error");
					}
				} 
                else if (n == 0) 
                {
					// connection closed by client 
					printf("client[%d] closed connection\n", i);
					close(sockfd);
					client[i].fd = -1;
				} 
                else 
                {
					for (j = 0; j < n; j++)
						buf[j] = toupper(buf[j]);
                    writen(sockfd, buf, n);
				}
				if (--nready <= 0)
					break; 				// no more readable descriptors 
			}
		}
	}
	return 0;
}
```

## 函数原型

```cpp
	int poll(struct pollfd *fds, nfds_t nfds, int timeout);

		fds：监听的文件描述符【数组】

			struct pollfd 
            {				
				int fd：	待监听的文件描述符				
				short events：	待监听的文件描述符对应的监听事件
								取值：POLLIN、POLLOUT、POLLERR
				short revnets：	传入时， 给0。如果满足对应事件的话， 返回 非0 --> POLLIN、POLLOUT、POLLERR
			}

		nfds: 监听数组的，实际有效监听个数。

		timeout:  
				> 0:  	超时时长。单位：毫秒。
			  	-1 :	阻塞等待
			  	0  ：   不阻塞

		返回值：返回满足对应监听事件的文件描述符总个数。
```

## 对比 select ：

select 采用 1024 大小的 bitmap，而 poll 采用的是数组，每个数组存入的类型为 struct pollfd，pollfd 内部包含 fd（待监听的文件描述符）、events（待监听事件类型）、revnets（若有事件发生，则由 0 变为具体事件类型，例如：POLLIN，类似于 fd_set 中的置位)。

> **select 缺点如下：**

- **1024 bitmap，监听上限受文件描述符限制**
- **fd_set 不可重用**
- **不知道哪个文件描述符有事件发生，需要每次循环遍历 fd_set，时间复杂度 O(n)**
- **不断地将 fd_set 从用户态复制到内核态，再由内核态复制到用户态，当 fd_set 比较大时，开销大**

> **相对于 select，poll 做了如下改进：**

- **不再使用 bitmap，而是传递链表，链表的大小可以很大，所以不再受到 1024 文件描述符的限制；**

- **当事件发生时，select 需要内核将 fd_set 置位，所以 fd_set 不可重用，而 poll 传递的链表存储的类型为 pollfd，内核只需将 pollfd 中的 revnets 更改即可，检查有事件发生时，只需检查 revnets 是否不为 0 即可，在进行完该描述符的操作时，再将 revnets 置 0 ；**

- **因为 poll 传递的是链表，在检查哪个描述符发生事件时，依然需要循环链表进行遍历，事件复杂度高；**
- **与 select 一样，同样需要将链表在用户态与内核态不断复制，开销大。**

**综上，poll 相对于 select 改进了前两个缺点，但最为致命的后两个缺点依然没有改进。**

