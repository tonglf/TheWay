# 多路IO转接-select

select 原理：  借助内核， select 来监听， 客户端连接、数据通信事件。

**select优缺点：**

**优点：**

- 跨平台
- 内核监听 fd，并将 fd_set 置位，速度快

**缺点：**

- **1024 bitmap，监听上限受文件描述符限制**
- **fd_set 不可重用**
- **不知道哪个文件描述符有事件发生，需要每次循环遍历 fd_set，时间复杂度 O(n)**
- **不断地将 fd_set 从用户态复制到内核态，再由内核态复制到用户态，当 fd_set 比较大时，开销大**

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

#define SERV_PORT 6666

int main(int argc, char *argv[])
{
    int i, j, n, nready;

    int maxfd = 0;

    int listenfd, connfd;

    char buf[BUFSIZ];         /* #define INET_ADDRSTRLEN 16 */

    struct sockaddr_in clie_addr, serv_addr;
    socklen_t clie_addr_len;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);  
    
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    bzero(&serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family= AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port= htons(SERV_PORT);
    
    bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    listen(listenfd, 128);
    
    fd_set rset, allset;                            // rset 读事件文件描述符集合 allset 用来暂存 

    maxfd = listenfd;

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);                                  // 构造select监控文件描述符集 

    while (1) 
    {   
        rset = allset;                                          // 每次循环时都从新设置 select 监控信号集 
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);	// rset 从用户态复制到内核态，监听读事件后，再从内核态复制回用户态
        if (nready < 0)											// 此时， rset 都是有事件发生的 fd，与 allset 不同了
            perr_exit("select error");

        if (FD_ISSET(listenfd, &rset))                          // 说明有新的客户端链接请求 
		{
            clie_addr_len = sizeof(clie_addr);
            connfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);// Accept 不会阻塞 

            FD_SET(connfd, &allset);                 // 向监控文件描述符集合 allset 添加新的文件描述符 connfd 

            if (maxfd < connfd)
                maxfd = connfd;

            if (0 == --nready)                                // 只有 listenfd 有事件, 后续的 for 不需执行 
                continue;
        } 

        for (i = listenfd + 1; i <= maxfd; i++)                // 检测哪个 clients 有数据就绪 
		{
            if (FD_ISSET(i, &rset)) 
            {
                if ((n = read(i, buf, sizeof(buf))) == 0))     // 当client关闭链接时,服务器端也关闭对应链接 
				{
                    close(i);
                    FD_CLR(i, &allset);                        // 解除select对此文件描述符的监控 
                } 
                else if (n > 0) 
                {
                    for (j = 0; j < n; j++)
                    {
                        buf[j] = toupper(buf[j]);
                    }   
                    write(i, buf, n);
                }
            }
        }
    }
    close(listenfd);

    return 0;
}
```

## 函数原型

**文件描述符数组**

**FD_ZERO**

```cpp
void FD_ZERO(fd_set *set);	--- 清空一个文件描述符集合。

	fd_set rset;

	FD_ZERO(&rset);
```

**FD_SET**


```cpp
void FD_SET(int fd, fd_set *set);	--- 将待监听的文件描述符，添加到监听集合中

	FD_SET(3, &rset);	FD_SET(5, &rset);	FD_SET(6, &rset);
```

**FD_CLR**

```cpp
void FD_CLR(int fd, fd_set *set);	--- 将一个文件描述符从监听集合中 移除。

	FD_CLR（4， &rset）;
```

**FD_ISSET**

```cpp
int  FD_ISSET(int fd, fd_set *set);	--- 判断一个文件描述符是否在监听集合中。

	返回值： 在：1；不在：0；

	FD_ISSET（4， &rset）;
```

**select**

```cpp
int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);

	nfds：监听的所有文件描述符中，最大文件描述符 + 1

	readfds：  读 文件描述符监听集合。	传入、传出参数

	writefds： 写 文件描述符监听集合。	传入、传出参数		NULL

	exceptfds：异常 文件描述符监听集合	传入、传出参数		NULL

	timeout： 	> 0: 	设置监听超时时长。

				NULL:	阻塞监听

				0：	非阻塞监听，轮询
	返回值：

		> 0:	所有监听集合（3个）中， 满足对应事件的总数。

		0：	没有满足监听条件的文件描述符

		-1： 	errno
```

