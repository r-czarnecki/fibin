#include "fibin.h"
#include <cstdint>
#include <iostream>

using namespace std; 

static_assert(Fibin<int>::eval<Lit<Fib<4>>>() == 3, "");
static_assert(Fibin<bool>::eval<Lit<True>>() == true, "");
static_assert(Fibin<int>::eval<Sum<Lit<Fib<1>>, Lit<Fib<5>>>>() == 6, "");
static_assert(Fibin<int>::eval<Inc1<Lit<Fib<5>>>>() == 6, "");
static_assert(Fibin<int>::eval<Inc10<Lit<Fib<10>>>>() == 110, "");
static_assert(Fibin<bool>::eval<Eq<Lit<Fib<10>>, Sum<Lit<Fib<8>>, Lit<Fib<9>>>>>(), "");
static_assert(Fibin<bool>::eval<Eq<Eq<Lit<Fib<10>>, Lit<Fib<1>>>, Lit<False>>>(), "");
static_assert(Fibin<bool>::eval<Let<Var("x"), Lit<Fib<10>>, Eq<Ref<Var("x")>, Lit<Fib<10>>>>>() == true, "");
// const unsigned temp = Fib<3>::result;


// Testy z przykładu
static_assert(1 == Fibin<int16_t>::eval<Let<Var("z"), Lit<Fib<0>>, Inc1<Ref<Var("Z")>>>>(), "");
static_assert(59 == Fibin<uint64_t>::eval<Invoke<Lambda<Var("x"),
              Sum<Ref<Var("x")>, Inc10<Lit<Fib<1>>>, Lit<Fib<2>>>>, Lit<Fib<3>>>>());

static_assert(Fibin<int>::eval<Lit<Fib<1>>, char, 3>() == 1);

static_assert(Fibin<int>::eval< If< Lit<True>, Lit<Fib<4>>, Lit<Fib<2>> > >() == 3, "Error in If true function");
static_assert(Fibin<int>::eval< If< Lit<False>, Lit<Fib<4>>, Lit<Fib<2>> > >() == 1, "Error in If true function");


int main() {
}
