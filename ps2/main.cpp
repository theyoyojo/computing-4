#include <iostream>
#include "LFSR.hpp"

int main() {
  jsavitz::LFSR test("01101000010", 8) ;

  std::cout << "generate(5) yields value: " << test.generate(5) << std::endl ;
  
  return 0 ;
}
