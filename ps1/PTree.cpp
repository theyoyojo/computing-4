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

  // Draw the left child square
  Square left(base._branchTop, sf::Vector2f(base._sideLength, base._offset.y + M_PI/4 + _shiftModifier) ) ;

  // Draw the right child square based on the left child
  Square right(left._branchBottom, sf::Vector2f(base._sideLength, base._offset.y - M_PI/4) ) ;

  // Draw the left square and the rest of the shape
  target.draw(left) ;
  pTree(currentDepth + 1, target, left) ;

  // Draw the right square and the rest of the shape
  target.draw(right) ;
  pTree(currentDepth + 1, target, right) ;
}

void PTree::draw(sf::RenderTarget& target, sf::RenderStates states) const {

  Square base(sf::Vector2f(_windowWidth/2 - _baseSquareSideLength/2, _windowHeight - 0.2 * _windowHeight), sf::Vector2f(_baseSquareSideLength, M_PI/4)) ;
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

void PTree::updateRotateAnimation() {

  // Every second, shift  M_PI / 64 radians
  double deltaThetaPerSecond = M_PI / 8 ;

  // Divide by frames per second and update every frame
  shift(-1 * deltaThetaPerSecond / FPS) ;
}

void PTree::updateWaveAnimation() {

  // Retain the value of psi between function calls
  static double psi = 0 ;

  // Animation should have period of 4 seconds, so each second, psi should increment by 2pi/4
  const double deltaPsiPerSecond = M_PI / 2 ;

  // Using psi, calculate the change in angle for the current frame
  double deltaTheta = sin(psi) / 1024 ;
  
  // Apply the shift in angle
  shift(deltaTheta) ;

  psi += deltaPsiPerSecond / FPS ;

  // If psi has gone around the circle, reset it
  if (psi >= 2 * M_PI) {
    psi = 0 ;
  }
}