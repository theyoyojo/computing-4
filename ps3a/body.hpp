#ifndef BODY_HPP
#define BODY_HPP "body.hpp"

#include <SFML/Graphics.hpp>

namespace jsavitz {

class Body : public sf::Drawable {

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
  static int windowWidth ;
  static int windowHeight ;

  Body(double xPosition, double yPosition, double xVelocity, double yVelocity, double mass, std::string spriteFilename) ;

  Body() ;

  void printProperties() ;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const ;

  friend std::istream& operator >>(std::istream& istream, Body& body) {

    istream >> body._xPosition ;
    istream >> body._yPosition ;
    istream >> body._xVelocity;
    istream >> body._yVelocity;
    istream >> body._mass ;
    istream >> body._spriteFilename ;

    return istream ;
  }

  
} ; // class Body

} // namespace jsavitz

#endif // BODY_HPP