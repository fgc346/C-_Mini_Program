#pragma once
template <typename T>
class MyStack
{
public:
    struct Node
    {
        Node() : next(nullptr){}
        T item;
        Node* next;
    };
    MyStack() : first_(nullptr), N_(0)
    {
    }
    bool IsEmpty() {
        return first_ = nullptr;
    }
    int Size() {
        return N_;
    }
    void Push(T item)
    {
        //向栈顶添加元素
        Node* old_first = first_;
        first_ = new Node();
        first_->item = item;
        first_->next = old_first;
        ++N_;
    }
    T Pop()
    {
        //从栈顶删除元素
        T item = first_->item;
        first_ = first_->next;
        --N_;
        return item;
    }
    T Top()
    {
        //获取栈顶元素
        T item = first_->item;
        return item;
    }
private:
    Node* first_;
    int N_;     //元素的数量
};