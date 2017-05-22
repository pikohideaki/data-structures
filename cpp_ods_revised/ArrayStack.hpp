#pragma once

/*
 * ArrayStack.hpp
 *
 *  Created on: 2017-5-15
 *      Author: Hideaki Noshiro
 */

#include <iostream>

#include "Array.hpp"
#include "utils.hpp"


namespace hnlib {


template<class T>
class ArrayStack {
//  private:
 protected:
    size_t   m_visibleSize;
    Array<T> m_containerArray;

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

 public:
    ArrayStack()
        : m_visibleSize(0)
        , m_containerArray(1)
    {};

    virtual ~ArrayStack() {};

    size_t size()     const { return m_visibleSize; }
    size_t capacity() const { return m_containerArray.size(); }
    T  get( const size_t pos ) const { return m_containerArray[pos]; }
    // T& get( const size_t pos )       { return m_containerArray[pos]; }

    T set( const size_t pos, const T& value ) {
        const T oldValue = m_containerArray[pos];
        m_containerArray[pos] = value;
        return oldValue;
    }

    void add( const size_t insertPos, const T& value ) {
        m_visibleSize++;
        if ( m_visibleSize > m_containerArray.size() ) reserveDouble();
        for ( size_t i = m_visibleSize - 1; i > insertPos; --i ) {
            m_containerArray[i] = m_containerArray[i - 1];
        }
        m_containerArray[insertPos] = value;
    }
    void add( const T& value ) { add( m_visibleSize, value ); }

    void addAll( const size_t insertPos, const ArrayStack<T>& from ) {
        size_t newCapacity = capacity();
        while ( newCapacity < size() + from.size() ) newCapacity *= 2;  /* x2 */
        if ( newCapacity > capacity() ) { reserve( newCapacity ); }
        // copy backward
        int it = m_visibleSize + from.size() - 1;
        for ( int i = size() - 1; i >= static_cast<int>(insertPos); --i ) {
            m_containerArray[it--] = m_containerArray[i];
        }
        for ( int i = from.size() - 1; i >= 0 ; --i ){
            m_containerArray[it--] = from.get(i);
        }
        m_visibleSize += from.size();
    }


    T remove( const size_t pos ) {
        m_visibleSize--;
        const auto removedValue = m_containerArray[pos];
        for ( size_t i = pos; i < m_visibleSize; ++i ) {
            m_containerArray[i] = m_containerArray[i + 1];
        }
        return removedValue;
    }

    void clear() {
        m_visibleSize = 0;
        Array<T> b(1);
        m_containerArray.swap(b);
    }

   // print
    template <typename S>  friend
    std::ostream& operator<<( std::ostream& ost, const ArrayStack<S>& as ) {
        ost << as.m_containerArray.copyOfRange( 0, as.size() );
        ost << '~';
        ost << as.m_containerArray.copyOfRange( as.size(), as.capacity() );
        return ost;
    }

};

} /* namespace hnlib */
