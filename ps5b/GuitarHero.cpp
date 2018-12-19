/*
  Joel Savitz's derivative work based on:

  Copyright 2015 Fred Martin, fredm@cs.uml.edu
  Mon Mar 30 08:58:49 2015

  Sue me
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <math.h>
#include <limits.h>

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

#include "RingBuffer.hpp"
#include "GuitarString.hpp"

#define STANDARD_A 440 // Hz
#define SAMPLES_PER_SEC 44100

const std::string pianoMap = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' " ;

std::vector<sf::Int16> makeSamplesFromString(GuitarString gs) {
  std::vector<sf::Int16> samples;

  gs.pluck();
  int duration = 8;  // seconds
  int i;
  for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
    gs.tic();
    samples.push_back(gs.sample());
  }

  return samples;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(300, 200), "SFML Guitar Hero");
  sf::Event event;
  double freq;
  const int KEYBOARD_LENGTH = 37 ;

  std::vector<std::vector<sf::Int16>> sampleVector(KEYBOARD_LENGTH) ;
  std::vector<sf::SoundBuffer> soundBufferVector(KEYBOARD_LENGTH) ;
  std::vector<sf::Sound> soundVector(KEYBOARD_LENGTH) ;

  [&]() {
    for(int i = 0; i < KEYBOARD_LENGTH; ++i) {
      freq = STANDARD_A * pow(2,(i - 24)/12.0) ;
      std::cout << freq << std::endl ;
      sampleVector[i] = makeSamplesFromString(GuitarString(freq)) ;
      if (!soundBufferVector[i].loadFromSamples(&sampleVector[i][0], sampleVector[i].size(), 2, SAMPLES_PER_SEC)) {
        throw std::runtime_error("sf::SoundBuffer: failed to load from samples.") ;
      }
      soundVector[i].setBuffer(soundBufferVector[i]) ;
    }
  }() ;

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::TextEntered:
      {
        int i = 0 ;
        for (auto ch : pianoMap) {
          if (event.text.unicode < 128 && ch == (char)event.text.unicode) {
            soundVector[i].play() ;
          }
          ++i ;
        }
      }
        break ;
      default:
        break;
      }

      window.clear();
      window.display();
    }
  }
  return 0;
}

