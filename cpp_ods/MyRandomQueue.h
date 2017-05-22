#include "ArrayStack.h"

template<class T>
class MyRandomQueue {
protected:
  ods::ArrayStack<T> as;
public:
  MyRandomQueue();
  int size();
  void add(T x);
  T remove();
};

template <class T>
MyRandomQueue<T>::MyRandomQueue() : as() {
}

template<class T> inline
int MyRandomQueue<T>::size() {
  return as.size();
}

template<class T> inline
void MyRandomQueue<T>::add(T x) {
  as.add(x);
}

template<class T> inline
T MyRandomQueue<T>::remove() {
// replace this function
  const int randomPos = rand() % size();
  const T returnValue = as.get( randomPos );
  const T last = as.get( as.size() - 1 );
  as.set( randomPos, last );
  as.remove(as.size() - 1);
  return returnValue;
}




