#include <stdio.h>

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  std::string str("abc");
  std::string::size_type position;
  position = str.find("a", 100);
  if (position == std::string::npos) {
    printf("str %s not find  'a' in pos 100\n", str.data());
  }
  std::string str(
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaa");
  return 0;
}