#include "PTree.hpp"
#include <math.h>
#include <iostream>

using namespace js ;


Square::Square(sf::Vector2f origin, sf::Vector2f offset ) : _origin(origin), _offset(offset) {

  setPointCount(4) ;
  setOutlineColor(sf::Color::White) ;
  setOutlineThickness(1) ;
  setFillColor(sf::Color::Transparent) ;

  double offsetMagnitude = offset.x ;
  double offsetDirectionRadians = offset.y ;

  _sideLength = offsetMagnitude * cos(M_PI/4)  ;

  // Calculation of vertex points based on origin coordinates and offset vector
  _branchBottom = sf::Vector2f(origin.x + _sideLength * cos(offsetDirectionRadians - M_PI/4 ), origin.y - _sideLength * sin(offsetDirectionRadians - M_PI/4)) ;
  _branchTop = sf::Vector2f(origin.x + _sideLength * cos(offsetDirectionRadians + M_PI/4), origin.y - _sideLength * sin(offsetDirectionRadians + M_PI/4)) ;
  _terminal = sf::Vector2f(origin.x + offsetMagnitude * cos(offsetDirectionRadians),  origin.y - offsetMagnitude * sin(offsetDirectionRadians)) ;
  
  //std::cout << "Origin coords: (" << origin.x << "," << origin.y << ")" << std::endl ;
  //std::cout << "terminal coords: (" << _terminal.x << "," << _terminal.y << ")" << std::endl ;
  

  setPoint(0, _origin) ;
  setPoint(1, _branchBottom) ;
  setPoint(2, _terminal) ;
  setPoint(3, _branchTop) ;
}

PTree::PTree(unsigned int recursionDepth, double baseSquareSideLength, double windowWidth, double windowHeight) :
_recursionDepth(recursionDepth),
_baseSquareSideLength(baseSquareSideLength), // This value is a double because I will be doing calculations with it
_windowWidth(windowWidth),
_windowHeight(windowHeight)
{}

void PTree::pTree(unsigned int currentDepth, sf::RenderTarget& target, Square base) const {

  // If we have reached the recursion depth, there is no more work to do.
  if (currentDepth >= _recursionDepth) return ;

  //std::cout << "Draw at depth: " << currentDepth << std::endl ;

  /*
  Square test(base._branchTop, sf::Vector2f(100.0, M_PI/2) ) ;

  target.draw(test) ;
  */

  //std::cout << "Passing parameters to left: " << base._sideLength << ", " << base._offset.y + M_PI/4 << std::endl ;

  Square left(base._branchTop, sf::Vector2f(base._sideLength, base._offset.y + M_PI/4 + _shiftModifier) ) ;
  Square right(left._branchBottom, sf::Vector2f(base._sideLength, base._offset.y - M_PI/4) ) ;

  target.draw(left) ;

  pTree(currentDepth + 1, target, left) ;
  target.draw(right) ;
  pTree(currentDepth + 1, target, right) ;
}

void PTree::draw(sf::RenderTarget& target, sf::RenderStates states) const {

  Square base(sf::Vector2f(_windowWidth/2 - _baseSquareSideLength/2, _windowHeight), sf::Vector2f(_baseSquareSideLength, M_PI/4)) ;
  target.draw(base) ;

  pTree(0, target, base) ;
}

void PTree::shiftLeft() {
  _shiftModifier += M_PI / 512 ;
}

void PTree::shiftRight() {
  _shiftModifier -= M_PI / 512 ;
}

void PTree::shift(double deltaTheta) {
  _shiftModifier += deltaTheta ;
}

void PTree::rotate() {
  for(double i = 0; i < 2 * M_PI; i++) {
    shift(M_PI / 512) ;
    sf::sleep(sf::milliseconds(10)) ;
  }
}