# Linux 下常用的网络命令

- 远程登录的 ssh 指令；
- 远程传输文件的 scp 指令；
- 查看网络接口的 ifconfig 指令；
- 查看网络状态的 netstat 指令；
- 测试网络延迟的 ping 指令；
- 可以交互式调试和服务端的 telnet 指令；
- 两个 DNS 查询指令 host 和 dig；
- 可以发送各种请求包括 HTTPS 的 curl 指令

## 远程连接命令

### ssh

在需要远程登录 Linux 系统，可以使用 ssh 命令，比如你想远程登录一台服务器，可以使用 `ssh user@ip` 的方式，如下图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210720083556251.png)

接着，会有输入密码的提示，输入正确的密码后，就进入到了服务器的终端页面，之后你操作的命令就是控制服务器的了。

### scp

当我们需要把一台机器上的文件传输给另一台机器时，使用 scp 命令就可以。

如下图，我使用 scp 命令将本地 test.txt 文件传输给了 IP 地址为 192.168.12.35 机器的 /home 目录。

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021072008373828.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTg2NzM4Mg==,size_16,color_FFFFFF,t_70)

输入 scp 命令后，会弹出需要输入对方密码的提示，输入完成后，输入回车即可，如果密码验证通过后，就进行文件的传输。

## 查看本地网络状态

要想知道本地机器的网络状态，比较常用的网络命令是 ifconfig 和 netstat。

### ifconfig

当你想知道机器上有哪些网口，和网口对应的状态信息时，使用 ifconfig 就可以，状态信息包含 IP 地址、子网掩码、MAC 地址等。

如下图，是在我设备上的 ifconfig 信息。

<img src="https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZdLPmMFIssgdY0EWKOa1SupEW5klrZia6jITiaLvCPNrYugtHcAWZN8ZwY871N7gTwTESiaHHKw2PK6w/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1" alt="图片" style="zoom: 67%;" />

可以看到，这台机器一共有 3 个网口，分别是 eth0、eth1、lo。其中 lo 是本地回路，发送给 lo 就相当于发送给自己，eth0 和 eth1 都是真实的网口。

### netstat

**netstat 命令主要用于查看目前本机的网络使用情况。**

#### 查看所有 socket

如果只是单纯执行 netstat 命令，则查询的是本地所有 socket，如下图：

<img src="https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZdLPmMFIssgdY0EWKOa1SuprfPficOEdJj4piczVhRr3BficaOtFMbVIwwlbzib8govv5Lia9ciaR0oYbpQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1" alt="图片" style="zoom: 80%;" />

上图中，我们看到的都是 socket 文件，socket 负责在客户端与服务端之间收发数据，当客户端和服务端建立连接时，各自同时都会生成一个 socket 文件，用于管理这个连接。

#### 查看 TCP/UDP 连接

如果只想看 TCP 连接的网络信息，可以使用 netstat -t。

比如下面我通过 netstat -t 看 tcp 协议的网络情况：

