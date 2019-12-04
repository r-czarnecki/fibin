#include "fibin.h"
#include <cstdint>
#include <iostream>

using namespace std; 

int main() {
    const unsigned temp = Fib<3>::result;

    static_assert(Fibin<int>::eval<Lit<Fib<4>>>() == 3, "");
    static_assert(Fibin<bool>::eval<Lit<True>>() == true, "");
    static_assert(Fibin<int>::eval<Sum<Lit<Fib<1>>, Lit<Fib<5>>>>() == 6, "");
}
