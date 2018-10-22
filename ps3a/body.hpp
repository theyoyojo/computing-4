#ifndef BODY_HPP
#define BODY_HPP "body.hpp"

#include <SFML/Graphics.hpp>

namespace jsavitz {

class Body : sf::Drawable {

private:

double _xPosition ;

double _yPosition ;

double _xVelocity ;

double _yVelocity ;

double _mass ;

std::string _spriteFilename ;

sf::Sprite _sprite ;

sf::Texture _texture ;

sf::Image _image ;

public:

static double universeSize ;

Body(double xPosition, double yPosition, double xVelocity, double yVelocity, double mass, std::string spriteFilename) ;

Body() ;

void draw(sf::RenderTarget& target, sf::RenderStates states) const ;

friend std::istream& operator >>(std::istream& istream, Body& obj) ;

} ; // class Body

} // namespace jsavitz

#endif // BODY_HPP