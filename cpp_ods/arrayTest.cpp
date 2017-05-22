#include "array.h"
#include <iostream>

int main(){
  int n;
  std::cin >> n;
  ods::array<int> a(n);
  for (int i = 0; i < n; i++){
    a[i] = i * i; 
  }
  for (int m; std::cin >> m && m > 0;){
    if (m < n){
      std::cout << a[m] << std::endl;
    }
  }
  return 0;
}
