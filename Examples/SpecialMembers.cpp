#undef MOVE_DEFS // define to use move constructor & move assignment operator
#undef DELETE_OP // define to see effect of deleted operator= in derived class

// Examples of move constructor and assignment operator

#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <cstring> // for memcpy

using namespace std;


// Exception classes for WickedSafeArray
class WSA_uninitialized_exception : exception {
	public:
		virtual const char* what() const noexcept override { return "WickedSafeArray is uninitialized"; }
};

class WSA_out_of_bounds_exception : exception {
	public:
		WSA_out_of_bounds_exception(int index, int size)
			{ message = "WickedSafeArray index ";
			  message += to_string(index);
			  message += " is out of bounds; upper bound is ";
			  message += to_string(size-1);
			}
		virtual const char* what() const noexcept override { return message.c_str(); }
	private:
		string message;
};


// Base class - unchecked index operator
template<class T>
class WickedGoodArray {
    public:
        WickedGoodArray() : size(0), warray(nullptr) {}
        WickedGoodArray(int s) : size(s) { warray = new T[s]; }
		
		virtual ~WickedGoodArray()
		    { cout << "WickedGoodArray destructor called\n"; delete [] warray; }
		    
        WickedGoodArray(const WickedGoodArray<T>&); // copy constructor
		WickedGoodArray<T>& operator= (const WickedGoodArray<T>&); // copy assignment operator
#ifdef MOVE_DEFS		
		WickedGoodArray(WickedGoodArray<T>&&); // move constructor		
		WickedGoodArray<T>& operator= (WickedGoodArray<T>&&); // move assignment operator
#endif		
        virtual T& operator[] (int index) { return warray[index]; } // unchecked index operator

        int getSize() { return size; }
        
    protected:
        T* warray;
        int size;
};

// Derived class - checked index operator
template<class T>
class WickedSafeArray : public WickedGoodArray<T> {
    public:
		WickedSafeArray() : WickedGoodArray<T>() {}
        WickedSafeArray(int s) : WickedGoodArray<T>::WickedGoodArray(s) {}
		WickedSafeArray(const WickedSafeArray<T>& wa) : WickedGoodArray<T>(wa)
			{ cout << "WickedSafeArray copy constructor called\n"; }
			
		WickedSafeArray<T>& operator= (const WickedSafeArray<T>& ws)
		    { cout << "WickedSafeArray copy assignment operator called\n"; WickedGoodArray<T>::operator= (ws); }
#ifdef MOVE_DEFS
#ifdef DELETE_OP
		WickedSafeArray(WickedSafeArray<T>&&) = default; // move constructor		
		WickedSafeArray<T>& operator= (WickedSafeArray<T>&&) = delete; // move assignment operator
#else
        WickedSafeArray(WickedSafeArray<T>&& ws) : WickedGoodArray<T>::WickedGoodArray(std::move(ws))
													// invoke base class move constructor
            { cout << "WickedSafeArray move constructor called\n"; }
			
		WickedSafeArray<T>& operator= (WickedSafeArray<T>&& ws)
		    { cout << "WickedSafeArray move assignment operator called\n";
			  WickedGoodArray<T>::operator= (std::move(ws)); // invoke base class move assignment operator
			  return *this; }
#endif // DELETE_OP
#endif // MOVE_DEFS
        virtual T& operator[] (int index) override; // checked index operator
        
        int getSize() { return WickedGoodArray<T>::size; }
};

// copy constructor implementation
template<typename T>
WickedGoodArray<T>::WickedGoodArray(const WickedGoodArray<T>& w) : size(w.size) {
    this->warray = new T[size];
    memcpy( this->warray, w.warray, sizeof(T)*size );
    cout << "WickedGoodArray copy constructor called\n";
}

// copy assignment operator implementation
template<typename T>
WickedGoodArray<T>& WickedGoodArray<T>::operator= (const WickedGoodArray<T>& w) {
    this->size = w.size;
    this->warray = new T[size];
    memcpy( this->warray, w.warray, sizeof(T)*size );
    cout << "WickedGoodArray copy assignment operator called\n";
    
    return *this;
}

#ifdef MOVE_DEFS
// move constructor implementation
template<typename T>
WickedGoodArray<T>::WickedGoodArray(WickedGoodArray<T>&& w) : size(w.size) {
	this->warray = w.warray;
	w.warray = nullptr;
    cout << "WickedGoodArray move constructor called\n";
}

