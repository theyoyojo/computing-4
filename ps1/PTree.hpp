#ifndef PTREE_H
#define PTREE_H "PTree.hpp"

#include <SFML/Graphics.hpp>

namespace js {

// Small helper class used to easily draw squares
class Square : public sf::ConvexShape {
public:
  sf::Vector2f _origin ;
  sf::Vector2f _branchTop ;
  sf::Vector2f _terminal ;
  sf::Vector2f _branchBottom ;
  sf::Vector2f _offset ;
  double _sideLength ;

  Square(sf::Vector2f origin, sf::Vector2f offset ) ;
} ; // class Square

class PTree : public sf::Drawable{

  // Recursion depth -- how many layers of squares to draw
  unsigned int _recursionDepth ;

  // The side length of the first square drawn -- the base square
  double _baseSquareSideLength ;

  // Horizontal dimension of window
  double _windowWidth ;

  // Vertical dimension of window
  double _windowHeight ;

  // A user supplied value to shift the tree in real time
  double _shiftModifier = 0;

  // Recursively draw the fractal
  void pTree(unsigned int currentDepth, sf::RenderTarget& target, Square base) const ;

public:

  // Construct the object
  PTree(unsigned int recursionDepth, double baseSquareSideLength, double windowWidth, double windowHeight) ;

  // Draw the object on the screen as per object state
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;

  void shiftLeft() ;

  void shiftRight() ;

  void shift(double deltaTheta) ;

  void rotate() ;

} ; // class PTree

} // namespace js

#endif // PTREE_H