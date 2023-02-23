// rvo_nrvo.cc
#include <iostream>

class A {
  public:
    A() {
      std::cout << "[C] constructor fired." << std::endl;
    }

    A(const A &a) {
      std::cout << "[C] copying constructor fired." << std::endl;
    }

    // A(A &&a) {
    //  std::cout << "[C] moving copying constructor fired." << std::endl;
    // }

    ~A() {
      std::cout << "[C] destructor fired." << std::endl;
    }
};

A getTempA() {
  return A();
}

int main(int argc, char **argv) {
  // auto x = getTempA();
  A x(getTempA());

  return 0;
}
