#include "fibin.h"
#include <cstdint>
#include <iostream>

using namespace std; 

int main() {
    const unsigned temp = Fib<3>::result;
    cout << temp << endl;
    
}
