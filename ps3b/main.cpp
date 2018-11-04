#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include "body.hpp"

const int WIDTH = 1000 ;
const int HEIGHT = 1000 ;

void simulatePhysics(std::vector<std::shared_ptr<jsavitz::Body >>& bodies, double timeIncrement) {
  // For each body:
  sf::Vector2f netForce ;
  sf::Vector2f relativePositions ;
  sf::Vector2f acceleration ;
  sf::Vector2f newVelocity ;

  double radius ;
  double tempForceMagnitude ;

  for (auto body : bodies) {
    // Sum the pairwise forces for each body
    netForce.x = 0, netForce.y = 0 ;
    for (auto otherBody : bodies) {
      // Don't bother calculating force on itself, radius will be 0
      if (body == otherBody) continue ;

      relativePositions.x = otherBody->getPosition().x - body->getPosition().x ;
      relativePositions.y = otherBody->getPosition().y - body->getPosition().y ;

      // Calculate radius ;
      radius = sqrt( pow(relativePositions.x,2.0) + pow(relativePositions.y,2.0) ) ;

      tempForceMagnitude = ( jsavitz::Body::G * (body->getMass() * otherBody->getMass())) / pow(radius,2.0) ;

      netForce.x += ( tempForceMagnitude * relativePositions.x) / radius ;
      netForce.y += ( tempForceMagnitude * relativePositions.y) / radius ;
    }
    
    // Calculate acceleration
    acceleration.x = netForce.x / body->getMass() ;
    acceleration.y = netForce.y / body->getMass() ;

    // Calculate new velocity
    newVelocity.x = body->getVelocity().x + acceleration.x * timeIncrement ;
    newVelocity.y = body->getVelocity().y + acceleration.y * timeIncrement ; 

    // Update stored velocity
    body->setVelocity(newVelocity) ;

    // Internally update position
    body->step(timeIncrement) ;

  }
}

int main(int argc, char ** argv) {

  if (argc != 3) {
    std::cout << "Usage: ./NBody <simulation_time> <time_increment>" << std::endl ;
    exit(1) ;
  }

  double simulationTime = atof(argv[1]) ;
  double timeIncrement = atof(argv[2]) ;
  double currentTime = 0 ;

  int numberBodies ; 

  std::cin >>  numberBodies ;
  std::cin >> jsavitz::Body::universeSize ;

  jsavitz::Body::windowWidth  = WIDTH ;
  jsavitz::Body::windowHeight = HEIGHT ;

  std::vector<std::shared_ptr<jsavitz::Body>> bodies ;


  for (int i = 0; i < numberBodies; i++) {
    bodies.push_back(std::make_shared<jsavitz::Body>()) ;
  }

  /* Debug output
  for ( auto body : bodies) {
    body->printProperties() ;
  }
  */

  sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"SFML-demo") ;

  sf::Event e ;

  bool justFinished = true ;
    
  while (window.isOpen()) {
    window.pollEvent(e) ;

    if (e.type == sf::Event::Closed) {
      window.close() ;
    }

    if (currentTime < simulationTime) {
      simulatePhysics(bodies, timeIncrement) ;
      std::cout << "ran sim" << std::endl ;
      currentTime += timeIncrement ;
      std::cout << "TIME: " << currentTime << " of " << simulationTime << std::endl ;
    }
    else if (justFinished){
      std::cout << numberBodies << std::endl ;
      std::cout << jsavitz::Body::universeSize << std::endl ;
      for (auto body : bodies) {
        std::cout << std::scientific 
        << body->getPosition().x << "\t" << body->getPosition().y << "\t"
        << body->getVelocity().x << "\t" << body->getVelocity().y << "\t"
        << body->getMass() << "\t" << body->getSpriteFilename() << std::endl ;
      }
      justFinished = false ;
    }

    window.clear() ;
    // Draw planets
    for(auto body : bodies) window.draw(*body) ;
    window.display() ;
  }

}