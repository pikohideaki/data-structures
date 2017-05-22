#include "ArrayDeque.h"
#include <iostream>

int main(){
  int n = 10;
  ods::ArrayDeque<int> aq;
  for (int i = 0; i < n; i++){
    aq.add(i, i); 
  }
  for (int i = 0; i < n; i++){
    aq.add(i, -i); 
    aq.remove(0);
    aq.set(i, i * i);
  }
  for (int i = 0; i < aq.size(); i++){
    std::cout << aq.get(i) << std::endl;
  }
  return 0;
}
