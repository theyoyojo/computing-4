// Our own version of a Smart Pointer class
#include <iostream>
#include <cstddef> // for nullptr_t

using namespace std;


template <typename T> class MySharedPointer; // forward declaration

// creation function : combines allocation and construction functionality
template <typename T>
MySharedPointer<T> make_myShared(T arg) {
    MySharedPointer<T> msp;
    
    msp._count = new unsigned(1);
    msp._ptr = new T (arg);
    
    return msp;
}


template <typename T>
class MySharedPointer {
public:
    // default constructor
    MySharedPointer<T> () : _count(new unsigned(0)), _ptr(nullptr) {}
    
    // value constructor
    MySharedPointer<T> (T* ptr) : _count(new unsigned(1)), _ptr(ptr) {}
    
    // copy constructor
    MySharedPointer<T> (const MySharedPointer<T>& msp) :
        _count(msp._count), _ptr(msp._ptr) { (*_count)++; }
    
    // destructor
    ~MySharedPointer<T> () {
        this->deleter();
    }
    
    // copy assignment operator
    MySharedPointer<T>& operator= (const MySharedPointer<T>& rhs) {
        this->deleter(); // delete original lhs
		this->_count = rhs._count;
		this->_ptr = rhs._ptr;
		(*_count)++;
		return *this;
	}
        
    // pointer dereference operators
    T& operator* () const { return *_ptr; } // returns reference usable in LHS/RHS contexts
    T* operator-> () const { return _ptr; } // returns same value as getPointer()
	
    // accessor functions
    unsigned getCount() const { return *_count; }
    T* getPointer() const { return _ptr; } // returns same value as operator->

// creation function; <> after function name indicates it's a template function
friend MySharedPointer<T> make_myShared<>(T);

// relational operators (declared as friend functions to enable automatic conversions)
friend bool operator== (const MySharedPointer<T>& lhs, const nullptr_t rhs)
	{ return lhs._ptr == rhs; }
friend bool operator== (const nullptr_t lhs, const MySharedPointer<T>& rhs)
	{ return lhs == rhs._ptr; }
friend bool operator!= (const MySharedPointer<T>& lhs, const nullptr_t rhs)
	{ return lhs._ptr != rhs; }
friend bool operator!= (const nullptr_t lhs, const MySharedPointer<T>& rhs)
	{ return lhs != rhs._ptr; }

private:
	// helper function
    void deleter() {
        (*_count)--;
        if (*_count == 0) {
            cout << "MSP == " << *_ptr << " deleted\n";
            delete _ptr;
            _ptr = nullptr; // being paranoid
            delete _count;
            _count = nullptr;
        }
    }
    
	// data members
    unsigned* _count;
    T* _ptr;
};


int main()
{
    MySharedPointer<int> msp1 = make_myShared(100);
    
    cout << "*msp1 == " << *msp1 << ", msp1 count is " << msp1.getCount() << endl;
    
    {
        MySharedPointer<int> msp2(msp1); // uses copy constructor
    
        cout << "\t*msp2 == " << *msp2 << ", msp2 count is " << msp2.getCount()
             << ", msp1 count is " << msp1.getCount() << endl;
    
        {    
            MySharedPointer<int> msp3; // uses default constructor
			
			cout << "\t\tmsp3 == nullptr is " << ((msp3 == nullptr) ? "true" : "false") << " (should be true)\n";
			
            msp3 = msp2; // uses copy assignment operator
    
            cout << "\t\tAfter copy assignment msp3 = msp2...\n";
            
            cout << "\t\t*msp3 == " << *msp3 << ", msp3 count is " << msp3.getCount()
                 << ", msp2 count is " << msp2.getCount()
                 << ", msp1 count is " << msp1.getCount() << endl;
             
        } // end of scope for msp3
    
        cout << "\t*msp2 == " << *msp2 << ", msp2 count is " << msp2.getCount()
             << ", msp1 count is " << msp1.getCount() << endl;
             
    } // end of scope for msp2
    
    cout << "*msp1 == " << *msp1 << ", msp1 count is " << msp1.getCount() << endl << endl;


    MySharedPointer<int> msp4(new int(400)); // uses value constructor
    cout << "*msp4 == " << *msp4 << ", msp4 count is " << msp4.getCount() << endl << endl;
    
    MySharedPointer<int> msp5(new int(500)); // uses value constructor
    cout << "*msp5 == " << *msp5 << ", msp5 count is " << msp5.getCount() << endl << endl;
    
    msp5 = msp4;
    cout << "After copy assignment msp5 = msp4:\n";
    cout << "*msp5 == " << *msp5 << ", msp5 count is " << msp5.getCount() << endl << endl;
	
	*msp4 = 200;
    cout << "After assignment *msp4 = 200:\n";	
    cout << "*msp4 == " << *msp4 << ", msp4 count is " << msp4.getCount() << endl;
    cout << "*msp5 == " << *msp5 << ", msp5 count is " << msp5.getCount() << endl << endl;
    
    
    cout << "End of program, msp5 & msp4 & msp1 go out of scope...\n";
    
    return 0;
}
