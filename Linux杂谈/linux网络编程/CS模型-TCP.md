# C/S模型-TCP

## socket 模型创建流程图

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210627195835232.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTg2NzM4Mg==,size_16,color_FFFFFF,t_70)

## 服务器端与客户端代码编写

**TCP通信流程分析:**

  **server:**
​    1. socket()  创建 socket
​    2. bind() 绑定服务器地址结构
​    3. listen()  设置监听上限 
​    4. accept()  阻塞监听客户端连接
​    5. read(fd)  读 socket 获取客户端数据
​    6. 小--大写  toupper()
​    7. write(fd)
​    8. close(); 

  **client:**
​    1. socket()  创建 socket
​    2. connect(); 与服务器建立连接
​    3. write() 写数据到 socket
​    4. read() 读转换后的数据。
​    5. 显示读取结果
​    6. close()

**服务器端：**

`server.cpp`

```cpp
#include <iostream>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define SERV_PORT 9527

void sys_err(const char *str)		// 错误处理函数
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
{
    int lfd = 0, cfd = 0;
    int ret, i;
    char buf[BUFSIZ], client_IP[1024];

    struct sockaddr_in serv_addr, clit_addr;  // 定义服务器地址结构 和 客户端地址结构
    socklen_t clit_addr_len;				  // 客户端地址结构大小

    serv_addr.sin_family = AF_INET;				// IPv4
    serv_addr.sin_port = htons(SERV_PORT);		// 转为网络字节序的 端口号
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// 获取本机任意有效IP

    lfd = socket(AF_INET, SOCK_STREAM, 0);		//创建一个 socket
    if (lfd == -1) 
    {
        sys_err("socket error");
    }

    // 给服务器socket绑定地址结构（IP+port)
    ret = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret == -1) 
    {
        sys_err("bind error");
    }
    
    ret = listen(lfd, 128);					// 设置监听上限
    if (ret == -1) 
    {
        sys_err("listen error");
    }
    
    clit_addr_len = sizeof(clit_addr);	// 	获取客户端地址结构大小

    cfd = accept(lfd, (struct sockaddr *)&clit_addr, &clit_addr_len);	// 阻塞等待客户端连接请求
    if (cfd == -1)
    {
        sys_err("accept error");
    }        

    // 根据accept传出参数，获取客户端 ip 和 port
    std::cout << "client ip : " 
        << inet_ntop(AF_INET, &clit_addr.sin_addr.s_addr, client_IP, sizeof(client_IP)) 
        << "port : " 
        << ntohs(clit_addr.sin_port) << std::endl;	

    while (1) 
    {
        ret = read(cfd, buf, sizeof(buf));		// 读客户端数据
        write(STDOUT_FILENO, buf, ret);			// 写到屏幕查看

        for (i = 0; i < ret; i++)				// 小写 -- 大写
            buf[i] = toupper(buf[i]);

        write(cfd, buf, ret);					// 将大写，写回给客户端。
    }

    close(lfd);
    close(cfd);

    return 0;
}
```

先测试一下服务器：

在一个终端运行服务器，在另一个终端连接服务器，连接命令：`nc 127.0.0.1 9527`，在用户端写入，服务器端会读入数据然后返回大写字符，用户端返回大写字符。

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021062720212950.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTg2NzM4Mg==,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210627202135207.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTg2NzM4Mg==,size_16,color_FFFFFF,t_70)

**客户端：**

`client.cpp`

```cpp
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define SERV_PORT 9527

void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
    int cfd;
    int conter = 10;
    char buf[BUFSIZ];
    
    struct sockaddr_in serv_addr;          //服务器地址结构

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    //inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd == -1)
    {
        sys_err("socket error");
    }    

    int ret = connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret != 0)
    {
        sys_err("connect err");
    }        

    while (--conter) 
    {
        write(cfd, "hello\n", 6);
        ret = read(cfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret);
        sleep(1);
    }

    close(cfd);

	return 0;
}
```

测试客户端与服务器端的连接：

**服务器端：**

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210627202724844.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTg2NzM4Mg==,size_16,color_FFFFFF,t_70)

**客户端：**

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210627202732662.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTg2NzM4Mg==,size_16,color_FFFFFF,t_70)

## 函数解析

### 网络字节序：

- **小端法**：（pc本地存储）  高位存高地址。低位存低地址。  int a = 0x12345678

- **大端法**：（网络存储） 高位存低地址。低位存高地址。

 ` htonl `--> 本地--》网络 （IP）     192.168.1.11 --> string --> atoi --> int --> htonl --> 网络字节序

 `htons` --> 本地--》网络 (port)

 ` ntohl` --> 网络--》 本地（IP）

 `ntohs` --> 网络--》 本地（Port）

