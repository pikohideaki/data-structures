#include "BinarySearchTree.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
  int null = -1;
  ods::BinarySearchTree<ods::BSTNode1<int>,int> primes(null);
  std::vector<int> vs;
  for(int i = 2; i < 1000; i++){
    vs.push_back(i);
  }
  std::random_shuffle(vs.begin(),vs.end());
  for(size_t k = 0; k < vs.size(); k++) primes.add(vs[k]);
  std::cout << "Tree height=" << primes.height() << std::endl;
  for(int i = 2; i < 1000; i++){
    if(primes.find(i) == i){
      std::cout << i << std::endl;
      for(int j = i + i; j < 1000; j += i){
        primes.remove(j);
      }
    }
  }
  std::cout << "Tree height=" << primes.height() << std::endl;
  std::cout << "Tree size=" << primes.size() << std::endl;
}
