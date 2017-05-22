#include "utils.h"
#include "LinearHashTable.h"

int main(){
  const int null = -1;
  const int del = -2;
  ods::LinearHashTable<int> primes(null, del);
  for(int i = 2; i < 1000; i++){
    primes.add(i);
  }
  // primes = {2,3,4,...,999}
  for(int i = 2; i < 1000; i++){
    if(primes.find(i) != null){
      std::cout << i << std::endl;
      for(int j = i + i; j < 1000; j += i) primes.remove(j);
    }
  }
  // primes = {2,3,5,7,11,...,997}
}
