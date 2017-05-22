#pragma once


#include "ArrayStack.hpp"
#include "utils.hpp"


namespace hnlib {


template<class T>
class RandomQueue {
 protected:
    hnlib::ArrayStack<T> m_arrayStack;
 public:
    RandomQueue() : m_arrayStack() {}

    size_t size() const { return m_arrayStack.size(); }

    void add( const T& value ) { m_arrayStack.add(value); }

    T remove() {  /* select randomly and remove it */
        const size_t randomPos = rand() % size();
        const T returnValue = m_arrayStack.get( randomPos );
        const T last = m_arrayStack.get( m_arrayStack.size() - 1 );
        m_arrayStack.set( randomPos, last );
        m_arrayStack.remove( m_arrayStack.size() - 1 );
        return returnValue;
    }
};

} /* namespace hnlib */
