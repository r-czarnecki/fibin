#ifndef FIBIN_H
#define FIBIN_H

template<int N> class Fib;

class True {
public:
	constexpr static bool generate() {
		return true;
	}
};

class False {
public:
	constexpr static bool generate() {
		return false;
	}
};


#endif /* FIBIN_H */