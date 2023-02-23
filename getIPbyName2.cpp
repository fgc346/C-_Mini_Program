#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
 
using namespace std;
 
bool GetIP(const std::string& strDevice,string& strip)
{
        int fd;
        struct ifreq ifr;
        //使用UDP协议建立无连接的服务
        fd = socket(AF_INET, SOCK_DGRAM, 0);
        strcpy(ifr.ifr_name, strDevice.c_str() );       
        //获取IP地址
        if (ioctl(fd, SIOCGIFADDR, &ifr) <  0)
        {
            close(fd);
            return false;
        }

        // 将一个IP转换成一个互联网标准点分格式的字符串
        strip = inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr);
        if(!strip.empty())
        {
            close(fd);
            return true;
        }
    return false;
}
 
int main()
{
    vector<string> vs;//预先定义了几种可能的网卡类型
    vs.push_back("enp4s0");
    std::string strDeviceName("enp4s0");
    // vs.push_back("em");
    // vs.push_back("oct");
    string str;
    if( (GetIP(strDeviceName,str)) )
    {
        cout<<str<<endl;
    }
    return 0;
}