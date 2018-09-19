#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <math.h>
#include "spoke_tree.hpp"

// Checks if str contains nothing but digits (i.e. can be converted to an unsigned int)
bool isNumber(char * str) {
  for(char * c = str; *c != '\0'; c++) {
    if (!std::isdigit(*c)) {
      return false ;
    }
  }
  return true ;
}

// original binary entry point 
int main(int argc, char ** argv) {
  if (argc != 3 || !isNumber(argv[1]) || !isNumber(argv[2])) {
    printf("Usage: original <u_int recursion-depth> <u_int window-size>\n") ;
    exit(1) ;
  }

  unsigned int recursionDepth = std::atoi(argv[1]) ;
  unsigned int windowDim = std::atoi(argv[2]) ;

  sf::RenderWindow window(sf::VideoMode(windowDim, windowDim), "SFML-demo") ;

  js::SpokeTree* pFractal = new js::SpokeTree(windowDim, recursionDepth) ;

  while(window.isOpen()) {
    sf::Event e ;

    while(window.pollEvent(e)) {
      // If x is pressed OR if key 'q' is pressed, exit the program (I have disabled titlebars in i3wm)
      if (e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Q)) {
        window.close() ;
      }
      else if (e.type == sf::Event::KeyPressed) {
        switch (e.key.code) {
          case sf::Keyboard::I:
            pFractal->setUserModifierRecursionDepth(pFractal->getUserModifierRecursionDepth() + 1) ;
            break ;
          case sf::Keyboard::U:
            pFractal->setUserModifierRecursionDepth(pFractal->getUserModifierRecursionDepth() - 1) ;
            break ;
          case sf::Keyboard::E:
            pFractal->setUserModifierRadialSpokes(pFractal->getUserModifierRadialSpokes() + 1) ;
            break ;
          case sf::Keyboard::W:
            pFractal->setUserModifierRadialSpokes(pFractal->getUserModifierRadialSpokes() - 1) ;
            break ;
          case sf::Keyboard::R:
            pFractal->setUserModifierRatioLineShrink(pFractal->getUserModifierRatioLineShrink() + 0.05) ;
            break ;
          case sf::Keyboard::T:
            pFractal->setUserModifierRatioLineShrink(pFractal->getUserModifierRatioLineShrink() - 0.05) ;
            break ;
          case sf::Keyboard::M:
            pFractal->setUserModifierSpokeMode(js::FIXED) ;
            break ;
          case sf::Keyboard::N:
            pFractal->setUserModifierSpokeMode(js::ARITHMETIC) ;
            break ;
          case sf::Keyboard::B:
            pFractal->setUserModifierSpokeMode(js::GEOMETRIC) ;
            break ;
          default:
            break ;
        }
      }
    }
    window.clear(sf::Color::Black) ;
    window.draw(*pFractal) ;
    window.display() ;
  }

  delete pFractal ;

  return 0 ;
}
