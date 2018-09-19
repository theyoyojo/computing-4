#include "triangle.hpp"

using namespace js ;

Triangle::Triangle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
  setPointCount(3) ;
  setPoint(0,a) ;
  setPoint(1,b) ;
  setPoint(2,c) ;
}

void Triangle::setColor(sf::Color color) {
  sf::ConvexShape::setFillColor(color) ;
}

void Triangle::setOrigin(sf::Vector2f origin) {
  sf::ConvexShape::setOrigin(origin) ;
}