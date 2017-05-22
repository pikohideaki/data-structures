// unit test

#include "RandomQueue.hpp"

using namespace std;
using namespace hnlib;

int main() {
    constexpr int n = 10;

    hnlib::RandomQueue<int> rq;
    for ( int i = 0; i < n; i++ ) {
      rq.add(i);
    }
    for ( int i = 0; i < n; i++ ) {
      std::cout << rq.remove() << ",";
    }
    std::cout << std::endl;

    return 0;
}
