#include "FastArrayStack.h"
#include <iostream>

int main(){
  int n = 100;
  ods::FastArrayStack<int> as;
  for (int i = 0; i < n; i++){
    as.add(i, i); 
  }
  as.set(88, 199);
  as.add(87, 133);
  std::cout << as.remove(98) << std::endl;
  for (int i = 0; i < 80; i++){
    std::cout << "removed = " << as.remove(0) << std::endl;
  }
  for (int i = 0; i < as.size(); i++){
    std::cout << "as.get(" << i << ")=" << as.get(i) << std::endl;
  }
  return 0;
}