// move assignment operator implementation
template<typename T>
WickedGoodArray<T>& WickedGoodArray<T>::operator= (WickedGoodArray<T>&& w) {
    this->size = w.size;
	delete [] this->warray;
    this->warray = w.warray;
	w.warray = nullptr;
    cout << "WickedGoodArray move assignment operator called\n";
    
    return *this;
}
#endif

// "safe array" index operator implementation
template<typename T>
T& WickedSafeArray<T>::operator[] (int index) {
	if (WickedGoodArray<T>::warray == nullptr)
		throw WSA_uninitialized_exception();
	
	int s = this->getSize();
	if ( (index < 0) || (index >= s) )
		throw WSA_out_of_bounds_exception(index, s);
	
	return WickedGoodArray<T>::operator[] (index);
}


// A few function declarations to demonstrate copy constructors versus move constructors
WickedGoodArray<int> wgf1 () {
    cout << "wgf1() called\n";
    
    WickedGoodArray<int> w(100);
    w[0] = 20;
    
    cout << "wgf1() returning\n";
	return std::move(w); // invokes move constructor if available
}

WickedGoodArray<int> wgf2 (const WickedGoodArray<int>& w) {
    cout << "wgf2() called and returning\n";
    return w; // invokes copy constructor
}

WickedSafeArray<int> wgf3 () {
    cout << "wgf3() called\n";
    
    WickedSafeArray<int> w(100);
    w[0] = 200;
    
    cout << "wgf3() returning\n";
	return std::move(w); // invokes move constructor if available
}

WickedSafeArray<int> wgf4 (const WickedSafeArray<int>& w) {
    cout << "wgf4() called and returning\n";
    return w; // invokes copy constructor
}


int main (void) {
#ifdef MOVE_DEFS
	cout << "Move constructor and move assignment operator ARE defined!\n\n";
#else
	cout << "Move constructor and move assignment operator are NOT defined!\n\n";
#endif

    WickedGoodArray<int> w1(100);
    w1[0] = 10;
    cout << "w1[0] == " << w1[0] << endl << endl;
    
    WickedGoodArray<int> w2(w1); // invoke copy constructor
    cout << "w2[0] == " << w2[0] << endl << endl;
	
	WickedGoodArray<int> w3;
	w3 = wgf1(); // invoke assignment operator
	cout << "w3[0] == " << w3[0] << endl << endl;

	WickedGoodArray<int> w4;
    w4 = wgf2(w2);
	cout << "w4[0] == " << w4[0] << endl << endl;
	
	WickedSafeArray<int> w5(100);
	w5[0] = 30;
	cout << "w5[0] == " << w5[0] << endl << endl;
	
	WickedSafeArray<int> w6;
	w6 = wgf3();
	cout << "w6[0] == " << w6[0] << endl << endl;

#ifdef DELETE_OP
	WickedGoodArray<int> w7(w5);
#else
	WickedSafeArray<int> w7(w5);
#endif
	w7 = wgf4(w6);
	cout << "w7[0] == " << w7[0] << endl << endl;
	
	// demonstrate checked index operator in WickedSafeArray: uninitialized
	WickedSafeArray<int> w0;
    try {
        cout << "Indexing w0[0], should throw uninitialized exception...\n";
        w0[0] = 100;
    }
	catch (WSA_out_of_bounds_exception& e) {
		cout << "*** Exception: w0 - " << e.what() << endl;
	}
	catch (WSA_uninitialized_exception& e) {
		cout << "*** Exception: w0 - " << e.what() << endl;
	}
	catch (...) {
	    cout << "*** Exception: w0 - Unidentified exception\n";
	}

	// demonstrate checked index operator in WickedSafeArray: out-of-bounds    
	try {
	    cout << "Indexing w5[1000], should throw out-of-bounds exception...\n";
		cout << w5[1000] << endl;
	}
	catch (WSA_out_of_bounds_exception& e) {
		cout << "*** Exception: w5 - " << e.what() << endl;
		exit(-1);
	}
	catch (WSA_uninitialized_exception& e) {
		cout << "*** Exception: w5 - " << e.what() << endl;
		exit(-1);
	}
	catch (...) {
	    cout << "*** Exception: w5 - Unidentified exception\n";
	    exit(-1);
	}

    return 0;
}
