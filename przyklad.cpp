#include <iostream>
#include <functional>
using namespace std;

class A {
public:
	static int* r;
	constexpr A() {}
};

int n = 2;
int* A::r = &n;

constexpr void f(int* a) {
	*(a) = 4;
}

int main() {
	cout << *(A::r) << endl;
	f(A::r);
	cout << *(A::r) << endl;
}