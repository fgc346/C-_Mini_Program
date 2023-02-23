#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include <string.h>
#include <unistd.h>
#include <chrono>
using namespace std;

	typedef struct CChannelParam
	{
		char* mc_ip;
		uint16_t mc_port;
		char* local_ip;
		uint16_t local_port;
		char* channel_name;
		int channel_type;
		uint32_t max_queue_size;
		int32_t max_msg_size;
		char strategy;
		char reliable_transport;
		char joiner_number;
		int timeout_ms;
		int resend_interval;
	} CChannelParam;

typedef struct CInitParam
{
    char* log_upload_addr;
    char* client_name;
    int client_type;
} CInitParam;

static double getCurrentTimestamp()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count()/ 1000000000.0;
};

int main(){
    CChannelParam oneChannelParam;
    memset(&oneChannelParam, 0, sizeof(oneChannelParam));
    oneChannelParam.mc_ip = new char[50];
    oneChannelParam.local_ip = new char[50];
    oneChannelParam.channel_name = new char[50];

    strcpy(oneChannelParam.mc_ip, "239.255.255.228");
    strcpy(oneChannelParam.local_ip, "10.0.105.56");
    strcpy(oneChannelParam.channel_name, "sendAll");

    printf("oneChannelParam.mc_ip=%s\n", oneChannelParam.mc_ip);
    printf("oneChannelParam.local_ip=%s\n", oneChannelParam.local_ip);
    printf("oneChannelParam.channel_name=%s\n", oneChannelParam.channel_name);
    printf("sizeof(oneChannelParam.mc_ip) = %d\n", sizeof(oneChannelParam.mc_ip));
    printf("sizeof(oneChannelParam.local_ip) = %d\n", sizeof(oneChannelParam.local_ip));
    printf("sizeof(oneChannelParam.channel_name) = %d\n", sizeof(oneChannelParam.channel_name));
    memset(oneChannelParam.mc_ip, 0, sizeof(oneChannelParam.mc_ip));
    printf("\noneChannelParam.mc_ip=%s\n\n", oneChannelParam.mc_ip);
    strcpy(oneChannelParam.mc_ip, "239.255.255.2");
    strcpy(oneChannelParam.local_ip, "10.0.105.5");
    strcpy(oneChannelParam.channel_name, "send");
    printf("oneChannelParam.mc_ip=%s\n", oneChannelParam.mc_ip);
    printf("oneChannelParam.local_ip=%s\n", oneChannelParam.local_ip);
    printf("oneChannelParam.channel_name=%s\n", oneChannelParam.channel_name);
    printf("sizeof(oneChannelParam.mc_ip) = %d\n", sizeof(oneChannelParam.mc_ip));
    printf("sizeof(oneChannelParam.local_ip) = %d\n", sizeof(oneChannelParam.local_ip));
    printf("sizeof(oneChannelParam.channel_name) = %d\n", sizeof(oneChannelParam.channel_name));


    while(1)
    {
        printf("\nbefore usleep is exec,the current time=%f\n",getCurrentTimestamp());
        usleep(1000000);
        printf("\nafter usleep is exec,the current time=%f\n",getCurrentTimestamp());
    }


    CChannelParam aChannelParam;
    memset(&aChannelParam, 0, sizeof(aChannelParam));
    int mnNetClientID = 20;
    std::stringstream ss;
        std::string strName("vehicle_");
        ss << strName << mnNetClientID;
    aChannelParam.strategy = 2;
    std::cout << "aChannelParam.strategy= " << aChannelParam.strategy << std::endl;

    CInitParam aInitParam;
     memset(&aInitParam, 0, sizeof(aInitParam));
    aInitParam.client_type = mnNetClientID;
    std::string str("aaaa");
    // aInitParam.client_name = (char *)str.data();
    aInitParam.client_name = const_cast<char*>(str.data()) ;
    // aInitParam.client_name = new char[ss.str().size() + 1];
     cout << " ss.str().size() = " << ss.str().size() << std::endl;
    cout << " aInitParam.client_name.size = " << sizeof(aInitParam.client_name) << std::endl;
    cout << "aInitParam.client_name.size =" << strlen(aInitParam.client_name) << std::endl;
    strcpy(aInitParam.client_name, ss.str().c_str());
    cout << "****aInitParam.client_name.size =" << strlen(aInitParam.client_name) << std::endl;

    // memcpy((char *)aInitParam.client_name, ss.str().c_str(), ss.str().size());

    std::cout << "aInitParam.client_name= " << aInitParam.client_name << std::endl;


    // delete aInitParam.client_name;
    // aInitParam.client_name = nullptr;
    
    printf("aChannelParam.strategy=%d\n",aChannelParam.strategy);
    int iData = aChannelParam.strategy;
    std::cout << "iData= " << iData << std::endl;
    //用于存放分割后的字符串 
    vector<string> res;
    //待分割的字符串，含有很多空格 
    string word="   Hello, I want   to learn C++!   ";
    //暂存从word中读取的字符串 
    string result;
    //将字符串读到input中 
    stringstream input(word);
    //依次输出到result中，并存入res中 
    while(input>>result)
        res.push_back(result);
    //输出res 
    for(int i=0;i<res.size();i++){
        cout<<res[i]<<endl;
    }
    return 0;
}