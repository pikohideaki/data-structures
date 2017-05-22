// unit test


#include <vector>

#include "Array.hpp"
#include "VariableArray.hpp"

using namespace std;
using namespace hnlib;

int main() {

    VariableArray<int> va(3,1);
    assert( va.size() == 3 and va.capacity() == 3 );
    va.push_back(4);
    assert( va.size() == 4 and va.capacity() == 6 );
    assert( va[0] == 1 and va[3] == 4 );
    cout << va << endl;
    va.reverse();
    cout << va << endl;

    VariableArray<int> va2;
    va2 = va.makeCopy( 0,3 );
    cout << va2 << endl;
    va2[2] = 999;
    va2.push_back(7);
    cout << va2 << endl;
    assert( va2[0] == 4 and va2[1] == 1 and va2[2] == 999 and va2[3] == 7 );
    assert( va2.size() == 4 and va2.capacity() == 6 );
    va2.insert( 4, 888 );
    cout << va2 << endl;

    va.fill(5);
    for ( int i = 0; i < 4; ++i ) { assert( va.at(i) == 5 ); }


    Array<int> ar(10,0);
    cout << ar << endl;
    VariableArray<int> va3;
    // va3.assignFromArray(ar);
    // cout << va3 << endl;


    // VariableArray<int> va5(11,11);
    // va3.insert( 4, 888 );
    // va3.insertAll( 4, va5 );
    // cout << va3 << endl;

    cout << "eof" << endl;
    return 0;
}
