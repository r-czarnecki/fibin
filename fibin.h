#ifndef FIBIN_H
#define FIBIN_H

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