#pragma once

/*
 * VariableArray.hpp
 *
 *  Created on: 2017-5-17
 *      Author: Hideaki Noshiro
 */

#include <iostream>
#include <cassert>

#include "Array.hpp"
#include "utils.hpp"


namespace hnlib {


template<class T>
class VariableArray {
 private:
//  protected:
    // friend class Array<T>;
    size_t   m_visibleSize;
    Array<T> m_containerArray;

    void reserveDouble() {
        reserve( m_containerArray.size() << 1 );
    }

 public:
    VariableArray()
        : m_visibleSize(0)
        , m_containerArray(1)
    {};

    VariableArray( const size_t initSize )
        : m_visibleSize( initSize )
        , m_containerArray( initSize )
    {};

    VariableArray( const size_t initSize, const T & initValue )
        : m_visibleSize( initSize )
        , m_containerArray( initSize, initValue )
    {};

    VariableArray( const VariableArray<T> & from )
        : m_visibleSize( from.m_visibleSize )
        , m_containerArray( from.m_containerArray )
    {}
    VariableArray( VariableArray<T> && from )
        : m_visibleSize( from.m_visibleSize )
        , m_containerArray( from.m_containerArray )
    {}


    virtual ~VariableArray() {};


    VariableArray& operator=( const VariableArray<T> & from ) {
        m_visibleSize = from.m_visibleSize;
        m_containerArray = from.m_containerArray;
        return *this;
    }
    VariableArray& operator=( VariableArray<T>&& from ) {
        m_visibleSize = from.m_visibleSize;
        m_containerArray = from.m_containerArray;
        return *this;
    }


    // from hnlib::Array
    void assignFromArray( const Array<T> & from ) {
        m_visibleSize = from.size();
        m_containerArray = from;
    }
    // void assignFromArray( Array<T>&& from ) {
    //     m_visibleSize = from.size();
    //     m_containerArray = from;
    // }


    size_t size()     const { return m_visibleSize; }
    size_t capacity() const { return m_containerArray.size(); }

    T operator[]( const size_t pos ) const {
        return m_containerArray[pos];
    }
    T & operator[]( const size_t pos ) {
        return m_containerArray[pos];
    }
    T at( const size_t pos ) const {
        assert( pos >= 0 and pos < m_visibleSize );
        return m_containerArray[pos];
    }
    T & at( const size_t pos ) {
        assert( pos >= 0 and pos < m_visibleSize );
        return m_containerArray[pos];
    }


    void fill( const T value ) {
        std::fill( m_containerArray.data(), m_containerArray.data() + m_visibleSize, value );
    }

    void swap( VariableArray<T>& b ) {
        using std::swap;
        m_containerArray.swap( b.m_containerArray );
        swap( m_visibleSize, b.m_visibleSize );
    }

    void reverse() {
        std::reverse( m_containerArray.data(), m_containerArray.data() + m_visibleSize );
    }

    VariableArray<T> makeCopy( const size_t startPos, const size_t endPos ) const {
        VariableArray<T> result( endPos - startPos );
        copyOfRange( result.m_containerArray, m_containerArray, startPos, endPos );
        return result;
        // return VariableArray<T>( m_containerArray.copyOfRange( startPos, endPos ) );
    }



    void reserve( const size_t newCapacity ) {
        if ( newCapacity <= 1 or newCapacity <= m_containerArray.size() ) return;
        Array<T> newArray( newCapacity );
        for ( size_t i = 0; i < size(); ++i ) {
            newArray[i] = m_containerArray[i];
        }
        m_containerArray.swap(newArray);
    }

    void insert( const size_t insertPos, const T& value ) {
        assert( 0 <= insertPos and insertPos <= size() );

        m_visibleSize++;
        if ( m_visibleSize > m_containerArray.size() ) reserveDouble();
        for ( size_t i = m_visibleSize - 1; i > insertPos; --i ) {
            m_containerArray[i] = m_containerArray[i - 1];
        }
        m_containerArray[insertPos] = value;
    }
    void push_back( const T& value ) { insert( m_visibleSize, value ); }

    void insertAll( const size_t insertPos, const VariableArray<T>& from ) {
        assert( 0 <= insertPos and insertPos <= size() );

std::cout << 1 << std::endl;
        size_t newCapacity = capacity();
        while ( newCapacity < size() + from.size() ) newCapacity *= 2;  /* x2 */
std::cout << 2 << std::endl;
        if ( newCapacity > capacity() ) { reserve( newCapacity ); }
        // copy backward
        int it = m_visibleSize + from.size() - 1;
std::cout << 3 << std::endl;
        for ( int i = size() - 1; i >= static_cast<int>(insertPos); --i ) {
            m_containerArray[it--] = m_containerArray[i];
        }
std::cout << 4 << std::endl;
        for ( int i = from.size() - 1; i >= 0 ; --i ){
            m_containerArray[it--] = from[i];
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



    template <class S>  friend
    bool operator==( const VariableArray<S>& a1, const VariableArray<S>& a2 ) {
        if ( a1.size() != a2.size() ) return false;
        for ( size_t i = 0; i < a1.size(); ++i ) {
            if ( a1[i] != a2[i] ) return false;
        }
        return true;
    }
    template <class S>  friend
    bool operator!=( const VariableArray<S>& a1, const VariableArray<S>& a2 ) {
        return !(a1 == a2);
    }

   // print
    template <typename S>  friend
    std::ostream& operator<<( std::ostream& ost, const VariableArray<S>& va ) {
        ost << va.m_containerArray.makeCopy( 0, va.size() );
        ost << '~';
        ost << va.m_containerArray.makeCopy( va.size(), va.capacity() );
        return ost;
    }

};

} /* namespace hnlib */
