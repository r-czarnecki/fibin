#ifndef FIBIN_H
#define FIBIN_H

#include <type_traits>
#include <cassert>
using namespace std;

template <typename ValueType>
class Fibin {
public:
	template<typename Expression>
	constexpr static ValueType eval() {
		return Expression().invoke().getValue();
	}

protected:
	constexpr Fibin()
	: value(0)
	, invoke(nullptr)
	, hasValue(false) {
		invoke = [] (Fibin& ths, Fibin& arg) -> Fibin& {
			(void)arg;
			return ths;
		};
	}

	constexpr ValueType getValue() const {
		static_assert(hasValue, "Object does not have any value");

		return value;
	}

	ValueType value;
	Fibin& (*invoke)(Fibin&, Fibin&);
	bool hasValue;
};

//LICZENIE LICZB FIBONACIEGO

template<int N> //Może lepiej zamiast int użyć ValueType z  fibina? Wrzucić do środka i takie tam
class Fib    {
public:
	static const int result = Fib<N-1>::result + Fib<N-2>::result;
};

template<>
class Fib<1> {
public:
	static const int result = 1;
}

template<>
class Fib<0> {
public:
	static const int result = 0;
}

//WARTOŚCI LOGICZNE

class True {};
class False {};


template <typename T, typename T::lit = 0>
class Lit : public Fibin<unsigned long long> {
	constexpr Lit() 
	: Fibin() {
		hasValue = true; 
		value = T::generate();
	}
};

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

#endif /* FIBIN_H */