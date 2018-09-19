#ifndef TRIANGLE_H
#define TRIANGLE_H "triangle.h"

#include <SFML/Graphics.hpp>

namespace js {

class Triangle : public sf::ConvexShape {

public:

  Triangle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) ;
  
  void setColor(sf::Color color) ;

  void setOrigin(sf::Vector2f origin) ;

} ; // class Triangle

} // namespace js

#endif // TRIANGLE_H