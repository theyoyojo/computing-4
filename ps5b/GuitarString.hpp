#ifndef GUITAR_STRING_HPP
#define GUITAR_STRING_HPP "GuitarString.hpp"

#include <SFML/Audio.hpp>
#include <vector>
#include "RingBuffer.hpp"

class GuitarString {

public:
  const static int SAMPLE_RATE = 44100 ; // Hz

  const static constexpr double ENERGY_DECAY_FACTOR = 0.996 ;

  GuitarString(double frequency) ;

  GuitarString(std::vector<sf::Int16> init) ;

  void pluck() ;

  void tic() ;

  sf::Int16 sample() ;

  int time() ;

private:
  RingBuffer string ;

  std::size_t bufferSize ;

  int ticCount ;

} ; // class GuitarString

#endif // GUITAR_STRING_HPP