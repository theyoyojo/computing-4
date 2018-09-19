#ifndef SIERPINSKI_H
#define SIERPINSKI_H "sierpinski.h"

#include <SFML/Graphics.hpp>

namespace js {

class Sierpinski : public sf::Drawable {
private:

  int _recursionDepth ;
  int _size ;

  Sierpinski() ;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;

public:

  Sierpinski(int recursionDepth, int size) ;

} ; // class Sierpinski

} // namespace js

#endif // SIERPINSKI_H