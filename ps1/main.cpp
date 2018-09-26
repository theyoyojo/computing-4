// Pythagoras tree

#include "PTree.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

const int RATIO_WINDOW_WIDTH_TO_SQUARE = 6 ;
const int RATIO_WINDOW_HEIGHT_TO_SQUARE = 4 ;

// Checks if str contains nothing but digits (i.e. can be converted to an unsigned int)
bool isNumber(char * str) {
  for(char * c = str; *c != '\0'; c++) {
    if (!std::isdigit(*c)) {
      return false ;
    }
  }
  return true ;
}

/* Executable parameters:
1: L -- The side length of the base square
2: N -- The recursion depth
*/

typedef enum animation {NONE, ROTATE, WAVE} Animation;

extern const int js::FPS = 60 ;

int main(int argc, char ** argv) {

  // Validate count and type of args
  if (argc != 3 || !isNumber(argv[1]) || !isNumber(argv[2])) {
    printf("Usage: PTree <uint base-square-side-length> <uint recursion-depth>\n") ;
    exit(1) ;
  }

  double baseSquareSideLength = atof(argv[1]) ;
  unsigned int recursionDepth = atoi(argv[2]) ;

  // Calculate window size from square side length L as 6L x 4L (as specified)
  double windowWidth = RATIO_WINDOW_WIDTH_TO_SQUARE * baseSquareSideLength ;
  double windowHeight = RATIO_WINDOW_HEIGHT_TO_SQUARE * baseSquareSideLength ;


  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML-ps1") ;

  window.setFramerateLimit(js::FPS) ;

  js::PTree pTree(recursionDepth, baseSquareSideLength, windowWidth, windowHeight) ;

  Animation currentAnimation = NONE ;

  while(window.isOpen()) {
    sf::Event capturedEvent ;

    while (window.pollEvent(capturedEvent) ) {
      if (capturedEvent.type == sf::Event::Closed) {
        window.close() ;
      }
      if (capturedEvent.type == sf::Event::KeyPressed) {
        switch(capturedEvent.key.code) {
          case sf::Keyboard::Q:
            window.close() ;
            break ;
          case sf::Keyboard::Left:
            pTree.shiftLeft() ;
            break ;
          case sf::Keyboard::Right:
            pTree.shiftRight() ;
            break ;
          case sf::Keyboard::A:
            currentAnimation = ROTATE ;
            break ;
          case sf::Keyboard::B:
            currentAnimation = WAVE ;
            break ;
          case sf::Keyboard::Space:
            currentAnimation = NONE ;
            break ;
          default:
          break ;
        }
      }
    }

    switch(currentAnimation) {
      case ROTATE:
        pTree.updateRotateAnimation() ;
        break ;
      case WAVE:
        pTree.updateWaveAnimation() ;
        break ;
      case NONE:
      default:
        break ;
    }

    window.clear() ;
    window.draw(pTree) ;
    window.display() ;
  }

  return 0;
}
