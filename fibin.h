#ifndef FIBIN_H
#define FIBIN_H

#include <type_traits>
#include <cassert>
#include <iostream>
using namespace std;

template<typename FIBIN, typename LST, typename ARG, typename TYPE>
struct Evaluate {
};

struct ARGNULL {};

//LICZENIE LICZB FIBONACIEGO

template<unsigned short N> 
struct Fib    {
	typedef bool lit; // Ensures that only structs with lit type defined can be template parameter of Lit
	static const unsigned long long result = Fib<N-1>::result + Fib<N-2>::result;
	static const bool isBoolean = false;
};

template<>
struct Fib<1> {
	typedef bool lit;
	static const unsigned long long result = 1;
	static const bool isBoolean = false;
};

template<>
struct Fib<0> {
	typedef bool lit;
	static const unsigned long long result = 0;
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
	static const unsigned long long Var = 0;
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

template <typename T, typename TYPE = unsigned long long, typename T::lit = 0>
struct Lit {
	static const TYPE value = T::result;
	static const bool isBoolean = T::isBoolean;
};

template<typename LST, typename ARG, typename T, typename TYPE, typename TYPE2>
struct Evaluate<Lit<T, TYPE2>, LST, ARG, TYPE> {
	typedef Lit<T, TYPE> result;
};

//SUM

template<typename FIRST, typename SECOND, typename... ARGS>
struct Sum {
};

template<typename LST, typename ARG, typename TYPE, typename FIRST, typename... ARGS>
struct Add {
	static const TYPE value = Add<LST, ARG, TYPE, FIRST>::value + Add<LST, ARG, TYPE, ARGS...>::value;
	static const bool isBoolean = false;
};

template<typename LST, typename ARG, typename TYPE, typename FIRST>
struct Add<LST, ARG, TYPE, FIRST> {
	typedef typename Evaluate<FIRST, LST, ARG, TYPE>::result EVAL;
	static_assert(!EVAL::isBoolean, "");
	static const TYPE value = EVAL::value;
};

template<typename LST, typename ARG, typename TYPE, typename FIRST, typename SECOND, typename... ARGS>
struct Evaluate<Sum<FIRST, SECOND, ARGS...>, LST, ARG, TYPE> {
	typedef Add<LST, ARG, TYPE, FIRST, SECOND, ARGS...> result;
};

template<typename LST, typename ARG, typename TYPE, typename FIRST, typename... ARGS, typename LST2, typename ARG2>
struct Evaluate<Add<LST, ARG, TYPE, FIRST, ARGS...>, LST2, ARG2, TYPE> {
	typedef Add<LST, ARG, TYPE, FIRST, ARGS...> result;
};

//Inc1

template<typename INCARG, typename LST, typename ARG, typename TYPE>
struct Inc1Helper {
	static const TYPE value = Evaluate<Sum<INCARG, Lit<Fib<1>>>, LST, ARG, TYPE>::result::value;
	static const bool isBoolean = false;
};
 
template<typename ARG>
struct Inc1 {};

template<typename LST, typename ARG, typename INCARG, typename TYPE>
struct Evaluate<Inc1<INCARG>, LST, ARG, TYPE> {
	typedef Inc1Helper<INCARG, LST, ARG, TYPE> result;
};

template<typename LST, typename ARG, typename TYPE, typename INCARG>
struct Evaluate<Inc1Helper<INCARG, LST, ARG, TYPE>, LST, ARG, TYPE> {
	typedef Inc1Helper<INCARG, LST, ARG, TYPE> result;
};

//Inc10

template<typename INCARG, typename LST, typename ARG, typename TYPE>
struct Inc10Helper {
	static const TYPE value = Evaluate<Sum<INCARG, Lit<Fib<10>>>, LST, ARG, TYPE>::result::value;
	static const bool isBoolean = false;
};

template<typename ARG>
struct Inc10 {};

template<typename LST, typename ARG, typename INCARG, typename TYPE>
struct Evaluate<Inc10<INCARG>, LST, ARG, TYPE> {
	typedef Inc10Helper<INCARG, LST, ARG, TYPE> result;
};

template<typename LST, typename ARG, typename INCARG, typename TYPE>
struct Evaluate<Inc10Helper<INCARG, LST, ARG, TYPE>, LST, ARG, TYPE> {
	typedef Inc10Helper<INCARG, LST, ARG, TYPE> result;
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

template<typename LEFT, typename RIGHT>
struct Eq {};

template<typename LST, typename ARG, typename TYPE, typename LEFT, typename RIGHT>
struct Evaluate<Eq<LEFT, RIGHT>, LST, ARG, TYPE> {
	typedef typename Evaluate<LEFT, LST, ARG, TYPE>::result ELEFT;
	typedef typename Evaluate<RIGHT, LST, ARG, TYPE>::result ERIGHT;
	typedef typename EqResult<ELEFT::value, ERIGHT::value, ELEFT::isBoolean, ERIGHT::isBoolean>::result result;
};

//REF

template<unsigned long long VAR>
struct Ref {};

template<typename LST, typename ARG, typename TYPE, unsigned long long VAR>
struct Evaluate<Ref<VAR>, LST, ARG, TYPE> {
	typedef typename Find<VAR, LST>::result FOUND;
	static_assert(!is_same<FOUND, LNULL>::value, "");
	typedef typename Evaluate<FOUND, LST, ARG, TYPE>::result result;
};

//LET

template<unsigned long long VAR, typename VALUE, typename EXPRESSION>
struct Let {};

template<typename LST, typename ARG, typename TYPE, unsigned long long VAR, typename VALUE, typename EXPRESSION>
struct Evaluate<Let<VAR, VALUE, EXPRESSION>, LST, ARG, TYPE> {
	typedef typename Evaluate<VALUE, LST, ARGNULL, TYPE>::result VAL;
	typedef typename PushFront<VAL, VAR, LST>::result NEWLST;
	typedef typename Evaluate<EXPRESSION, NEWLST, ARG, TYPE>::result result;
};

//IF

template<bool CONDITION, typename THEN, typename ELSE, typename LST, typename ARG, typename TYPE>
struct IfHelper {
	typedef typename Evaluate<THEN, LST, ARG, TYPE>::result result;
};

template<typename THEN, typename ELSE, typename LST, typename ARG, typename TYPE>
struct IfHelper<false, THEN, ELSE, LST, ARG, TYPE> {
	typedef typename Evaluate<ELSE, LST, ARG, TYPE>::result result;
};

template<typename CONDITION, typename THEN, typename ELSE>
struct If {};

template<typename LST, typename ARG, typename TYPE, typename CONDITION, typename THEN, typename ELSE>
struct Evaluate<If<CONDITION, THEN, ELSE>, LST, ARG, TYPE> {
	typedef typename Evaluate<CONDITION, LST, ARG, TYPE>::result COND;
	static const bool cond = COND::value;
	static_assert(COND::isBoolean, "");
	typedef typename IfHelper<cond, THEN, ELSE, LST, ARG, TYPE>::result result;
};

//LAMBDA

template<unsigned long long VAR, typename BODY, typename LST = LNULL, bool hasLST = false>
struct Lambda {};

template<typename LST, typename TYPE, unsigned long long VAR, typename BODY, typename LST2>
struct Evaluate<Lambda<VAR, BODY, LST2, false>, LST, ARGNULL, TYPE> {
	typedef Lambda<VAR, BODY, LST, true> result;
};

template<typename LST, typename ARG, typename TYPE, unsigned long long VAR, typename BODY, typename LST2>
struct Evaluate<Lambda<VAR, BODY, LST2, false>, LST, ARG, TYPE> {
	typedef typename PushFront<ARG, VAR, LST>::result NEWLST;
	typedef typename Evaluate<BODY, NEWLST, ARGNULL, TYPE>::result result;
};

template<typename LST, typename TYPE, unsigned long long VAR, typename BODY, typename LST2>
struct Evaluate<Lambda<VAR, BODY, LST2, true>, LST, ARGNULL, TYPE> {
	typedef Lambda<VAR, BODY, LST2, true> result;
};

template<typename LST, typename ARG, typename TYPE, unsigned long long VAR, typename BODY, typename LST2>
struct Evaluate<Lambda<VAR, BODY, LST2, true>, LST, ARG, TYPE> {
	typedef typename PushFront<ARG, VAR, LST2>::result NEWLST;
	typedef typename Evaluate<BODY, NEWLST, ARGNULL, TYPE>::result result;
};

//INVOKE

template<typename FUN, typename PARAM>
struct Invoke {};

template<typename LST, typename ARG, typename TYPE, typename FUN, typename PARAM>
struct Evaluate<Invoke<FUN, PARAM>, LST, ARG, TYPE> {
	typedef typename Evaluate<FUN, LST, ARG, TYPE>::result EFUN;
	typedef typename Evaluate<PARAM, LST, ARG, TYPE>::result PAR;
	typedef typename Evaluate<EFUN, LST, PAR, TYPE>::result result;
};

//VAR

constexpr unsigned long long Var(const char* str) {
	unsigned long long result = 1;
	char c = 0;
	for(int i = 0; str[i] != '\0'; i++) { 
		c = str[i];
		if(str[i] >= 'A' && str[i] <= 'Z')
			c += 32;
		// cout << c << endl;
		
		assert(((void)"Illegal character in Var(const char*)",
			   (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')));
		assert(((void)"Argument in Var(const char*) is too long", i < 6));

		if(c >= '0' && c <= '9')
			c -= '0';
		else
			c = 11 + c - 'a';

		result *= 100;
		result += c;
	}

	return result;
}

//FIBIN

template <typename ValueType>
struct Fibin {
	template<typename Expression, typename T = ValueType, typename enable_if<is_integral<T>::value, int>::type = 0>
	constexpr static ValueType eval() {
		return Evaluate<Expression, LNULL, ARGNULL, ValueType>::result::value; 
	}

	template<typename Expression, typename T = ValueType, typename enable_if<!is_integral<T>::value, int>::type = 0>
	constexpr static void eval() {
		cout << "Fibin doesn't support: " << typeid(ValueType).name() << "\n";
	}
};

#endif /* FIBIN_H */