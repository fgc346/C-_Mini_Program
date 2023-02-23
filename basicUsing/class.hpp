/*
 * @Author: fenggaochao
 * @Date: 2022-06-01 16:37:33
 * @LastEditTime: 2022-06-02 09:05:17
 * @LastEditors: fenggaochao
 * @Description: 
 * @FilePath: /C-Concurrence-master/basicUsing/class.hpp
 */
#pragma once
#include <string>
#include <stdio.h>

// 如何设计基类和子类的关系，看Effiective C++ 的相关条款

class Base {
public:
  Base(const std::string &name, int age) : name_(name), age_(age) {
    printf("Base contruct, the name = %s, age = %d\n", name.data(), age);
  }
  virtual ~ Base(){
    printf("Base decontruct\n");
  }
  virtual void play(){
    printf("Base play\n");
    printInfo();
    printf("Base printInfo end\n");
  }
protected:
  virtual void printInfo() = 0;
  std::string name_;
  int age_;
};
class DriveA : public Base {
public:
  DriveA(const std::string &name, int age) : Base(name, age)
  {
    printf("DriveA construct\n");
  }
  virtual ~ DriveA() {
    printf("DriveA decontruct\n");
  }
  void play() override {
    printf("DriveA play\n");
    printInfo();
    printf("DriveA printInfo end\n");
  }
private:
  void printInfo() override
  {
    printf(" DriveA, printInfo successful, name = %s\n", name_.data());
  }
};

class DriveB : public Base {
public:
  DriveB(const std::string &name, int age) : Base(name, age)
  {
    printf("DriveB construct\n");
  }
   ~ DriveB(){}
private:
  void printInfo() override
  {
    printf(" DriveB, printInfo successful\n");
  }
};

class Drive_Drive_C : public DriveA {
public:
  Drive_Drive_C(const std::string &name, int age) : DriveA(name, age){
    
  }
  ~ Drive_Drive_C(){
    printf("Drive_Drive_C decontruct\n");
  }
};