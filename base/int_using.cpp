#include <stdio.h>

typedef signed long int64_t;

const double latency = 0.05; // 决策周期50ms

int main()
{
  int64_t sleep_time_us = latency * 1e6;

  printf("sleep_time_us = %lld\n", sleep_time_us);
  return 0;
}