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
	static const bool isBoolean = false;
};

template<>
class Fib<1> {
public:
	typedef bool lit;
	static const int result = 1;
	static const bool isBoolean = false;
};

template<>
class Fib<0> {
public:
	typedef bool lit;
	static const int result = 0;
	static const bool isBoolean = false;
};

//WARTOŚCI LOGICZNE

class True {
public:
	typedef bool lit;
	static const bool result = true;
	static const bool isBoolean = true;
};

class False {
public:
	typedef bool lit;
	static const bool result = false;
	static const bool isBoolean = true;
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
class PushFront {
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
	static const bool isBoolean = T::isBoolean;
};

template<typename LST, typename ARG, typename T>
class Evaluate<Lit<T>, LST, ARG> {
public:
	typedef Lit<T> result;
};

//SUM

template<typename FIRST, typename SECOND, typename... ARGS>
class Sum {
};

template<typename LST, typename ARG, typename FIRST, typename... ARGS>
class Add {
public:
	static const unsigned long long int value = Add<LST, ARG, FIRST>::value + Add<LST, ARG, ARGS...>::value;
	static const bool isBoolean = false;
};

template<typename LST, typename ARG, typename FIRST>
class Add<LST, ARG, FIRST> {
public:
	static_assert(!FIRST::isBoolean, "");
	static const unsigned long long int value = Evaluate<FIRST, LST, ARG>::result::value;
};

template<typename LST, typename ARG, typename FIRST, typename SECOND, typename... ARGS>
class Evaluate<Sum<FIRST, SECOND, ARGS...>, LST, ARG> {
public:
	typedef Add<LST, ARG, FIRST, SECOND, ARGS...> result;
};

//Inc1

template<typename ARG>
class Inc1 {
public:
	static const unsigned long long int value = Evaluate<Sum<ARG, Lit<Fib<1>>>, LNULL, ARGNULL>::result::value;
};

template<typename LST, typename ARG, typename INCARG>
class Evaluate<Inc1<INCARG>, LST, ARG> {
public:
	typedef Inc1<INCARG> result;
};

//Inc10

template<typename ARG>
class Inc10 {
public:
	static const unsigned long long int value = Evaluate<Sum<ARG, Lit<Fib<10>>>, LNULL, ARGNULL>::result::value;
};

template<typename LST, typename ARG, typename INCARG>
class Evaluate<Inc10<INCARG>, LST, ARG> {
public:
	typedef Inc10<INCARG> result;
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