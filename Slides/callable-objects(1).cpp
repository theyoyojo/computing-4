#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>  // Class template std::function
// objects specifically designed to be used with a syntax similar to that of functions. 
// achieved by defining member function operator() in their class

using namespace std;

void printNum(int y) {
	cout << y << endl;
}
struct printnumberclass {
	void operator() (int y) { cout << y << endl; }
} printNumberObj;

void run_within_for_each(std::function<void(int)> func)
{
	vector<int> numbers{ 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };

	for_each(numbers.begin(), numbers.end(), func);
}

int main()
{
	vector<int> numbers{ 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };

	for_each(numbers.begin(), numbers.end(), printNum);
	cout << "-----------------" << endl;
	for_each(numbers.begin(), numbers.end(), printNumberObj);
	cout << "-----------------" << endl;

	for_each(numbers.begin(), numbers.end(), [](int y) 
	{
		cout << y << endl;
	});
	cout << "-----------------" << endl;
	//----------------  lambda capture syntax-----------//
	int divisor = 3;
	for_each(numbers.begin(), numbers.end(), [divisor](int y)
	{
		if (y % divisor == 0)
		{
			cout << y << endl;
		}

	});
	cout << "-----------  [divisor, &sum] ------" << endl;
	int sum = 0;
	// Captures any referenced variable within the lambda by value
	// (making a copy), except sum that has to be captured by reference
	for_each(numbers.begin(), numbers.end(), [divisor, &sum](int y)
	{
		if (y % divisor == 0)
		{
			cout << y << endl;
			sum += y;
		}
	});
	cout << sum << endl;
	cout << "--------------------\n";
	// Passing Lambda Expressions with std::function
	auto func1 = [](int y)
	{
		cout << y << endl;
	};

	auto func2 = [](int z)
	{
		cout << z * 2 << endl;
	};

	run_within_for_each(func1);
	run_within_for_each(func2);

	return 0;
}

