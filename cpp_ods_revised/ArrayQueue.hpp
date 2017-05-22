#pragma once

/*
 * ArrayQueue.hpp
 *
 *  Created on: 2017-5-17
 *      Author: Hideaki Noshiro
 */

#include <iostream>

#include "Array.hpp"
#include "utils.hpp"


namespace hnlib {


template<class T>
class ArrayQueue {
 protected:
    size_t   m_visibleSize;
    Array<T> m_containerArray;
 public:
    void reserve( const size_t newCapacity ) {
        if ( newCapacity <= 1 or newCapacity <= m_containerArray.size() ) return;
        Array<T> newArray( newCapacity );
        for ( size_t i = 0; i < size(); ++i ) {
            newArray[i] = m_containerArray[i];
        }
        m_containerArray.swap(newArray);
    }
    void reserveDouble() {
        reserve( m_containerArray.size() << 1 );
    }

};

} /* namespace hnlib */
