#include "ArrayStack.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

uint64_t cputime(){
  unsigned int ax,dx;
  asm volatile("rdtsc\nmovl %%eax,%0\nmovl %%edx,%1":"=g"(ax),"=g"(dx): :"eax","edx");
  return (uint64_t(dx)<<32)+uint64_t(ax);
}

int main(){
  int n = 100;
  ods::ArrayStack<int> as;
  int r1 = 0, r2 = 0;
  uint64_t cpu1 = cputime();
  for (int i = 0; i < n; i++){
    as.add(i, i); 
  }
  for (int i = n - 1; i >= 0; i--){
    r1 += as.remove(i); 
  }
  uint64_t cpu2 = cputime();
  for (int i = 0; i < n; i++){
    as.add(0, i); 
  }
  for (int i = n - 1; i >= 0; i--){
    r2 += as.remove(0); 
  }
  uint64_t cpu3 = cputime();
  std::cout << "r1=" << r1 << ", cycle(1) : " << cpu2 - cpu1 << std::endl;
  std::cout << "r2=" << r2 << ", cycle(2) : " << cpu3 - cpu2 << std::endl;
  return 0;
}
