#include "ChainedHashTable.h"

int main(){
  ods::ChainedHashTable<int> primes;
  for(int i = 2; i < 1000; i++){
    primes.add(i);
  }
  // primes = {2,3,4,...,999}
  for(int i = 2; i < 1000; i++){
    if(primes.find(i) == i){
      std::cout << i << std::endl;
      for(int j = i + i; j < 1000; j += i) primes.remove(j);
    }
  }
  // primes = {2,3,5,7,11,...,997}
}
