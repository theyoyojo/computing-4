#include "body.hpp"
#include <stdexcept>
#include <iostream>

using namespace jsavitz ;

Body::Body(double xPosition, double yPosition, double xVelocity, double yVelocity, double mass, std::string spriteFilename) :
_xPosition(xPosition), _yPosition(yPosition), _xVelocity(xVelocity), _yVelocity(yVelocity), _mass(mass), _spriteFilename(spriteFilename)
{
  if (!_image.loadFromFile(_spriteFilename)) throw std::runtime_error("Body sprite image not found!") ;

  _texture.loadFromImage(_image) ;
  _sprite.setTexture(_texture) ;
}

Body::Body() {
  std::cin >> *this ;
  if (!_image.loadFromFile(_spriteFilename)) throw std::runtime_error("Body sprite image not found!") ;
  _texture.loadFromImage(_image) ;
  _sprite.setTexture(_texture) ;
}

void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}

std::istream& jsavitz::operator >>(std::istream& istream, Body& body) {
  istream >> body._xPosition ;
  istream >> body._yPosition ;
  istream >> body._xVelocity;
  istream >> body._yVelocity;
  istream >> body._mass ;
  istream >> body._spriteFilename ;

  return istream ;
}