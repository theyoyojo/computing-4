#include <iostream>
#include "LFSR.hpp"

using namespace jsavitz ;

int main() {

  jsavitz::LFSR test("01101000010", 8) ;

  int temp ;
  for(int i = 0; i < 10; i++) {
    temp = test.generate(5) ;
    std::cout << test << " " << temp << std::endl ;
  }

  
  return 0 ;
}
