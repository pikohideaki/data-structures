#include "DLList.h"
#include <iostream>

void print(std::ostream& os, ods::DLList<int> & l){
  os << "[";
  for (int i = 0; i < l.size(); ++i){
    os << (i == 0 ? "" : ",") << l.get(i);
  }
  os << "]" << std::endl;
}

int main(){
  ods::DLList<int> l;
  for (int i = 0; i < 10; i++){
    l.add(i, i * 2);
  }
  // l = [0,2,4,6,8,10,12,14,16,18]
  print(std::cerr, l); 
  for (int i = 0; i < 10; i++){
    l.add(5, 100 + i);
  }
  // l = [0,2,4,6,8,109,108,107,106,105,104,103,102,101,100,10,12,14,16,18]
  print(std::cerr, l); 
  for (int i = 0; i < 10; i++){
    l.set(i * 2, 200 + i);
  }
  // l = [200,2,201,6,202,109,203,107,204,105,205,103,206,101,207,10,208,14,209,18]
  print(std::cerr, l); 
  l.remove(1);
  // l = [200,201,6,202,109,203,107,204,105,205,103,206,101,207,10,208,14,209,18]
  print(std::cerr, l); 
  return 0;
}
  
