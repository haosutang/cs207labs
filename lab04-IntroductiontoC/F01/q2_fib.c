#include <stdint.h>
#include <stdio.h>

int fib(int n);

int main(int argc, char **argv)
{
  int64_t n = 8;
  printf("output: %d", fib(n));
}

int fib(int n){
  if(n==1){
    return 0;
  }
  if(n==2){
    return 1;
  }
  return fib(n-1)+fib(n-2);
}
