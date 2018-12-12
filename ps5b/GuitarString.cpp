#include "GuitarString.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

GuitarString::GuitarString(double frequency) : string(std::ceil(SAMPLE_RATE / frequency)) {
  std::srand(std::time(0)) ;
  ticCount = 0 ;
}

GuitarString::GuitarString(std::vector<sf::Int16> init) : string(init.size()){
  for (auto sample : init) string.enqueue(sample) ;
  std::srand(std::time(0)) ;
  ticCount = 0 ;
}

void GuitarString::pluck() {
  string.empty() ;
  for (int i = 0; i < string.capacity(); ++i) {
    string.enqueue(0 + (int16_t)rand()) ;
  }
}

void GuitarString::tic() {
  int16_t deletedValue = string.dequeue() ;
  int16_t firstValue = string.peek() ;
  //int16_t secondValue = string.peek(5) ;
  string.enqueue(ENERGY_DECAY_FACTOR * ((deletedValue + firstValue) / 2)) ;
  //string.enqueue(ENERGY_DECAY_FACTOR * ((0.9 * deletedValue + 0.1 * firstValue))) ;
  //string.enqueue(ENERGY_DECAY_FACTOR * ((deletedValue + firstValue + secondValue) / 3)) ;
  //string.enqueue(ENERGY_DECAY_FACTOR * ((deletedValue * 0.19 + firstValue * 0.2+ secondValue * 0.6) )) ;
  ++ticCount ;
}

sf::Int16 GuitarString::sample() {
  return string.peek() ;
}

int GuitarString::time() {
  return ticCount ;
}