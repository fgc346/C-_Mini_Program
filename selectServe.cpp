#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>

#define IPADDR      "127.0.0.1"
#define PORT        8787
#define MAXLINE     1024
#define LISTENQ     5
#define SIZE        3

typedef struct server_context_st
{
    int cli_cnt;        /*客户端个数*/
    int clifds[SIZE];   /*客户端的个数*/
    fd_set allfds;      /*句柄集合*/
    int maxfd;          /*句柄最大值*/
} server_context_st;
static server_context_st *s_srv_ctx = NULL;
/*===========================================================================
 * ==========================================================================*/
static int create_server_proc(const char* ip,int port)
{
    int  fd;
    struct sockaddr_in servaddr;
    
    //socket函数建立一个网络通信的套接口
    //第一个参数是网络通信的协议族，AF_INET ipv4, AF_INET6 ipv6
    //第二个参数，套接口的类型，SOCK_STREAM 有保障的，面向连接的SOCKET，SOCK_DGRAM 无保障地面向消息的SOCKET,主要用于在网络上发广播消息
    //第三个参数，表示通信协议，通常为0
    //正常返回值为 套接口的描述符，出错返回-1
    fd = socket(AF_INET, SOCK_STREAM,0);        
    if (fd == -1) {
        fprintf(stderr, "create socket fail,erron:%d,reason:%s\n",
                errno, strerror(errno));
        return -1;
    }

    /*一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用。*/
    int reuse = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        return -1;
    }

    //bzero，对结构体进行清零，类似于memset函数
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    //"点分十进制" -> "整数"
    inet_pton(AF_INET,ip,&servaddr.sin_addr);
    //htons 主机字节顺序转换为网络字节顺序
    servaddr.sin_port = htons(port);

    //bind函数将一个本地协议地址赋予一个套接字
    if (bind(fd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1) {
        perror("bind error: ");
        return -1;
    }

    // 将套接字变成被动的连接监听套接字（被动等待客户端的连接）
    // 第二个参数内核应为相应套接字排队的最大连接个数，默认为5
    listen(fd,LISTENQ);

    return fd;
}

static int accept_client_proc(int srvfd)
{
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cliaddr);
    int clifd = -1;

    printf("accpet clint proc is called.\n");

//accept 服务器通过 accept 函数接收来自客户端的连接请求的方式，默认是阻塞方式
//goto的用法， 由有效标志符和符号“；”组成
ACCEPT:
    clifd = accept(srvfd,(struct sockaddr*)&cliaddr,&cliaddrlen);

    if (clifd == -1) {
        if (errno == EINTR) {
            goto ACCEPT;
        } else {
            fprintf(stderr, "accept fail,error:%s\n", strerror(errno));
            return -1;
        }
    }

    //inet_ntoa 将网络地址转换成“.”点隔的字符串格式
    fprintf(stdout, "accept a new client: %s:%d\n",
            inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);

    //将新的连接描述符添加到数组中
    int i = 0;
    for (i = 0; i < SIZE; i++) {
        if (s_srv_ctx->clifds[i] < 0) {
            s_srv_ctx->clifds[i] = clifd;
            s_srv_ctx->cli_cnt++;
            break;
        }
    }

    if (i == SIZE) {
        fprintf(stderr,"too many clients.\n");
        return -1;
    }

}

static int handle_client_msg(int fd, char *buf)
{
    assert(buf);
    printf("\n\nrecv buf is :%s,from fd %d\n\n", buf, fd);
    write(fd, buf, strlen(buf) +1);
    return 0;
}

