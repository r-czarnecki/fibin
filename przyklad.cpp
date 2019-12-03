#include <iostream>
#include <functional>
using namespace std;

class A {
public:
	static int r;
	A() {}
};

int A::r = 2;

constexpr void f() {
	A::r = 4;
}

int main() {
	cout << A::r << endl;
	f();
	cout << A::r << endl;
}