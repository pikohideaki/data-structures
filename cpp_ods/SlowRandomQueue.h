#include "ArrayStack.h"

template<class T>
class SlowRandomQueue {
protected:
  ods::ArrayStack<T> as;
public:
  SlowRandomQueue();
  int size();
  void add(T x);
  T remove();
};

template <class T>
SlowRandomQueue<T>::SlowRandomQueue() : as() {
}

template<class T> inline
int SlowRandomQueue<T>::size() {
  return as.size();
}

template<class T> inline
void SlowRandomQueue<T>::add(T x) {
  as.add(x);
}

template<class T> inline
T SlowRandomQueue<T>::remove() {
  int i = rand() % size();
  return as.remove(i);
}




