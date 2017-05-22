/*
 * MyArrayStack.h
 *
 *  Created on: 2011-11-23
 *      Author: morin
 */

#ifndef MYArrayStack_H_
#define MYArrayStack_H_

#include "array.h"
#include "utils.hpp"

namespace ods {

template<class T>
class DualArrayDeque;

template<class T>
class MyArrayStack {
protected:
    friend class DualArrayDeque<T>;
    array<T> a;
    int n;
    virtual void resize();
public:
    MyArrayStack();
    virtual ~MyArrayStack();
    int size();
    T get(int i);
    T set(int i, T x);
    virtual void add(int i, T x);
    virtual void addAll(int i, MyArrayStack<T>& x);
    virtual void add(T x) { add(size(), x); }
    virtual T remove(int i);
    virtual void clear();
};

template<class T> inline
int MyArrayStack<T>::size() {
    return n;
}

template<class T> inline
T MyArrayStack<T>::get(int i) {
    return a[i];
}

template<class T> inline
T MyArrayStack<T>::set(int i, T x) {
    T y = a[i];
    a[i] = x;
    return y;
}

template<class T>
void MyArrayStack<T>::clear() {
    n = 0;
    array<T> b(1);
    a.swap(b);
}

template <class T>
MyArrayStack<T>::MyArrayStack() : a(1) {
    n = 0;
}

template<class T>
MyArrayStack<T>::~MyArrayStack() {
}

template<class T>
void MyArrayStack<T>::resize() {
    array<T> b(max(2 * n, 1));
    for (int i = 0; i < n; i++)
        b[i] = a[i];
    a.swap(b);
}

template<class T>
void MyArrayStack<T>::add(int i, T x) {
    if (n + 1 > a.length) resize();
    for (int j = n; j > i; j--)
        a[j] = a[j - 1];
    a[i] = x;
    n++;
}
template<class T>
void MyArrayStack<T>::addAll(int insertPos, MyArrayStack<T>& x) {
    array<T> b( n + x.size() );

    int it = 0;

    for ( ; it < insertPos; ++it ) {
        b[it] = a[it];
    }
    for ( int i = 0; i < x.size(); i++){
        b[it++] = x.get(i);
    }
    for ( int i = insertPos; i < this->size(); ++i ) {
        b[it++] = a[i];
    }

    a.swap(b);
    n += x.size();
}

template<class T>
T MyArrayStack<T>::remove(int i) {
    T x = a[i];
    for (int j = i; j < n - 1; j++)
        a[j] = a[j + 1];
    n--;
    if (a.length >= 3 * n) resize();
    return x;
}

} /* namespace ods */

#endif /* MyArrayStack_H_ */
