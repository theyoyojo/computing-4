#include "sierpinski.hpp"
#include "triangle.hpp"
#include <math.h>
#include <stdio.h>

using namespace js ;

Sierpinski::Sierpinski(int recursionDepth, int size) :
  _recursionDepth(recursionDepth),
  _size(size)
  {} 


void draw_recursive(sf::RenderTarget& target, int depth, sf::Vector2f origin, int sideLength) {

  // No more triangles to draw if you're out of your depths and out of your mind
  if (depth == 0) return ;

  // Draw triangle starting from specified origin, then call self with three new origins and depth-1

  js::Triangle t(
    sf::Vector2f(0,0),
    sf::Vector2f(-1 * sideLength/2, -1 * sideLength/2 * sqrt(2)),
    sf::Vector2f(sideLength/2, -1 * sideLength/2 * sqrt(2))
  ) ;
  t.setColor(sf::Color::Black) ;
  t.setOrigin(origin) ;

  sf::Vector2f a(origin.x, origin.y + sqrt(2)*sideLength/2) ;
  sf::Vector2f b(origin.x - sideLength/2,origin.y) ;
  sf::Vector2f c(origin.x + sideLength/2,origin.y) ;

  draw_recursive(target, depth -1, a, sideLength/2) ;
  draw_recursive(target, depth -1, b, sideLength/2) ;
  draw_recursive(target, depth -1, c, sideLength/2) ;

  target.draw(t) ;
}

void Sierpinski::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    js::Triangle t(
      sf::Vector2f(0,_size),
      sf::Vector2f(_size/2, _size - std::sqrt(2)*(_size/2)),
      sf::Vector2f(_size,_size)
    ) ;

  target.draw(t) ;
  draw_recursive(target, _recursionDepth, sf::Vector2f(-1 * _size / 2, -1 * _size), _size/2) ;
}