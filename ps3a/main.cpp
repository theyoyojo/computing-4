#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "body.hpp"

const int WIDTH = 200 ;
const int HEIGHT = 200 ;

int main() {

  int numberBodies ; 

  std::cin >>  numberBodies ;
  std::cin >> jsavitz::Body::universeSize ;

  std::vector<std::shared_ptr<jsavitz::Body>> bodies ;


  for (int i = 0; i < numberBodies; i++) {
    bodies.push_back(std::make_shared<jsavitz::Body>()) ;
  }

  sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"SFML-demo") ;

  sf::Event e ;
    
  while (window.isOpen()) {
    window.pollEvent(e) ;

    if (e.type == sf::Event::Closed) {
      window.close() ;
    }
  }

  window.clear() ;
  //window.draw() ;
  window.display() ;
}