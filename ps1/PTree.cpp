#include "PTree.hpp"
#include <math.h>

using namespace js ;

// Small helper class used to easily draw squares
class Square : public sf::ConvexShape {
public:
  Square(sf::Vector2f origin, double offsetMagnitude, double offsetDirectionRadians) {
    setPointCount(4) ;
    setOutlineColor(sf::Color::White) ;
    setOutlineThickness(1) ;
    setFillColor(sf::Color::Black) ;

    sf::Vector2f terminal(offsetMagnitude * cos(offsetDirectionRadians),  offsetMagnitude * sin(offsetDirectionRadians)) ;

    setPoint(0, origin) ;
    setPoint(1, sf::Vector2f(terminal.x , origin.y)) ;
    setPoint(2, sf::Vector2f(terminal.x, terminal.y)) ;
    setPoint(3, sf::Vector2f(origin.x, terminal.y)) ;
  }

} ; // class Square

PTree::PTree(unsigned int recursionDepth, double baseSquareSideLength, double windowWidth, double windowHeight) :
_recursionDepth(recursionDepth),
_baseSquareSideLength(baseSquareSideLength), // This value is a double because I will be doing calculations with it
_windowWidth(windowWidth),
_windowHeight(windowHeight)
{}

void PTree::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  
  Square s(sf::Vector2f(_windowWidth/2 - _baseSquareSideLength/2,_windowHeight), _baseSquareSideLength, M_PI/4) ;

  target.draw(s) ;
}