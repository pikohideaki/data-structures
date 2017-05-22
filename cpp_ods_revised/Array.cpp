// unit test

#include <cassert>
#include "Array.hpp"

using namespace std;
using namespace hnlib;

int main() {

    Array<int> a1(20,2);
    Array<int> a2(5,0);
    Array<int> a3(20,0);
    Array<int> a4(10,0);
    for ( size_t i = 0; i < a1.size(); ++i ) { a1[i] = i; }
    for ( size_t i = 0; i < a2.size(); ++i ) { a2[i] = i; }
    a1.swap(a2);
    a2.reverse();
    a1.fill(999);
    copyOfRange( a3, a2, 4,12 );
    // a4 = a1.copyOfRange( 0, 10 );
    a1[3] = 4;
    a2[4] = a1.at(3);

    assert( a1.size() == 5  and a1.length() == 5  );
    assert( a2.size() == 20 and a2.length() == 20 );
    assert( a3.size() == 8  and a3.length() == 8  );
    for ( int i = 0; i < 5; ++i ) {
        if ( i == 3 ) { assert( a1[3] == 4 ); }
        else { assert( a1[i] == 999 ); }
    }
    for ( int i = 0; i < 20; ++i ) {
        if ( i == 4 ) { assert( a2[4] == 4 ); }
        else { assert( a2[i] == (19 - i) ); }
    }
    for ( int i = 0; i < 8; ++i ) {
        assert( a3[i] == (15 - i) );
    }

    cout << "a1 = " << a1 << endl;
    cout << "a2 = " << a2 << endl;
    cout << "a3 = " << a3 << endl;
    cout << "a4 = " << a4 << endl;
    a4 = a2.makeCopy( 2, 12 );
    cout << a4 << endl;
    for ( int i = 0; i < 10; ++i ) { cout << a4[i] << ','; }
    cout << a4.size() << endl;

    // Array<int> a5(a4);
    // Array<int> a6(std::move(a4));
    // cout << a5 << endl;
    // cout << a6 << endl;
    // assert( a5 == a6 );

    // Array<int> a8(4,5);
    // Array<int> a9(5,6);
    // a8 = a9;
    // cout << a8 << endl;
    // cout << a9 << endl;

    cout << "eof" << endl;
    return 0;
}
