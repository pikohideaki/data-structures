// unit test

#include "ArrayStack.hpp"

using namespace std;
using namespace hnlib;

int main() {

    hnlib::ArrayStack<int> as;
    for ( int i = 0; i < 10; ++i ) { as.add(i); }
    as.add(3,999);
    as.remove(7);
    as.remove(1);
    as.remove(6);
    // cout << as << endl;
    as.clear();
    // cout << as << endl;
    assert( as.size() == 0 );
    assert( as.capacity() == 1 );

    hnlib::ArrayStack<int> as2, as3;
    for ( int i = 0; i < 10; ++i ) { as2.add(i); }
    for ( int i = 0; i < 15; ++i ) { as3.add(i); }
    cout << as2.size() << ',' << as2.capacity() << as2 << endl;
    cout << as3.size() << ',' << as3.capacity() << as3 << endl;
    assert( as2.size() == 10 and as2.capacity() == 16 );
    assert( as3.size() == 15 and as3.capacity() == 16 );

    as2.addAll( 3, as3 );
    cout << as2 << endl;
    cout << as2.size() << endl;
    assert( as2.size() == 25 and as2.capacity() == 32 );
    return 0;
}
