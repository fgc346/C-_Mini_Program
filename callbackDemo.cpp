#include <stdio.h> 
 
typedef void(*lpFunc)(void *, char *);  // 函数指针 
// 回调函数的宿主函数,在这里回调用函数被使用, 
void GetCallBack(void * lpVoid, lpFunc callback) 
{ 
    callback(lpVoid, "test"); 
    printf("GetCallBack,callback is end\n");
} 
  
  
class A{ 
public: 
    A(){}; 
    
    void outName(char szAlarm[]){ 
       printf("my name is %s \n", szAlarm);    
    } 
    
    // 被宿主调用的回调函数 
    static void fCallback(void *lpVoid, char szAlarm[]){ 
       A * p = (A*)(lpVoid); 
       p->outName(szAlarm); 
    } 
    
    //调用外部宿主函数,当Test函数调用过宿主函数以后，Test就再也不关心宿主函数 
    //什么时候调用回调函数了，因为那是宿主函数自己的事了 
    void Test(){ 
       GetCallBack(this, fCallback); 
       printf("Test,GetCallBack is end.\n");
    } 
}; 
 
int main(void) 
{ 
    A a; 
    a.Test(); 
    printf("a.Test is end.\n");
} 
