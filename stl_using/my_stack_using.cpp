#include <iostream>
#include <vector>
#include <string>

#include "my_stack.h"

#include <stack>
#include <deque>

int main(int argc, char *argv[]) {
  MyStack<int> my_stack;
  std::cout << "my_stack size = " << my_stack.Size();
  my_stack.Push(1);
  std::cout << "after push 1, my_stack size = " << my_stack.Size()
            << " the top elem = " << my_stack.Top() << std::endl;

  my_stack.Push(2);
  std::cout << "after push 2, my_stack size = " << my_stack.Size()
            << " the top elem = " << my_stack.Top() << std::endl;

  my_stack.Push(3);
  std::cout << "after push 3, my_stack size = " << my_stack.Size()
            << " the top elem = " << my_stack.Top() << std::endl;

  std::vector<int> vec_1;
  int st_size = my_stack.Size();
  for (int i = 0; i < st_size; ++i) {
    std::cout << my_stack.Top() << " ";
    vec_1.emplace_back(my_stack.Pop());
  }
  std::cout << std::endl;
  std::cout << "vec_1.size =  " << vec_1.size() << std::endl;

  std::stack<std::string> st_str;

  st_str.push("fgc");
  st_str.push("jk");
  st_str.pop();


  return 0;
}