#ifndef PTREE_H
#define PTREE_H "PTree.hpp"

#include <SFML/Graphics.hpp>

namespace js {

class PTree : public sf::Drawable{

  // Recursion depth -- how many layers of squares to draw
  unsigned int _recursionDepth ;

  // The side length of the first square drawn -- the base square
  double _baseSquareSideLength ;

  // Horizontal dimension of window
  double _windowWidth ;

  // Vertical dimension of window
  double _windowHeight ;


  // Recursively draw the fractal
  void pTree(/* params */) ;

public:

  // Construct the object
  PTree(unsigned int recursionDepth, double baseSquareSideLength, double windowWidth, double windowHeight) ;

  // Draw the object on the screen as per object state
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;

} ; // class PTree

} // namespace js

#endif // PTREE_H