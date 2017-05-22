#include "ArrayQueue.h"
#include <iostream>

int main(){
  int n = 10;
  ods::ArrayQueue<int> aq;
  for (int i = 0; i < n; i++){
    aq.add(i); 
  }
  for (int i = 0; i < n * 10; i++){
    std::cout << aq.remove() << std::endl;
    aq.add(i * i); 
  }
  return 0;
}