![图片](https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZdLPmMFIssgdY0EWKOa1Supo3XCULXKxhQK8rQUMgbYXmq4TwoSY0Sbh8niaLsDOA3ZrKApTibA8iayw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

上图的末尾的 state 描述的是当前 TCP 连接处于的状态。

另外，如果要想看 UDP 的网络信息，可以使用 netstat -u。

#### 查看端口占用

如果你想知道某个端口是哪个进程在占用，比如我想查 80 端口被哪个进程占用了，如下图：

![图片](https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZdLPmMFIssgdY0EWKOa1SupOQFcbzOPpVMzoKcn3MdZrehukiassMAf8nia4HLykibb9X1M2kibWlOr2g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

可以看到，80 端口被 http 进程占用了，最末尾的信息也能看到这个进程对应的 pid。

## 网络测试

当我们想确认网络的延时情况，以及与服务器网络是否畅通，则可以使用 ping 和 telnet 命令。

### ping

想知道本机到目标网页的网络延时，可以使用 ping 命令，如下图所示：

<img src="https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZdLPmMFIssgdY0EWKOa1SupKOzHJqB12jLknETr5gLuiczCu0K0u87CyhcDIpXaoztpUZ3KGnicPxyg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1" alt="图片" style="zoom:80%;" />

**ping 是基于 ICMP 协议的**，所以对方防火墙如果屏蔽了 ICMP 协议，那么我们就无法与它 ping 通，但这并不代表网络是不通的。

每一个 ICMP 包都有序号，所以你可以看到上图中 icmp 序号，如果序号是断断续续的，那么可能出现了丢包现象。

time 显示了网络包到达远程主机后返回的时间，单位是毫秒。time 的时间越小，说明网络延迟越低，如果你看到 time 的时间变化很大，这种现象叫做网络抖动，这说明客户端与服务器之间的网络状态不佳。

**ttl 全称叫 time to live，指定网络包被路由器丢弃之前允许通过的网段数量，说白了就是定义了网络包最大经过路由器的数量**，这个目的是防止网络包在网络中被无限转发，永不停止。当网络包在网络中被传输时，ttl 的值通过一个路由器时会递减1，当 ttl 递减到 0 时，网络包就会被路由器抛弃。

另外，ping 不单单只能输入 ip 地址，也能输入域名地址，如果输入的是域名地址，会先通过 DNS 查询该域名的 ip 地址，再进行通信。

### telnet

有时候，我们想知道本机到某个 IP + 端口的网络是否通畅，也就是想知道对方服务器是否有对应该端口的进程，于是就可以使用 telnet 命令，如下所示：

> telnet 192.168.0.5 

telnet 执行后会进入一个交互式的页面，这时就可以填写你将要发送给对方的信息，比如你想发 HTTP 请求给服务器，那么你就可以写出 HTTP 请求 的格式信息，但是手写 HTTP 报文太累人吧，后面会介绍专门用于 HTTP 的网络工具。

## DNS 查询

如果想知道 DNS 解析域名的过程，可以使用 host 和 dig 命令。

### host

host 就是一个 DNS 查询命令，比如我们要查百度的 DNS，如下图所示：

![图片](https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZdLPmMFIssgdY0EWKOa1SupgIhibNlgxRAEeiaPiaxibhu6oDg8KGyhSGOqZN9txq58qSdMZl8gNPt77A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

可以看到，www.baidu.com 只是个别名，原名是 www.a.shifen.com，且对应了 2 条 IPv4 地址。

如果想追查某种类型的记录，可以加个 -t 参数，比如下图我们追查百度的 AAAA 记录，也就是查询域名对应的 IPv6 地址，由于百度还没部署 IPv6 地址，所以没有查询到 ：

![图片](https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZdLPmMFIssgdY0EWKOa1Supiawsbvms0EjLQQBIS03E2yJhBF4KrBYqBcujT1eww7odgbJo3nZPWEg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

### dig

dig 同样也是做 DNS 查询的，区别在于，dig 显示的内容更加详细，比如下图是 dig 百度的结果：

![图片](https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZdLPmMFIssgdY0EWKOa1SupNOibiatibeibDnp0GOEMnb6OCP6kPcgIfT3tMiaGXP3PvUznfC9tywjibj2A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

也可以看到 www.baiu.com 的别名（CNAME）为 www.a.shifen.com，然后共有 2 条 A 记录，也就是 IPv4 地址的记录，通常对应多个是为了负载均衡或分发内容。

## HTTP

在电脑桌面我们常使用浏览器去请求网页，而在服务器一般是没有可视化页面的，也就没有浏览器，这时如果想要 HTTP 访问，就需要网络相关的命令。

### curl

如果要在命令行请求网页或者接口，可以使用 curl 命令，curl 支持很多应用协议，比如 HTTP、FTP、SMTP 等，实际运用中最常用还是 HTTP。

比如，我用 curl 访问了百度网页，如下图：

![图片](https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZdLPmMFIssgdY0EWKOa1SupxxCFdrjY3yFiazdvHUDE5jz4hIBxNVHo686pxamrzTzDZNS0QV6uRlA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

如果不想看 HTTP 数据部分，只想看 HTTP GET 返回头，可以在加个 -I 参数，如 curl -I，如下图所示：

![图片](https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZdLPmMFIssgdY0EWKOa1SupKtEwYKlXo0EpN3fIz4H45hjaGHibVr1aoqZkOljZTecnr52tWgPgnew/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

上面演示的 HTTP GET 请求，如果想使用 POST 请求，命令如下：

![图片](https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZdLPmMFIssgdY0EWKOa1Sup5LksicibeicqFTXrAWrxX9icbuymsbic16GeiblAaE2bSq9vShpzhzVOqtGw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

curl 向 http://localhost/myapi 接口发送 POST 请求，各参数的说明：

- -d 后面是要发送的数据，例子中发送的是 JSON 格式的数据； 
- -X 后面是指定 HTTP 的方法，例子中指定的是 POST 方法；
- -H 是指定自定义的请求头，例子中由于发送的是 JSON 数据，所以内容类型指定了 JSON；