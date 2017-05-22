#pragma once


#include "ArrayDeque.h"

namespace hnlib {

constexpr BalancingThreshold = 3;

template<class T>
class Treque {
protected:
    ArrayDeque<T> front;
    ArrayDeque<T> back;
    void balance();
public:
    Treque();
    virtual ~Treque();
    int size();
    T get(int i);
    T set(int i, T x);
    virtual void add(int i, T x);
    virtual T remove(int i);
    virtual void clear();
};

template<class T> inline
T Treque<T>::get(int i) {
    if (i < front.size()) {
        return front.get(front.size() - i - 1);
    } else {
        return back.get(i - front.size());
    }
}

template<class T> inline
T Treque<T>::set(int i, T x) {
    if (i < front.size()) {
        return front.set(front.size() - i - 1, x);

    } else {
        return back.set(i - front.size(), x);
    }
}

template<class T>
Treque<T>::Treque() {
}

template<class T>
Treque<T>::~Treque() {
}

template<class T>
int Treque<T>::size() {
    return front.size() + back.size();
}

template<class T>
void Treque<T>::add(int i, T x) {
    if (i < front.size()) {
        front.add(front.size() - i, x);
    } else {
        back.add(i - front.size(), x);
    }
    balance();
}

template<class T>
T Treque<T>::remove(int i) {
    T x;
    if (i < front.size()) {
            x = front.remove(front.size()-i-1);
    } else {
            x = back.remove(i-front.size());
    }
    balance();
    return x;
}

template<class T>
void Treque<T>::balance() {
    if ( !(BalancingThreshold * front.size() < back.size()
        || BalancingThreshold * back.size()  < front.size()) ) return;

    int n = front.size() + back.size();
    int nf = n/2;
    array<T> af( max(2 * nf, 1) );
    for ( int i = 0; i < nf; i++ ) {
        af[nf - i - 1] = get(i);
    }
    int nb = n - nf;
    array<T> ab( max(2 * nb, 1) );
    for ( int i = 0; i < nb; i++ ) {
        ab[i] = get(nf + i);
    }
    front.a.swap(af);
    front.n = nf;
    back.a.swap(ab);
    back.n = nb;
}

template<class T>
void Treque<T>::clear() {
    front.clear();
    back.clear();
}

} /* namespace hnlib */
