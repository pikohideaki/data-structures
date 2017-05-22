#include "BinaryHeap.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
  ods::BinaryHeap<int> pq;
  std::vector<int> vs;
  for(int i = 2; i < 50; i++){
    vs.push_back(i);
  }
  std::random_shuffle(vs.begin(),vs.end());
  for(size_t k = 0; k < vs.size(); k++) pq.add(vs[k]);
  while (pq.size() > 0)
    std::cout << pq.remove() << " ";
  std::cout << std::endl;
}
