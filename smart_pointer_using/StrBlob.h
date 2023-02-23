#pragma once

#include <stdio.h>


#include <string>
#include <vector>
#include <memory>
#include <exception>

class StrBlobPtr;

class StrBlob {
public:
    friend class StrBlobPtr;
    using size_type = std::vector<std::string>::size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const {
        return data->size();
    }
    bool empty() const {
        return data->empty();
    }
    // 添加和删除元素
    void push_back(const std::string &t) {
        data->push_back(t);
    }
    void pop_back();
    //元素访问
    std::string& front();
    std::string& back();

    // 重载const版本的添加和访问
    const std::string& front() const;
    const std::string& back() const;
private:
    std::shared_ptr<std::vector<std::string>> data;
    //如果 data[i]不合法，抛出一个异常
    void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()){
    printf(" StrBlob construct called!\n");
}

StrBlob::StrBlob(std::initializer_list<std::string> il) : 
    data(std::make_shared<std::vector<std::string>>(il))
{
    printf("StrBlob initializer_list construct called\n");
}

void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i > data->size())
    {
        throw std::out_of_range(msg);
    }
}

std::string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}
std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on emptyp StrBlob");
    data->pop_back();
}

const std::string& StrBlob::front() const {
    check(0,"front on empty const StrBlob");
    return data->front();
}
const std::string& StrBlob::back() const{
    check(0, "back on empty const StrBlob");
    return data->back();
}


class StrBlobPtr {
public :
    StrBlobPtr() : curr(0){
        printf("StrBlobPtr contruct is called\n");
    }
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {
        printf("StrBlobPtr contruct StrBlob a is called\n");
    }

    StrBlobPtr(const StrBlob &b, size_t sz = 0) : wptr(b.data), curr(sz){
        printf("StrBlobPtr const contruct is called\n");
    }

    std::string& deref() const;
    StrBlobPtr& incr();     //前缀递增

private :
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string &) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;   //在数组中的当前位置
};

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
    {
        throw std::runtime_error("unbound StrBlobPtr");
    }
    if (i >= ret->size())
    {
        throw std::out_of_range(msg);
    }
    return ret;     //否则，返回指向vector的shared_ptr
}

std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];        //(*p)是对象所指向的vector
}

StrBlobPtr& StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr; //推进当前位置
    return *this;
}