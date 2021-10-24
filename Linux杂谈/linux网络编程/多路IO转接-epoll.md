# 多路 IO 转接 - epoll

## 简介

epoll 是 Linux 下多路复用 IO 接口 select / poll 的增强版本，**它能显著提高程序在==大量并发连接==中==只有少量活跃==的情况下的系统 CPU 利用率**，因为它会**复用文件描述符集合来传递结果**而不用迫使开发者每次等待事件之前都必须重新准备要被侦听的文件描述符集合，另一点原因就是获取事件的时候，它无须遍历整个被侦听的描述符集，只要遍历那些被内核 IO 事件异步唤醒而加入 Ready 队列的描述符集合就行了。

目前 epoll 是 linux 大规模并发网络程序中的热门首选模型。(**epoll 只能在 Linux 下使用**)

## 代码实现

```cpp
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>

#define MAXLINE 8192
#define SERV_PORT 8000

#define OPEN_MAX 5000

int main(int argc, char *argv[])
{
    int i, listenfd, connfd, sockfd;
    int  n, num = 0;
    ssize_t nready, efd, res;
    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    
    struct sockaddr_in cliaddr, servaddr;
	socklen_t clilen;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));      // 端口复用
    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    
    listen(listenfd, 20);

    efd = epoll_create(OPEN_MAX);               // 创建 epoll 模型, efd 指向红黑树根节点
    if (efd == -1)
        perr_exit("epoll_create error");

    struct epoll_event tep, ep[OPEN_MAX];       // tep: epoll_ctl 参数  ep[] : epoll_wait 参数

    tep.events = EPOLLIN; 
    tep.data.fd = listenfd;           // 指定 lfd 的监听时间为"读"

    res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);  // 将 lfd 及对应的结构体设置到树上, efd 可找到该树
    if (res == -1)
        perr_exit("epoll_ctl error");

    while (1) 
    {
        // epoll 为 server 阻塞监听事件, ep 为 struct epoll_event 类型数组, OPEN_MAX 为数组容量, -1表永久阻塞
        nready = epoll_wait(efd, ep, OPEN_MAX, -1); 
        if (nready == -1)
            perr_exit("epoll_wait error");

        for (i = 0; i < nready; i++) 
        {
            if (!(ep[i].events & EPOLLIN))      // 如果不是"读"事件, 继续循环
                continue;

            if (ep[i].data.fd == listenfd) 		// 判断满足事件的 fd 是不是 lfd   
            {             
                clilen = sizeof(cliaddr);
                connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);    // 接受链接

                printf("received from %s at PORT %d\n", 
                        inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), 
                        ntohs(cliaddr.sin_port));
                printf("cfd %d---client %d\n", connfd, ++num);

                tep.events = EPOLLIN; 
                tep.data.fd = connfd;
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);      // 加入红黑树
                if (res == -1)
                    perr_exit("epoll_ctl error");
            } 
            else 								 // 不是 lfd, 
            {                                                  
                sockfd = ep[i].data.fd;
                n = read(sockfd, buf, MAXLINE);

                if (n == 0) 					// 读到 0,说明客户端关闭链接
                {                                           
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);  // 将该文件描述符从红黑树摘除
                    if (res == -1)
                        perr_exit("epoll_ctl error");
                    close(sockfd);                                      // 关闭与该客户端的链接
                    printf("client[%d] closed connection\n", sockfd);

                } 
                else if (n < 0) 				// 出错
                {                                     
                    perror("read n < 0 error: ");
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);  // 摘除节点
                    close(sockfd);
                } 
                else 							// 实际读到了字节数
                {                                                
                    for (i = 0; i < n; i++)
                    {
                        buf[i] = toupper(buf[i]);                       //转大写,写回给客户端
                    }
                    write(STDOUT_FILENO, buf, n);
                    write(sockfd, buf, n);
                }
            }
        }
    }
    close(listenfd);
    close(efd);

    return 0;
}
```

## 函数原型

```cpp
	int epoll_create(int size);						// 创建一棵监听红黑树

// size：创建的红黑树的监听节点数量。（仅供内核参考。）

// 返回值：
//		成功：指向新创建的红黑树的根节点的 fd。 
//		失败： -1 errno



	int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);	// 操作监听红黑树

	// epfd：epoll_create 函数的返回值。 epfd

	// op：对该监听红黑数所做的操作。

	//		EPOLL_CTL_ADD 添加 fd 到监听红黑树
	//		EPOLL_CTL_MOD 修改 fd 在监听红黑树上的监听事件。
	//		EPOLL_CTL_DEL 将一个 fd 从监听红黑树上摘下（取消监听）

	// fd：
	//		待监听的fd

	// event：	本质 struct epoll_event 结构体 地址
	//		成员 events：
	//				EPOLLIN / EPOLLOUT / EPOLLERR
	//		成员 data： 联合体（共用体）：
	//				int fd;	  对应监听事件的 fd
	//				void *ptr； 
	//				uint32_t u32;
	//				uint64_t u64;		

	// 返回值：
	//		成功 0； 
	// 		失败： -1 errno



	int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout); 	 // 阻塞监听

	// epfd：epoll_create 函数的返回值。 epfd

	// events：传出参数，【数组】， 满足监听条件的哪些 fd 结构体。

	// maxevents：数组元素的总个数。 1024			
	//		struct epoll_event evnets[1024]

	// timeout：
	//		-1: 阻塞
	//		0 ：不阻塞
	//		>0: 超时时间（毫秒）

	// 返回值：
	//		>0: 满足监听的总个数。 可以用作循环上限。
	//		0 ： 没有 fd 满足监听事件
	//		-1：	失败。 errno
```



