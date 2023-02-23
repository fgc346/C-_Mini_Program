#include<errno.h>
#include "/usr/include/x86_64-linux-gnu/sys/types.h"
#include <unistd.h>
#inlcude <netinet/tcp.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<arpa/inet.h>
#include<net/if.h>
#include<cstdlib>
#include<iostream>
#include <string>

/****************
brief:根据网卡的名称编号获取指定的IP地址
param:ifName，需要取IP地址的网卡名称
return 获取的指定网卡上的IP地址
****************/
const char* getIPByIfName(const char *ifName)
{
      int sock;
      struct ifreq ifr;   //结构体头文件#include<net/if.h>
      static const char *none_if="0.0.0.0";
      if(Null == ifName)
      	return none_ip;
      sock = ::socket(AF_INET,SOCK_DGRAM,0)；
      if(-1 == sock)
      	return none_ip;
      bzero(ifr.ifr_name,sizeof(ifr.ifr_name));
      strncpy(ifr.ifr_name,ifName,sizeof(ifr.ifr_name)-1);
      if(-1 == ioctl(sock,SIOCGIFADDR,&ifr))//获取网卡的IP地址
      {
          TEMP_FAILURE_ENTRY(::close(sock));
          return none_ip;
      }
       TEMP_FAILURE_ENTRY(::close(sock));
       return inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr);//将网络地址转换成字符串
}


int main()
{
    std::string  strName("enp4s0");
    printf("the ip=%s\n", getIPByIfName(strName.data()));
}