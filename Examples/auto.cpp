// Example of the auto type specifier (Lippman "C++ Primer", section 2.5.2)
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int val1=1, val2=2;
//	float val1=1.5, val2=2;
//	string val1="Hello, ", val2="world!";
	
	// the type of item is deduced from the type of the result of adding val1 and val2
	auto item = val1 + val2; // item initialized to the result of val1 + val2
	
	cout << "item == " << item << endl;
}
