#include "LFSR.hpp"

using namespace jsavitz ;

// Function to simuate XOR on two bits stored as chars
// Returns either a 0 or 1
// Inputs MUST be either '0' or '1' 
inline char XOR(char a, char b) {
    return a == b ? '0' : '1' ;
}

LFSR::LFSR(std::string seed, int tap) {

    // Validate that seed string contains only 0's and 1's
    for(auto bit : seed) {
        if (bit != '0' && bit != '1') throw "Invalid seed string!" ;
    }

    // Validate that tap is non-negative and less than the seed length
    if (tap < 0 || tap >= seed.length) throw "Tap value out of bounds!" ;

    // Now that everything is in order, initialize the data members
    _state = seed ;
    _tap = tap ;
    _length = seed.length ;
}

int LFSR::step() {
   char tempBit = XOR ()


}