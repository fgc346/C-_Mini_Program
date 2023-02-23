//这里是对模板各种特性的小函数说明
//熟悉各个语法的使用

#pragma once
#include <memory>
#include <string>
#include <iostream>

template <typename T>
T average(T const* begin, T const* end)
{
    T total = T();
    int count = 0;
    while (begin != end){
        total += *begin;
        ++begin;
        ++count;
    }
    return total/count;
}

template <typename T>
class TypeTraits;

template <>
class TypeTraits<char>{
public:
    typedef int ReturnType;
};

template <>
class TypeTraits<short>{
public:
    typedef short ReturnType;
};

template <>
class TypeTraits<int>{
public:
    typedef int ReturnType;
};

template <>
class TypeTraits<float>{
public:
    typedef float ReturnType;
};

template <typename T,typename Traits>
typename Traits::ReturnType average_2(T const* begin, T const* end)
{
    typedef typename Traits::ReturnType ReturnType;
    ReturnType total = ReturnType();
    int count = 0;
    while (begin != end){
        total += *begin;
        ++begin;
        ++count;
    }
    return total/count;
}

//类模板成员函数在 模板外定义

class NullType {};

template <typename M0 = NullType, typename M1 = NullType,
          typename M2 = NullType, typename M3 = NullType>
class Component {
 public:
  Component() {}
  ~Component()  {}

  /**
   * @brief init the component by protobuf object.
   *
   * @param config which is defined in 'cyber/proto/component_conf.proto'
   *
   * @return returns true if successful, otherwise returns false
   */
  bool Initialize(const std::string& config) ;
  bool Process(const std::shared_ptr<M0>& msg0, const std::shared_ptr<M1>& msg1,
               const std::shared_ptr<M2>& msg2,
               const std::shared_ptr<M3>& msg3);

 private:
  /**
   * @brief The process logical of yours.
   *
   * @param msg0 the first channel message.
   * @param msg1 the second channel message.
   * @param msg2 the third channel message.
   * @param msg3 the fourth channel message.
   *
   * @return returns true if successful, otherwise returns false
   */
  virtual bool Proc(const std::shared_ptr<M0>& msg0,
                    const std::shared_ptr<M1>& msg1,
                    const std::shared_ptr<M2>& msg2,
                    const std::shared_ptr<M3>& msg3) = 0;
};

// 模板Component的全特化，需要为所有模板参数提供实参，实际上就是实例化模板，生成一个类定义
template <>
class Component<NullType, NullType, NullType, NullType>{
 public:
  Component() {}
  ~Component()  {}
  bool Initialize(const std::string& config);
};

//我们正在特例化的模板名为Component，全特例化版本Component<NullType, NullType, NullType, NullType> 实际上就是一个类
//下面就是对类的成员函数在类外的定义，和一个普通类的成员函数定义并没有什么区别
inline bool Component<NullType, NullType, NullType, NullType>::Initialize(const std::string &config) {
    std::cout << " Component<NullType, NullType, NullType>::Initialize is called " << std::endl;
    std::cout << " config = " << config << std::endl;
}

template < typename M0>
class Component<M0, NullType, NullType, NullType>{
 public:
  Component() {}
  ~Component()  {}
  bool Initialize(const std::string& config);
};

//偏特化模板，本质上还是一个模板
template < typename M0>
bool Component<M0, NullType, NullType, NullType>::Initialize(const std::string &config)
{
        std::cout << " template < typename M0> Component<NullType, NullType, NullType>::Initialize is called " << std::endl;
    std::cout << " config = " << config << std::endl;
}


//C++模板中困惑的语法


