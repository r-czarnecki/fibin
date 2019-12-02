#ifndef FIBIN_H
#define FIBIN_H

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
	, invoke(nullptr) {
		invoke = [] (Fibin& ths, Fibin& arg) -> Fibin& {
			(void)arg;
			return ths;
		};
	}

	constexpr ValueType getValue() const {
		return value;
	}

	ValueType value;
	Fibin& (*invoke)(Fibin&, Fibin&);
};

template<int N>
class Fib {
public:
	constexpr static unsigned generate() {
		unsigned fs = 0, sn = 1, t = 0;
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