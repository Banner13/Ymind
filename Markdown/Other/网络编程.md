第六章.网络编程	2
1. 网络编程简介	2
1.1 五层因特网协议栈	2
1. 2 传输层和应用层的常见协议	2
2. 网络编程之TCP/UDP比较	4
2.1 TCP和UDP 原理上的区别	4
2.2 为何存在UDP协议	4
2.3 TCP/UDP网络通信大概交互图	4
3. 网络编程主要函数介绍	7
3.1 socket函数	7
3.2 bind函数	7
3.3 listen函数	8
3.4 accept函数	8
3.5 connect函数	8
3.6 send函数	9
3.7 recv函数	9
3.8 recvfrom函数	9
3.9 sendto函数	9
4. TCP编程简单示例	10
4.1 服务器端代码	10
4.2 客户端代码	13
4.3 Makefile文件	15
4.4 执行	15
5. UDP编程简单示例	16
5.1 服务器端代码	16
5.2客户端代码	18
5.2.1 客户端程序1	18
5.2.2 客户端程序2	20
5.3 Makefile文件	22
5.4 执行	22

 

第六章.网络编程

1. 网络编程简介
要编写通过计算机网络通信的程序，首先要确定这些程序同通信的协议（protocol），在设计一个协议的细节之前，首先要分清程序是由哪个程序发起以及响应何时产生。
举例来说，一般认为WEB服务器程序是一个长时间运行的程序（守护进程deamon），它只在响应来自网络的请求时才发送网络消息。协议的另一端是web客户程序，如某种浏览器，与服务器进程的通信总是由客户进程发起。大多数网络应用就是按照划分为客户（clinet）和服务器（server）来组织的。

1.1 五层因特网协议栈
为了给网络协议的设计提供一个结构，网络设计者以分层（layer）的方式组织协议以及实现这些协议的网络硬件和软件。
分层提供了一种结构化方式来讨论系统组件。模块化使更新系统组件更为容易。
协议栈是各层所有协议的总和。
 
五层因特网协议栈
应用层：应用层是网络应用程序及它们的应用层协议存留的地方。
运输层：因特网的运输层在应用程序端点之间传从应用层报文。
网络层：因特网呃网络层负责将称为数据包（datagram）的网络层分组从一台主机移动到另一台主机。
链路层：因特网的网络层通过源和目的地之间的一系列路由器路由数据报。
物理层：虽然链路层的任务是将整个帧从一个网络元素移动到临近的网络元素，而物理层的任务是将该帧的一个一个比特从一个节点移动到下一个节点。

1.	2 传输层和应用层的常见协议
我们重点介绍和应用层编程关系密切的应用层和运输层。

应用层：
因特网的应用层包含很多协议，例如HTTP，SMTP，和 FTP。我们看到的某些网络功能，比如将www.baidu.com这样对人友好的端系统名字转换为32比特网络地址，也是借助于特定的应用层协议即域名系统（DNS）完成的。
应用层的协议分布在多个端系统上，一个端系统中的应用程序使用协议与另一个端系统中的应用程序交换信息分组。

运输层：
在英特网中有两个运输协议，即TCP和UDP，利用其中的任何一个都能运输应用层报文。我们写应用程序的时候具体选择哪个运输层协议应该根据实际情况来确定（后面会具体讲解）。
 

2.	网络编程之TCP/UDP比较

2.1 TCP和UDP 原理上的区别
TCP向它的应用程序提供了面向连接的服务。这种服务包括了应用层报文向目的地的确保传递和流量控制（即发送方/接收方速率匹配）。这种服务包括了应用层报文划分为短报文，并提供拥塞控制机制，因此当网络拥塞时源抑制其传输速率。
UDP协议向它的应用程序提供无连接服务。这是一种不提供不必要服务的服务，没有可靠性，没有流量控制，也没有拥塞控制。

2.2 为何存在UDP协议
既然TCP提供了可靠数据传输服务，而UDP不能提供，那么TCP是否总是首选呢？答案是否定的，因为有许多应用更适合用UDP，原因有以下几点：
a.	关于何时发送什么数据控制的更为精细。
采用UDP时只要应用进程将数据传递给UDP，UDP就会立即将其传递给网络层。而TCP有重传机制，而不管可靠交付需要多长时间。但是实时应用通常不希望过分的延迟报文段的传送，且能容忍一部分数据丢失。
b.	无需建立连接，不会引入建立连接时的延迟。
c.	无连接状态，能支持更多的活跃客户。
d.	分组首部开销较小。

2.3 TCP/UDP网络通信大概交互图
下面我们分别画出运用TCP协议和运用UDP协议的客户端和服务器大概交互图。
 
面向连接的TCP流模式


 
UDP用户数据包模式
 

3. 网络编程主要函数介绍
3.1 socket函数
int socket(int domain, int type,int protocol);

此函数用于创建一个套接字。
domain是网络程序所在的主机采用的通讯协族(AF_UNIX和AF_INET等)。
AF_UNIX只能够用于单一的Unix 系统进程间通信，而AF_INET是针对Internet的，因而可以允许远程通信使用。

type是网络程序所采用的通讯协议(SOCK_STREAM,SOCK_DGRAM等)。
SOCK_STREAM表明用的是TCP 协议，这样会提供按顺序的，可靠，双向，面向连接的比特流。
SOCK_DGRAM 表明用的是UDP协议，这样只会提不可靠，无连接的通信。

