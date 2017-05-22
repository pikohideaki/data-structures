
#include <iostream>
#include <vector>
#include <cassert>

#include "Treque.hpp"


int main() {
    ods::Treque<int> tq;
    for ( int i = 0; i < 20; ++i ) {
        tq.add( i, i );
    }

    tq.add( 3, 111 );
    tq.set( 15, 222 );
    tq.remove(8);

    // print
    std::cout << std::endl;
    for ( int i = 0; i < tq.size(); ++i ) {
        std::cout << tq.get(i) << ", ";
    }
    std::cout << std::endl;

    return 0;
}