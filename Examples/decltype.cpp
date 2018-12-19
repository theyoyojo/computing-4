// Examples of decltype type specification (Lippman "C++ Primer", section 2.5.3)
#include <iostream>
#include <string>

using namespace std;

int f() { return 2; }
// float f() { return 2.5; }

int main()
{
	// "magic formula"
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	
	int x1 = 1;
	
	decltype(f()) sum = x1; // sum has whatever type f returns
	
	cout << "x1 == " << x1 << ", sum == " << sum << endl;
	
	const int ci = 0, &cj = ci;
	decltype(ci) x = 0; // x has type const int
	decltype(cj) y = x; // y has type const int& and is bound to x
//	decltype(cj) z;     // error: z is a reference and must be initialized
	
	// decltype of an expression can be a reference type
	int i = 42, *p = &i, &r = i;
	decltype(r + 0) b;  // ok: addition yields an int; b is an (uninitialized) int
//	decltype(*p) c;     // error: c is int& and must be initialized

	// decltype of a parenthesized variable is always a reference
//	decltype((i)) d;    // error: d is int& and must be initialized
	decltype(i) e;      // ok: e is an (uninitialized) int
}
