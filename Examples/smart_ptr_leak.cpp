// smart pointer memory leak example
#include <iostream>     // std::cout, std::endl
#include <new>          // std::bad_alloc
#include <memory>       // std::shared_ptr
#include <array>        // std::array

using namespace std;


int main () {
    
  const bool useSmartPointers = false;  // *** change to switch between smart and built-in pointers ***
  
  const int mySize = 1000000;
  const int numIterations = 10000; // 10,000 for cpp.sh, VS2015, & g++/Windows; 600,000+ for g++/Linux
  int i = 0;
  
  cout << "Demo of memory leak behavior when using smart pointers versus built-in pointers.\n";
  cout << "***** For this run, we are using "
	   << ((useSmartPointers) ? "smart" : "built-in") << " pointers!\n\n";

  cout << "Allocating std::array of " << mySize << " integers up to " << numIterations << " times:\n";
  
  try
  {
    while (i < numIterations) {
        i++;
        
        if (useSmartPointers) {
            auto myArray = make_shared<array<int, mySize>>();
            
            myArray->at(0) = 1; // avoid warning message for non-use of myArray
            
        }  // myArray goes out of scope; shared_ptr will automatically delete its memory here!
        else {
            auto myArray = new array<int, mySize>;
            
            myArray->at(0) = 1; // avoid warning message for non-use of myArray
            
            // delete myArray; // memory leak if we forget to delete!
        }
    }
  }
  catch (std::bad_alloc& ba)
  {
    cout << "***** bad_alloc caught: " << ba.what() << " after " << i << " allocations\n\n";
  }
  
  cout << "Allocation loop exited after " << i << " allocations (should be "
	   << numIterations << " if no memory leaks!)" << endl;
  
  return 0;
}
