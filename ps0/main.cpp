#include <SFML/Graphics.hpp>
#include <stdio.h>

// Global Frames Per Second
int const FPS = 60 ;

// Global constants for window size
int const WINDOW_WIDTH = 800 ;
int const WINDOW_HEIGHT = 800 ;

class Ball {
  
  sf::Sprite& _sprite ;
  
  // velocity in pixels per second
  float _xVelocity ;
  float _yVelocity ;

  int _xDim ;
  int _yDim ;

public:

  Ball(sf::Sprite& sprite) ;

  // Velocity is in pixels per second

  void setXVelocity(float newVelocity) ;
  void setYVelocity(float newVelocity) ;

  float getXVelocity() ;
  float getYVelocity() ;

  void updatePosition() ;

  sf::Sprite& getSprite() ;

} ; // class Ball 

Ball::Ball(sf::Sprite& sprite) :
  _sprite(sprite),
  _xVelocity(0.f),
  _yVelocity(0.f),
  _xDim((float)_sprite.getTexture()->getSize().x),
  _yDim((float)_sprite.getTexture()->getSize().y)
  {
    // Start the ball in the center of the window
    _sprite.setPosition(WINDOW_WIDTH/2 - _xDim/2, WINDOW_HEIGHT/2 - _yDim/2) ;  
  }

sf::Sprite& Ball::getSprite() {
  return _sprite ;
}

void Ball::setXVelocity(float newVelocity) {
  _xVelocity = newVelocity ;
}

void Ball::setYVelocity(float newVelocity) {
  _yVelocity = newVelocity ;
}

float Ball::getXVelocity() {
  return _xVelocity ;
}

float Ball::getYVelocity() {
  return _yVelocity ;
}

void Ball::updatePosition() {
  sf::Vector2f newPosition ;

  newPosition.x = _sprite.getPosition().x + _xVelocity / FPS ;
  newPosition.y = _sprite.getPosition().y + _yVelocity / FPS ;

  // collision check first
  
  // Case: left edge collision
  if (newPosition.x <= 0 ) {
    newPosition.x = 0 ;
    _xVelocity *= -1 ; // Reverse direction and maintain momentum
  }
  // Case: top edge collision
  else if (newPosition.y <= 0 ) {
    newPosition.y = 0 ;
    _yVelocity *= -1 ; 
  }
  // Case: right edge collision
  else if (newPosition.x + _xDim >= WINDOW_WIDTH) {
    newPosition.x = WINDOW_WIDTH - _xDim ;
    _xVelocity *= -1 ;  
  }
  // Case: bottom edge collision
  else if (newPosition.y + _yDim >= WINDOW_HEIGHT) {
    newPosition.y = WINDOW_HEIGHT - _yDim ;
    _yVelocity *= -1 ;  
  }

  _sprite.setPosition(newPosition) ;
}

int main() {

  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!") ;

  // Updates to display happen FPS times per second
  window.setFramerateLimit(FPS) ;


  sf::Texture textureFootball;
  if (textureFootball.loadFromFile("paintex_football_small.png") == false) {
    exit(1) ;
  }
  sf::Sprite spriteFootball(textureFootball) ;

  Ball football(spriteFootball) ;
  
  printf("origin is at: %f, %f\n", spriteFootball.getOrigin().x, spriteFootball.getOrigin().y) ;
  while (window.isOpen())
  {
    sf::Event event ;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close() ;
      }
      else if (event.type == sf::Event::KeyPressed ) {

        switch(event.key.code) {
          case sf::Keyboard::Right:
            football.setXVelocity(football.getXVelocity() + 10.f) ;
            break ;
          case sf::Keyboard::Left:
            football.setXVelocity(football.getXVelocity() - 10.f) ;
            break ;
          case sf::Keyboard::Down:
            football.setYVelocity(football.getYVelocity() + 10.f) ;
            break ;
          case sf::Keyboard::Up:
            football.setYVelocity(football.getYVelocity() - 10.f) ;
            break ;
          default:
            break ;
        }

      }
    }

    // check for collision and
    // update ball position based on current velocity
    printf("Vx = %f, Vy = %f\n", football.getXVelocity(), football.getYVelocity() ) ;
    football.updatePosition() ;

    window.clear() ;
    window.draw(football.getSprite()) ;
    window.display() ;

  }

  return 0 ;
}
