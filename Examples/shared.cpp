#include <iostream>
#include <memory>

using namespace std;


shared_ptr<int> f(shared_ptr<int> x) {
    auto p = make_shared<int>(55);
    
    cout << "In function f: *x == " << *x
		 << ", x.use_count() == " << x.use_count() << endl << endl;
    
    return p; // makes a copy of p
}


int main(void) {
	// The following two declarations are similar, but not equivalent.
	// See the "Notes" section in the following reference
	// for a discussion of the trade-offs:
	// <https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared>
    shared_ptr<int> q(new int(21)); // use value constructor
    auto r = make_shared<int>(42);  // use make_shared function
    
    cout << "After declarations:\n";
    cout << "*q == " << *q << ", *r == " << *r << endl;
	cout << "q.use_count() == " << q.use_count()
		 << ", r.use_count() == " << r.use_count() << endl << endl;
    
    r = q;
    
    cout << "After assignment r=q:\n";
    cout << "*q == " << *q << ", *r == " << *r << endl;
	cout << "q.use_count() == " << q.use_count()
		 << ", r.use_count() == " << r.use_count() << endl << endl;
	
	auto y = f(q); // call-by-value and return-by-value with shared pointers
	
	cout << "After call to function f:\n";
	cout << "*y == " << *y << ", y.use_count() == " << y.use_count() << endl;
    cout << "*q == " << *q << ", *r == " << *r << endl;
	cout << "q.use_count() == " << q.use_count()
		 << ", r.use_count() == " << r.use_count() << endl << endl;
	
	// A deleter is a callable object (in this case, a lambda expression)
	// that takes a single parameter which is of the underlying pointer type
	// of the shared pointer.
	auto myDeleter = [](int* x)
		{ cout << "Shared pointer is being destroyed! (int value == " << *x << ")\n";
		  delete x; };
	
	// Here we use the explicit deleter so that we can see the shared pointer
	// being destroyed!
	// Allocate the underlying pointer using new; destroy using the deleter...
	shared_ptr<int> s(new int(99), myDeleter);
    
    cout << "main() is exiting...\n\n";
    
    return 0;
}
