#include "LFSR.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


bool validateArgs(int argc, char ** argv) { 
  int tap ;
  try {
     tap = std::atoi(argv[4]) ;
  }
  catch(const std::exception & e) {
    std::cout << "Error: " << e.what() << std::endl ;
    return false ;
  }
  
  try {
    jsavitz::LFSR validator(argv[3], tap) ;
  }
  catch (const char * eMsg) {
    std::cout << "Error: " << eMsg << std::endl ;
    return false ;
  }

  return true ;
}

sf::Image negateImage(const sf::Image& input) {
  sf::Image output = input ;
  sf::Vector2u dimensions = input.getSize() ;

  sf::Color tempPixel ;

  for(unsigned int i = 0; i < dimensions.x; i++) {
    for(unsigned int j = 0; j < dimensions.y; j++) {
      tempPixel = input.getPixel(i,j) ;
      output.setPixel(i,j,sf::Color(255 - tempPixel.r, 255 - tempPixel.g, 255 - tempPixel.b)) ;
    }
  }

  return output ;
}

sf::Image encryptImage(const sf::Image& input, jsavitz::LFSR lfsr) {
  sf::Image output = input ;
  sf::Vector2u dimensions = input.getSize() ;

  sf::Color tempPixel ;

  for(unsigned int i = 0; i < dimensions.x; i++) {
    for(unsigned int j = 0; j < dimensions.y; j++) {
      tempPixel = input.getPixel(i,j) ;
      output.setPixel(i,j,sf::Color(tempPixel.toInteger() ^ lfsr.generate(32))) ;
    }
  }

  return output ;
}

int main(int argc, char ** argv) {

  // Validate command line args
  if(argc != 5 || !validateArgs(argc, argv)) {
    std::cout << "Usage: PhotoMagic <input-file> <output-file> <LFSR-seed> <tap-position>" << std::endl ;
    exit(1) ;
  }

  sf::Image input ;

  if (!input.loadFromFile(argv[1])) {
    std::cout << "Error: Input file " << argv[1] << " not found." ;
    exit(1) ;
  }

  jsavitz::LFSR lfsr(argv[3],std::atoi(argv[4])) ;

  sf::Image output = encryptImage(input,lfsr) ;

  if (!output.saveToFile(argv[2])) {
    std::cout << "Error: Unable to save output file with the name " << argv[2] << std::endl ;
  }

  auto windowDim = input.getSize() ;

  const int WIDTH = windowDim.x ;
  const int HEIGHT = windowDim.y;

  sf::RenderWindow windowOriginal(sf::VideoMode(WIDTH, HEIGHT),"SFML-LFSR-original") ;
  sf::RenderWindow windowResult(sf::VideoMode(WIDTH, HEIGHT),"SFML-LFSR-result") ;

  sf::Texture inputImageTexture ;
  sf::Texture outputImageTexture ;

  inputImageTexture.loadFromImage(input) ;
  outputImageTexture.loadFromImage(output) ;

  sf::Sprite inputSprite(inputImageTexture) ;
  sf::Sprite outputSprite(outputImageTexture) ;

  
  while (windowOriginal.isOpen() && windowResult.isOpen()) {
    sf::Event userEvent ;

    while(windowOriginal.pollEvent(userEvent)) {
      if(userEvent.type == sf::Event::Closed) {
        windowOriginal.close() ;
      }
    }
    while(windowResult.pollEvent(userEvent)) {
      if(userEvent.type == sf::Event::Closed) {
        windowResult.close() ;
      }
    }

    windowOriginal.clear() ;
    windowOriginal.draw(inputSprite) ;
    windowOriginal.display() ;

    windowResult.clear() ;
    windowResult.draw(outputSprite) ;
    windowResult.display() ;
  }

}