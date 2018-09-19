#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <math.h>
#include "sierpinski.hpp"

bool isNumber(char * str) {
  for(char * c = str; *c != '\0'; c++) {
    if (!std::isdigit(*c)) {
      return false ;
    }
  }
  return true ;
}

// sierpinski binary entry point 
int main(int argc, char ** argv) {
  if (argc != 3 || !isNumber(argv[1]) || !isNumber(argv[2])) {
    printf("Usage: sierpinski <u_int recursion-depth> <u_int window-size>\n") ;
    exit(1) ;
  }

  int recursionDepth = std::atoi(argv[1]) ;
  int windowDim = std::atoi(argv[2]) ;

  sf::RenderWindow window(sf::VideoMode(windowDim, windowDim), "SFML-demo") ;

  js::Sierpinski st(recursionDepth, windowDim) ;

  while(window.isOpen()) {
    sf::Event e ;


    while(window.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        window.close() ;
      }
    }
    window.clear(sf::Color::Blue) ;
    window.draw(st) ;
    window.display() ;
  }


  return 0 ;
}