关于protocol，由于指定了type，所以这个地方一般只要用0来代替就可以了。
此函数执行成功时返回文件描述符，失败时返回-1,看errno可知道出错的详细情况。

3.2 bind函数
int bind(int sockfd, struct sockaddr *my_addr, int addrlen);

从函数用于将地址绑定到一个套接字。
sockfd是由socket函数调用返回的文件描述符。
my_addr是一个指向sockaddr的指针。
addrlen是sockaddr结构的长度。

sockaddr的定义：







不过由于系统的兼容性,我们一般使用另外一个结构(struct sockaddr_in) 来代替。

sockaddr_in的定义：
 
 








如果使用Internet所以sin_family一般为AF_INET。
sin_addr设置为INADDR_ANY表示可以和任何的主机通信。
sin_port是要监听的端口号。
bind将本地的端口同socket返回的文件描述符捆绑在一起.成功是返回0,失败的情况和socket一样。

3.3 listen函数
int listen(int sockfd,int backlog);

此函数宣告服务器可以接受连接请求。
sockfd是bind后的文件描述符。
backlog设置请求排队的最大长度。当有多个客户端程序和服务端相连时，使用这个表示可以介绍的排队长度。
listen函数将bind的文件描述符变为监听套接字，返回的情况和bind一样。

3.4 accept函数
int accept(int sockfd, struct sockaddr *addr,int *addrlen);

服务器使用此函数获得连接请求，并且建立连接。
sockfd是listen后的文件描述符。
addr，addrlen是用来给客户端的程序填写的,服务器端只要传递指针就可以了， bind,listen和accept是服务器端用的函数。
accept调用时，服务器端的程序会一直阻塞到有一个客户程序发出了连接。 accept成功时返回最后的服务器端的文件描述符，这个时候服务器端可以向该描述符写信息了，失败时返回-1 。

3.5 connect函数
int connect(int sockfd, struct sockaddr * serv_addr,int addrlen);

可以用connect建立一个连接，在connect中所指定的地址是想与之通信的服务器的地址。
sockfd是socket函数返回的文件描述符。
serv_addr储存了服务器端的连接信息，其中sin_add是服务端的地址。
addrlen是serv_addr的长度 
connect函数是客户端用来同服务端连接的.成功时返回0，sockfd是同服务端通讯的文件描述符，失败时返回-1。

3.6 send函数
ssize_t send(int sockfd, const void *buf, size_t len, int flags);

sockfd 指定发送端套接字描述符；
buf 指明一个存放应用程序要发送数据的缓冲区；
len 指明实际要发送的数据的字节数；
flags 一般置0。
客户或者服务器应用程序都用send函数来向TCP连接的另一端发送数据

3.7 recv函数
ssize_t recv(int sockfd, void *buf, size_t len, int flags);

sockfd 指定接收端套接字描述符；
buf 指明一个缓冲区，该缓冲区用来存放recv函数接收到的数据；
len 指明buf的长度；
flags 一般置0。
客户或者服务器应用程序都用recv函数从TCP连接的另一端接收数据。

3.8 recvfrom函数
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);

recvfrom通常用于无连接套接字，因为此函数可以获得发送者的地址。
src_addr 是一个struct sockaddr类型的变量，该变量保存源机的IP地址及端口号。
addrlen 常置为sizeof （struct sockaddr）。

3.9 sendto函数
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);

sendto和send相似，区别在于sendto允许在无连接的套接字上指定一个目标地址。
dest_addr 表示目地机的IP地址和端口号信息，
addrlen 常常被赋值为sizeof （struct sockaddr）。
sendto 函数也返回实际发送的数据字节长度或在出现发送错误时返回－1。  
 

4. TCP编程简单示例
服务器首先进行初始化操作：调用函数socket创建一个套接字，函数bind将这个套接字与服务器的公认地址绑定在一起，函数listen将这个套接字换成倾听套接字，然后调用函数accept来等待客户机的请求。过了一段时间后，客户机启动，调用socket创建一个套接字，然后调用函数connect来与服务器建立连接。连接建立之后，客户机和服务器通过读、写套接字来进行通信。

4.1 服务器端代码

参考：TCP/server_line.c
 




 
 

4.2 客户端代码

参考TCP/client_line.c 
 

4.3 Makefile文件














4.4 执行
服务器端：


客户端：


客户端输入：


服务器端显示：


 

5. UDP编程简单示例
UDP服务器首先进行初始化操作：调用函数socket创建一个数据报类型的套接字，函数bind将这个套接字与服务器的公认地址绑定在一起。然后调用函数recvfrom接收UDP客户机的数据报。UDP客户机首先调用函数socket创建一个数据报套接字，然后调用函数sendto向服务器发送数据报。在结束通信后，客户机调用close关闭UDP套接字，服务器继续使用这个UDP套接字接收其它客户机的数据报。

5.1 服务器端代码

参考UDP/server_line.c 


 










 

5.2 客户端代码
5.2.1 客户端程序1

参考UDP/client_line_1.c 
 

问：用UDP协议写网络通讯程序不可以用connect函数吗？
答：非也。

5.2.2 客户端程序2

参考UDP/client_line_2.c
 
 








在客户端代码2中，connect函数并非真的在协议层建立了连接，它只是指定了服务器的地址和端口号信息。
因为在connect中指定了服务器的地址和端口号信息，所以后面的send就可以直接发送了，而不用再次指定地址和端口号。

5.3 Makefile文件















5.4 执行
服务器端执行：


客户端执行：


客户端输入：


服务器端显示：