static void recv_client_msg(fd_set *readfds)
{
    printf("recv_client_msg,s_srv_ctx->cli_cnt=%d\n",s_srv_ctx->cli_cnt);
    int i = 0, n = 0;
    int clifd;
    char buf[MAXLINE] = {0};
    int icurrentClientCnt = s_srv_ctx->cli_cnt;
    for (i = 0;i <= icurrentClientCnt;i++) {
        clifd = s_srv_ctx->clifds[i];
        if (clifd < 0) {
            continue;
        }
        /*判断客户端套接字是否有数据*/
        if (FD_ISSET(clifd, readfds)) {
            //接收客户端发送的信息
            n = read(clifd, buf, MAXLINE);
            if (n <= 0) {
                /*n==0表示读取完成，客户都关闭套接字*/
                FD_CLR(clifd, &s_srv_ctx->allfds);
                close(clifd);
                s_srv_ctx->clifds[i] = -1;
                --s_srv_ctx->cli_cnt;   //如果客户端关闭了套接字，服务端的连接总数需要将该连接去除
                continue;
            }
            handle_client_msg(clifd, buf);
        }
    }
}
static void handle_client_proc(int srvfd)
{
    int  clifd = -1;
    int  retval = 0;
    fd_set *readfds = &s_srv_ctx->allfds;
    struct timeval tv;
    int i = 0;

    while (1) {
        /*每次调用select前都要重新设置文件描述符和时间，因为事件发生后，文件描述符和时间都被内核修改啦*/
        FD_ZERO(readfds);
        /*添加监听套接字*/
        FD_SET(srvfd, readfds);
        s_srv_ctx->maxfd = srvfd;

        tv.tv_sec = 30;     //设置超时时间 30s
        tv.tv_usec = 0;
        /*添加客户端套接字*/
        for (i = 0; i < s_srv_ctx->cli_cnt; i++) {
            clifd = s_srv_ctx->clifds[i];
            printf("i=%d,clifd=%d,\n", i , clifd);
            /*去除无效的客户端句柄*/
            if (clifd != -1) {
                FD_SET(clifd, readfds);
            }
            s_srv_ctx->maxfd = (clifd > s_srv_ctx->maxfd ? clifd : s_srv_ctx->maxfd);
        }

        /*开始轮询接收处理服务端和客户端套接字*/
        //select：返回值 就绪描述符的数目，超时返回0，出错返回-1
        retval = select(s_srv_ctx->maxfd + 1, readfds, NULL, NULL, &tv);
        if (retval == -1) {
            fprintf(stderr, "select error:%s.\n", strerror(errno));
            return;
        }
        if (retval == 0) {
            fprintf(stdout, "select is timeout.\n");
            continue;
        }
        //FD_ISSET：检查集合中指定的文件描述符是否可以读写
        if (FD_ISSET(srvfd, readfds)) {
            /*监听客户端请求*/
            printf("exec accept_client_proc.\n");
            accept_client_proc(srvfd);
        } else {
            /*接受处理客户端消息*/
            printf("exec recv_client_msg.\n");
            recv_client_msg(readfds);
        }
    }
}

static void server_uninit()
{
    if (s_srv_ctx) {
        free(s_srv_ctx);
        s_srv_ctx = NULL;
    }
}

static int server_init()
{
    s_srv_ctx = (server_context_st *)malloc(sizeof(server_context_st));
    if (s_srv_ctx == NULL) {
        return -1;
    }

    memset(s_srv_ctx, 0, sizeof(server_context_st));

    int i = 0;
    for (;i < SIZE; i++) {
        s_srv_ctx->clifds[i] = -1;
    }

    return 0;
}

int main(int argc,char *argv[])
{
    int  srvfd;
    /*初始化服务端context*/
    if (server_init() < 0) {
        return -1;
    }
    /*创建服务,开始监听客户端请求*/
    srvfd = create_server_proc(IPADDR, PORT);
    if (srvfd < 0) {
        fprintf(stderr, "socket create or bind fail.\n");
        goto err;
    }
    /*开始接收并处理客户端请求*/
    printf("the serve fd,srvfd=%d\n", srvfd);
    handle_client_proc(srvfd);
    server_uninit();
    return 0;
err:
    server_uninit();
    return -1;
}