#include "body.hpp"
#include <stdexcept>
#include <iostream>

using namespace jsavitz ;

double Body::universeSize = 0 ;

int Body::windowWidth = 0 ;

int Body::windowHeight = 0 ;

sf::Vector2f getDisplayCoordinates(sf::Vector2f cartesianCoordinates) {
  sf::Vector2f displayCoordinates ;

  displayCoordinates.x = Body::windowWidth/2 + Body::windowWidth/2 * ( (cartesianCoordinates.x) / Body::universeSize ) ;
  displayCoordinates.y = Body::windowHeight/2 + Body::windowHeight/2 * ( (-1 * cartesianCoordinates.y) / Body::universeSize ) ;

  return displayCoordinates ;
}

Body::Body(double xPosition, double yPosition, double xVelocity, double yVelocity, double mass, std::string spriteFilename) :
_xPosition(xPosition), _yPosition(yPosition), _xVelocity(xVelocity), _yVelocity(yVelocity), _mass(mass), _spriteFilename(spriteFilename)
{
  if (!_image.loadFromFile(_spriteFilename)) throw std::runtime_error("Body sprite image not found!") ;

  _texture.loadFromImage(_image) ;
  _sprite.setTexture(_texture) ;
  _sprite.setPosition(getDisplayCoordinates(sf::Vector2f(_xPosition,_yPosition))) ;

}

Body::Body() {
  std::cin >> *this ;
  if (!_image.loadFromFile(_spriteFilename)) throw std::runtime_error("Body sprite image not found!") ;
  _texture.loadFromImage(_image) ;
  _sprite.setTexture(_texture) ;
  _sprite.setPosition(getDisplayCoordinates(sf::Vector2f(_xPosition,_yPosition))) ;

  // Debug output
  //std::cout << "Position set to" << _sprite.getPosition().x << "," << _sprite.getPosition().y << std::endl ;
}

void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(_sprite) ;
}

void Body::step(double seconds) {
  _xPosition += _xVelocity * seconds ;
  _yPosition += _yVelocity * seconds ;
  _sprite.setPosition(getDisplayCoordinates(sf::Vector2f(_xPosition,_yPosition))) ;
}

sf::Vector2f Body::getVelocity() {
  sf::Vector2f velocity ;
  velocity.x = _xVelocity ;
  velocity.y = _yVelocity ;
  return velocity ;
}

void Body::setVelocity(sf::Vector2f velocity) {
  _xVelocity = velocity.x ;
  _yVelocity = velocity.y ;
}

sf::Vector2f Body::getPosition() {
  sf::Vector2f position ;
  position.x = _xPosition ;
  position.y = _yPosition ;
  return position ;
}

double Body::getMass() {
  return _mass ;
}

void Body::printProperties() {

  std::cout << _xPosition << "\t" ;
  std::cout << _yPosition << "\t" ;
  std::cout << _xVelocity << "\t" ;
  std::cout << _yVelocity << "\t" ;
  std::cout << _mass << "\t" ;
  std::cout << _spriteFilename ;

  std::cout << std::endl ;
}

std::string Body::getSpriteFilename() {
  return _spriteFilename ;
}