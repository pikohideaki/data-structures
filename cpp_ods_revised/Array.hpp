#pragma once

/*
 * Array.h
 *
 *  Created on: 2017-5-15
 *      Author: Hideaki Noshiro
 */

#include <iostream>
#include <cassert>
#include <algorithm>

#include "utils.hpp"


namespace hnlib {


/**
 * A simple array class that simulates Java's arrays implementation - kind of
 * TODO: Make a reference-counted version so that the = operator doesn't have
 * to destroy its right-hand side.
 */

template<class T>
class Array {
 private:
//  protected:
    T*      m_data;
    size_t  m_size;

 public:
    Array() : m_size(0) {
        m_data = new T[1];
    }
    Array( const size_t initSize ) : m_size( initSize ) {
        m_data = new T[initSize];
    }
    Array( const size_t initSize, const T initValue ) : Array( initSize ) {
        std::fill( this->m_data, this->m_data + initSize, initValue );
    }

    Array( const Array<T>& from ) : m_size( from.m_size ) {
        // std::cout << "copy constructor" << std::endl;
        for ( size_t i = 0; i < m_size; ++i ) {
            m_data[i] = from.m_data[i];
        }
    }
    Array( Array<T>&& from ) : m_size( from.m_size ) {
        // std::cout << "move constructor" << std::endl;
        m_data = from.m_data;
        from.m_data = nullptr;
    }

    virtual ~Array() {
        if ( m_data != nullptr ) delete[] m_data;
    }

    Array& operator=( const Array<T>& from ) {
        // std::cout << "copy!" << std::endl;
        m_size = from.m_size;
        for ( size_t i = 0; i < m_size; ++i ) {
            m_data[i] = from.m_data[i];
        }
        return *this;
    }
    Array& operator=( Array<T>&& from ) {
        // std::cout << "move!" << std::endl;
        m_size = from.m_size;
        m_data = from.m_data;
        // from.m_data = nullptr;
        return *this;
    }



    T* data() { return m_data; }
    size_t size()   const { return m_size; }
    size_t length() const { return m_size; }

    T operator[]( const size_t pos ) const {
        return m_data[pos];
    }
    T& operator[]( const size_t pos ) {
        return m_data[pos];
    }
    T at( const size_t pos ) const {
        assert( pos >= 0 && pos < m_size );
        return m_data[pos];
    }
    T& at( const size_t pos ) {
        assert( pos >= 0 && pos < m_size );
        return m_data[pos];
    }


    void fill( const T value ) {
        std::fill( m_data, m_data + m_size, value );
    }

    void swap( Array<T>& b ) {
        using std::swap;
        swap( this->m_data, b.m_data );
        swap( this->m_size, b.m_size );
    }

    // virtual
    void reverse() {
        std::reverse( m_data, m_data + m_size );
    }

    Array<T> makeCopy( const size_t startPos, const size_t endPos ) const {
        Array<T> result( endPos - startPos );
        std::copy( m_data + startPos, m_data + endPos, result.m_data );
using namespace std;
cout << "result = " << result << endl;
cout << "result size = " << result.size() << endl;
        return result;
    }

    template <class S>  friend
    void copyOfRange( Array<S>& to, const Array<S>& from, const size_t startPos, const size_t endPos ) {
        Array<S> result( endPos - startPos );
        std::copy( &(from.m_data[startPos]), &(from.m_data[endPos]), result.m_data );
        to.swap( result );
    }



    template <class S>  friend
    bool operator==( const Array<S>& a1, const Array<S>& a2 ) {
        if ( a1.size() != a2.size() ) return false;
        for ( size_t i = 0; i < a1.size(); ++i ) {
            if ( a1[i] != a2[i] ) return false;
        }
        return true;
    }
    template <class S>  friend
    bool operator!=( const Array<S>& a1, const Array<S>& a2 ) {
        return !(a1 == a2);
    }


    // print
    template <typename S>  friend
    std::ostream& operator<<( std::ostream& ost, const Array<S>& arr ) {
        if ( arr.size() <= 0 ) {
            ost << "[]";
            return ost;
        }
        ost << "[ ";
        for ( size_t i = 0; i < arr.size() - 1; ++i ) {
            ost << arr[i] << ", ";
        }
        ost << arr[ arr.size() - 1 ] << " ]";
        return ost;
    }

};

} /* namespace hnlib */
