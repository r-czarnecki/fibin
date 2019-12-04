#ifndef FIBIN_H
#define FIBIN_H

#include <type_traits>
#include <cassert>
using namespace std;

template<typename FIBIN, typename LST, typename ARG>
struct Evaluate {};

struct ARGNULL {};

//LICZENIE LICZB FIBONACIEGO

template<int N> //Może lepiej zamiast int użyć ValueType z  fibina? Wrzucić do środka i takie tam
struct Fib    {
	typedef bool lit;
	static const int result = Fib<N-1>::result + Fib<N-2>::result;
	static const bool isBoolean = false;
};

template<>
struct Fib<1> {
	typedef bool lit;
	static const int result = 1;
	static const bool isBoolean = false;
};

template<>
struct Fib<0> {
	typedef bool lit;
	static const int result = 0;
	static const bool isBoolean = false;
};

//WARTOŚCI LOGICZNE

struct True {
	typedef bool lit;
	static const bool result = true;
	static const bool isBoolean = true;
};

struct False {
	typedef bool lit;
	static const bool result = false;
	static const bool isBoolean = true;
};

//LISTA - JESZCZE NIE TESTOWANA

struct LNULL {
	typedef LNULL Head;
	typedef LNULL Tail;
	static const unsigned long long Var;
};

template<typename H, unsigned long long V, typename T = LNULL>
struct List {
	typedef H Head;
	typedef T Tail;
	static const unsigned long long Var = V;
};

template<typename H, unsigned long long V, typename LST>
struct PushFront {
	typedef List<H, V, LST> result;
};

// template <typename A, typename B>
// struct Equals {
// 	static const bool result = false;
// };

// template<typename A>
// struct Equals<A, A> {
// 	static const bool result = true;
// };

template<unsigned long long V, typename LST, bool FOUND = false, bool INIT = true>
struct Find {
	typedef typename Find<V, LST, (V == LST::Var), false>::result result;
};

template<unsigned long long V, typename LST>
struct Find<V, LST, false, false> {
	typedef typename Find<V, typename LST::Tail, (V == LST::Tail::Var)>::result result;
};

template<unsigned long long V, typename LST>
struct Find<V, LST, true, false> {
	typedef typename LST::Head result;
};

template<unsigned long long V, bool FOUND, bool INIT>
struct Find<V, LNULL, FOUND, INIT> {
	typedef LNULL result;
};

//LIT

template <typename T, typename T::lit = 0>
struct Lit {
	static const unsigned long long value = T::result;
	static const bool isBoolean = T::isBoolean;
};

template<typename LST, typename ARG, typename T>
struct Evaluate<Lit<T>, LST, ARG> {
	typedef Lit<T> result;
};

//SUM

template<typename FIRST, typename SECOND, typename... ARGS>
struct Sum {
};

template<typename LST, typename ARG, typename FIRST, typename... ARGS>
struct Add {
	static const unsigned long long int value = Add<LST, ARG, FIRST>::value + Add<LST, ARG, ARGS...>::value;
	static const bool isBoolean = false;
};

template<typename LST, typename ARG, typename FIRST>
struct Add<LST, ARG, FIRST> {
	static_assert(!FIRST::isBoolean, "");
	static const unsigned long long int value = Evaluate<FIRST, LST, ARG>::result::value;
};

template<typename LST, typename ARG, typename FIRST, typename SECOND, typename... ARGS>
struct Evaluate<Sum<FIRST, SECOND, ARGS...>, LST, ARG> {
	typedef Add<LST, ARG, FIRST, SECOND, ARGS...> result;
};

//Inc1

template<typename INCARG, typename LST, typename ARG>
struct Inc1Helper {
	static const unsigned long long int value = Evaluate<Sum<INCARG, Lit<Fib<1>>>, LST, ARG>::result::value;
	static const bool isBoolean = false;
};
 
template<typename ARG>
struct Inc1 {};

template<typename LST, typename ARG, typename INCARG>
struct Evaluate<Inc1<INCARG>, LST, ARG> {
	typedef Inc1Helper<INCARG, LST, ARG> result;
};

//Inc10

template<typename INCARG, typename LST, typename ARG>
struct Inc10Helper {
	static const unsigned long long int value = Evaluate<Sum<INCARG, Lit<Fib<10>>>, LST, ARG>::result::value;
	static const bool isBoolean = false;
};

template<typename ARG>
struct Inc10 {};

template<typename LST, typename ARG, typename INCARG>
struct Evaluate<Inc10<INCARG>, LST, ARG> {
	typedef Inc10Helper<INCARG, LST, ARG> result;
};

//EQ

template<unsigned long long LVAL, unsigned long long RVAL, bool LTYPE, bool RTYPE>
struct EqResult {
	typedef Lit<False> result;
};

template<unsigned long long VAL, bool TYPE>
struct EqResult<VAL, VAL, TYPE, TYPE> {
	typedef Lit<True> result;
};

template<typename LEFT, typename RIGHT, typename LST, typename ARG>
struct EqHelper {
	typedef typename Evaluate<LEFT, LST, ARG>::result ELEFT;
	typedef typename Evaluate<RIGHT, LST, ARG>::result ERIGHT;
	typedef typename EqResult<ELEFT::value, ERIGHT::value, ELEFT::isBoolean, ERIGHT::isBoolean>::result result;
};

template<typename LEFT, typename RIGHT>
struct Eq {};

template<typename LST, typename ARG, typename LEFT, typename RIGHT>
struct Evaluate<Eq<LEFT, RIGHT>, LST, ARG> {
	typedef typename EqHelper<LEFT, RIGHT, LST, ARG>::result result;
};

//REF

template<unsigned long long VAR, typename LST>
struct RefHelper {
	typedef typename Find<VAR, LST>::result result;
};

template<unsigned long long VAR>
struct Ref {};

template<typename LST, typename ARG, unsigned long long VAR>
struct Evaluate<Ref<VAR>, LST, ARG> {
	typedef typename RefHelper<VAR, LST>::result result;
	static_assert(!is_same<result, LNULL>::value, "");
};

//IF - Zakomentowane, bo się nie kompiluje

// template<typename _TRUE, typename _FALSE>
// struct IfHelper<true>
// {
// 	typedef _TRUE::result result;
// };

// template<typename _TRUE, typename _FALSE>
// struct IfHelper<false>
// {
// 	typedef _FALSE::result result;
// };

// // ROZWIĄZENIE ALTERNATYWNE – WYMAGA PRZEPISANIA POZOSTAŁEJ CZĘŚCI

// // template<typename _TRUE, typename _FALSE>
// // struct IfHelper<Lit<True>>
// // {
// // 	typedef _TRUE::result result;
// // };

// // template<typename _TRUE, typename _FALSE>
// // struct IfHelper<Lit<False>>
// // {
// // 	typedef _FALSE::result result;
// // };

// template<typename _BOOL, typename _TRUE, typename _FALSE>
// struct If { //TRZEBA OGARNĄĆ PRZYPADEK GDY BOOL JEST NIE BOOLEM
//   typedef IfHelper<_BOOL::result><_TRUE, _FALSE>::result result; 
// };


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
struct Fibin {
	template<typename Expression>
	constexpr static ValueType eval() {
		return Evaluate<Expression, LNULL, ARGNULL>::result::value; 
	}
};

#endif /* FIBIN_H */