### IP地址转换函数：

```cpp
 int inet_pton(int af, const char *src, void *dst);   // 本地字节序（string IP） ---> 网络字节序
```

- **参数**：

  ​    `af`：AF_INET、AF_INET6

  ​    `src`：传入，IP地址（点分十进制）

  ​    `dst`：传出，转换后的 网络字节序的 IP地址。 

- **返回值**：

  成功： 1

  异常： 0， 说明src指向的不是一个有效的ip地址。

  失败：-1

  ```cpp
  // 网络字节序 ---> 本地字节序（string IP） 
  const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);  
  ```

- **参数**：

  ​    `af`：AF_INET、AF_INET6

  ​    `src`: 网络字节序IP地址

  ​    `dst`：本地字节序（string IP）

  ​    `size`： dst 的大小。

- **返回值**： 

  ​	成功：dst。   

  ​    失败：NULL

### sockaddr地址结构： 

**IP + port --> 在网络环境中唯一标识一个进程**。

```cpp
struct sockaddr_in addr;

addr.sin_family = AF_INET/AF_INET6;      // man 7 ip

addr.sin_port = htons(9527);  

int dst;

inet_pton(AF_INET, "192.157.22.45", (void *)&dst);

addr.sin_addr.s_addr = dst;
// 另一种方式（常用）
addr.sin_addr.s_addr = htonl(INADDR_ANY);   // 【*】 取出系统中有效的任意IP地址。二进制类型。
```

### socket函数：

####  socket

```cpp
#include <sys/socket.h>

int socket(int domain, int type, int protocol);  // 创建一个 套接字
// socket(AF_INET, SOCK_STREAM, 0);
```

-  **参数：**

  ​    `domain`：AF_INET、AF_INET6、AF_UNIX

  ​    `type`：SOCK_STREAM、SOCK_DGRAM	// 数据流（TCP）、数据报（UDP）

  ​    `protocol`: 0 		// 使用协议：SOCK_STREAM 使用 TCP，SOCK_DGRAM 使用 UDP，0 为默认与 type 匹配

- **返回值：**

  ​    成功： 新套接字所对应文件描述符

  ​    失败: -1 errno

####  bind

 ```c++
 #include <arpa/inet.h>
 
 // 给socket绑定一个 地址结构 (IP+port)
 int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 
 // 示例
 struct sockaddr_in addr;
 addr.sin_family = AF_INET;
 addr.sin_port = htons(8888);
 addr.sin_addr.s_addr = htonl(INADDR_ANY);
 bind(fd, (struct sockaddr *)&addr, sizeof(addr)); 
 ```

- **参数：**

​    `sockfd`: socket 函数返回值

​    `addr`: 传入参数(struct sockaddr *)&addr

​    `addrlen`: sizeof(addr) 地址结构的大小。

- **返回值：**

     成功：0

     失败：-1 errno

####  listen

```c++
// 设置同时与服务器建立连接的上限数。（同时进行3次握手的客户端数量）
int listen(int sockfd, int backlog); 
// listen(fd. 5);
```

- **参数：**

  `sockfd`: socket 函数返回值

  `backlog`：上限数值。最大值 128.

- **返回值：**

     成功：0

     失败：-1 errno  

#### accept

 ```cpp
 // 阻塞等待客户端建立连接，成功的话，返回一个与客户端成功连接的socket文件描述符。
 int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); 
 ```

- **参数：**

  `sockfd`: socket 函数返回值

  `addr`：传出参数。成功与服务器建立连接的那个客户端的地址结构（IP+port）

  ​      socklen_t clit_addr_len = sizeof(addr);

​      `addrlen`：传入传出。 &clit_addr_len

​       **入：addr的大小。 出：客户端addr实际大小。**

- **返回值：**

    成功：能与客户端进行数据通信的 socket 对应的文件描述。

    失败： -1 ， errno

#### connect

```c++
// 使用现有的 socket 与服务器建立连接
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);  

// 示例
struct sockaddr_in srv_addr;    // 服务器地址结构
srv_addr.sin_family = AF_INET;
srv_addr.sin_port = 9527   		// 跟服务器bind时设定的 port 完全一致。
inet_pton(AF_INET, "服务器的IP地址"，&srv_adrr.sin_addr.s_addr);
connect(fd, (struct sockaddr*)&addr, sizeof(addr));
```

- **参数：**

  `sockfd`： socket 函数返回值

  `addr`：传入参数。服务器的地址结构

​      `addrlen`：服务器的地址结构的大小

- **返回值：**

    成功：0

    失败：-1 errno

​    如果不使用bind绑定客户端地址结构, 采用"隐式绑定".
