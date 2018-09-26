#include "LFSR.hpp"
#include <vector>
#include <math.h>
#include <iostream>

using namespace jsavitz ;

// Function to simuate XOR on two bits stored as chars
// Returns either a 0 or 1
// Inputs MUST be either '0' or '1' 
inline char XOR(char a, char b) {
    return a == b ? '0' : '1' ;
}

// Convert a binary value represented as a vector of characters (least->most significant) to an binaryCharVectorToInteger
// Input vector<char> MUST contain only '0's and '1's
int binaryCharVectorToInteger(const std::vector<char>& binaryCharVector ) {
    int integer = 0 ;

    for(int i = 0; i < (int) binaryCharVector.size(); ++i) {
        integer += binaryCharVector[i] == '1' ? pow(2,(double)binaryCharVector.size() - i - 1) : 0 ;
    }

    return integer ;
}

void LFSR::shiftLeft() {
    // Swap every character with the proceeding one from the back to the front
    for(auto i = _length - 1; i > 0; --i) {
        std::swap(_state[i],_state[i - 1]) ;
    }

    // Finally, set the last character in the string (least significant bit) to 0
    _state[_length - 1] = '0' ;
}

LFSR::LFSR(std::string seed, int tap) {

    // Validate that seed string contains only 0's and 1's
    for(auto bit : seed) {
        if (bit != '0' && bit != '1') throw "Invalid seed string!" ;
    }

    // Validate that tap is non-negative and less than the seed length
    if (tap < 0 || tap >= (int)seed.length()) throw "Tap value out of bounds!" ;

    // Now that everything is in order, initialize the data members
    _state = seed ;
    _tap = tap ;
    _length = seed.length() ;
}

int LFSR::step() {
    char tempBit = XOR (_state[0], _state[_length - _tap]) ;

    shiftLeft() ;

    _state[_length - 1] = tempBit ;

    return tempBit == '0' ? 0 : 1 ;
}

int LFSR::generate(int iterations) {

    std::vector<char> generatedBitsAsChars ;

    for(int i = 0; i < iterations; i++) {
        generatedBitsAsChars.push_back(step() == 0 ? '0' : '1') ;
    }
    
    /*
    std::cout << "binary representation: " << std::endl ;
    for(auto i : generatedBitsAsChars) {
        std::cout << i << std::endl ;
    }
    */

    return binaryCharVectorToInteger(generatedBitsAsChars) ;
}