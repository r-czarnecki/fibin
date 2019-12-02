#include "fibin.h"
#include <cstdint>
#include <iostream>

using namespace std; 

template<int N>
class Fib {
public:
    constexpr static unsigned generate() {
        unsigned fs = 0, sn = 1, t;
        if (N < 2)
            return N;
        for (int i=1; i<N; i++) {
            t = sn + fs;
            fs = sn;
            sn = t;
        }
        return t;
    }
};

int main() {
    const unsigned temp = Fib<3>::generate();
    cout << temp << endl;
    
    const bool b = True::generate();
    cout << (b ? "Prawda" : "Falsh") << endl;
}
