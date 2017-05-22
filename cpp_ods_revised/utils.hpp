#pragma once

namespace hnlib {

template<typename T> 
inline max( const T& x, const T& y ) {
  return ( x > y ? x : y );
}

}