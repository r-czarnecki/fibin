#ifndef FIBIN_H
#define FIBIN_H

#include <type_traits>
#include <cassert>
using namespace std;

template<typename FIBIN, typename LST, typename ARG>
class Evaluate {};

class ARGNULL {};

//LICZENIE LICZB FIBONACIEGO

template<int N> //Może lepiej zamiast int użyć ValueType z  fibina? Wrzucić do środka i takie tam
class Fib    {
public:
	typedef bool lit;
	static const int result = Fib<N-1>::result + Fib<N-2>::result;
};

template<>
class Fib<1> {
public:
	typedef bool lit;
	static const int result = 1;
};

template<>
class Fib<0> {
public:
	typedef bool lit;
	static const int result = 0;
};

//WARTOŚCI LOGICZNE

class True {
public:
	typedef bool lit;
	static const bool result = true;
};

class False {
public:
	typedef bool lit;
	static const bool result = false;
};

//LISTA - JESZCZE NIE TESTOWANA

class LNULL {
	typedef LNULL Head;
	typedef LNULL Var;
	typedef LNULL Tail;
};

template<typename H, typename V, typename T = LNULL>
class List {
	typedef H Head;
	typedef V Var;
	typedef T Tail;
};

template<typename H, typename V, typename LST>
class Add {
	typedef List<H, V, LST> result;
};

template <typename A, typename B>
class Eq {
	static const bool result = false;
};

template<typename A>
class Eq<A, A> {
	static const bool result = true;
};

template<typename V, typename LST, bool FOUND = false>
class Find {
	typedef Find<V, LST, Eq<V, typename LST::Var>::result> result;
};

template<typename V, typename LST>
class Find<V, LST, false> {
	typedef Find<V, typename LST::Tail, Eq<V, typename LST::Tail::Var>::result> result;
};

template<typename V, typename LST>
class Find<V, LST, true> {
	typedef typename LST::Head result;
};

template<typename V, bool FOUND>
class Find<V, LNULL, FOUND> {
	typedef LNULL result;
};

//LIT

template <typename T, typename T::lit = 0>
class Lit {
public:
	static const unsigned long long value = T::result;
};

template<typename T, typename LST, typename ARG>
class Evaluate<Lit<T>, LST, ARG> {
public:
	typedef Lit<T> result;
};

//VAR

constexpr unsigned long long Var(const char* str) {
	unsigned long long result = 1;
	for(int i = 0; str[i] != '\0'; i++) { 
		char c = str[i];
		if(str[i] >= 'A' && str[i] <= 'Z')
			c += 32;
		
		assert(((void)"Illegal character in Var(const char*)",
			   (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')));
		assert(((void)"Argument in Var(const char*) is too long", i < 6));

		result *= 100;
		result += c;
	}

	return result;
}

//FIBIN

template <typename ValueType>
class Fibin {
public:
	template<typename Expression>
	constexpr static ValueType eval() {
		return Evaluate<Expression, LNULL, ARGNULL>::result::value; 
	}
};

#endif /* FIBIN_H */