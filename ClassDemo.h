#ifndef _CLASSDEMO_H_
#define _CLASSDEMO_H_

#include <string>
#include <stdio.h>
class A
{
public:
    A();
    ~A(){}
    void printMember();
private:
    int m_age;
    std::string m_strID;
};
A::A():m_age(10)
{
    m_strID = "id1";
}
void A::printMember()
{
    printf("the age=%d, m_strID= %s\n", m_age, m_strID.data());
}
#endif