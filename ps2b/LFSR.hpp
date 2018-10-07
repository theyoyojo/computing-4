#ifndef LFSR_HPP
#define LFSR_HPP "LFSR.hpp"

#include <string>

namespace jsavitz {

class LFSR {

public:
    // Constructor that creates the object based on a binary string and integer tap value
    LFSR(std::string seed, int tap) ;

    // Simulate a single step. Returns the new bit (either 0 or 1)
    int step() ;

    // Simulate k steps. Returns a k-bit integer
    int generate(int k) ;

    std::ostream& write(std::ostream& target) const ;

private:

    // Simulate left bitshift operation on object's state
    void shiftLeft() ;

    // Private storage of the tap value. Must be positive
    unsigned int _tap ;

    // The current characters stored in the register
    std::string _state ;

    // The size of the register
    std::string::size_type _length ;

friend std::ostream& operator<<(std::ostream& target, const LFSR& rvalue) {
    return rvalue.write(target) ;
}

} ; // class LFSR


} // namespace jsavitz

#endif // LFSR_HPP