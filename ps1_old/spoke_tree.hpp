#ifndef SPOKE_TREE_H
#define SPOKE_TREE_H "spoke_tree.h"

#include <SFML/Graphics.hpp>
#include <map>

namespace js {

typedef enum spokeMode {
  FIXED,
  ARITHMETIC,
  GEOMETRIC
} SpokeMode ;

class SpokeTree : public sf::Drawable {

private:

  // Private data members

  const sf::Color _colorLines ;

  static const sf::Color _COLOR_LINES_DEFAULT ;

  static const double _RATIO_FIRST_LINE_TO_WINDOW ;

  static const double _RATIO_LINE_SHRINK ;

  unsigned int _lengthWindowSide ;

  unsigned int _maxRecursionDepth ;

  int _userModifierRadialSpokes ;

  int _userModifierRecursionDepth ;

  double _userModifierRatioLineShrink ;

  SpokeMode _userModifierSpokeMode ;

  // Define class for the next three data members?
  // draw is const qualified so I cannot optimize?

  std::map<unsigned int, double> _radAngleBetweenSpokesGivenRecursionDepth ;

  std::map<unsigned int, double> _lengthLineNextGivenRecursionDepth ;

  std::map<unsigned int, double> _ratioLineShrinkGivenRecursionDepth ; // This could also be defined using a function that depends on recursionDepth


  // Private member functions

  double calculateRatioLineShrink(unsigned int recursionDepth) ;
  double calculateRatioLineShrink(unsigned int recursionDepth) const ;

  double calculateRadAngleBetweenSpokes(unsigned int recursionDepth) ;
  double calculateRadAngleBetweenSpokes(unsigned int recursionDepth) const ;

  double calculateLengthNextLine(unsigned int recursionDepth) ;
  double calculateLengthNextLine(unsigned int recursionDepth) const ;

  unsigned int calculateRadialSpokesMax(unsigned int recursionDepth) const ;

  // Base angle is calculated relative to the x-axis, as in basic trigonometry
  //sf::Vector2f calculateDestinationCoordinates(unsigned int recursionDepth, unsigned int iterationsRadialSpokes, sf::Vector2f& cursor, double radBaseAngle, double& radNewAngle) ;
  sf::Vector2f calculateDestinationCoordinates(unsigned int recursionDepth, unsigned int iterationsRadialSpokes, sf::Vector2f& cursor, double radBaseAngle, double& radNewAngle, double radAngleBetweenSpokes, double lengthNextLine) const ;
  
  void draw_fractal(sf::RenderTarget& target, sf::Vector2f cursor, unsigned int recursionDepth, double radBaseAngle) const ;

  // Class may not be instantiated using default constructor, must use (unsigned int, unsigned int, sf::Color&)
  SpokeTree() ;

public:

/*
  Essential constructor params:
  - window side length
  - maximum recursion depth

  Non-essential constructor params:
  - line color
*/

  // Constructors

  SpokeTree(unsigned int windowSideLength, unsigned int recursionDepthMax, sf::Color color = _COLOR_LINES_DEFAULT) ;

  // Public member functions

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;

  void setUserModifierRadialSpokes(int newValue) ;
  int getUserModifierRadialSpokes() ;

  void setUserModifierRecursionDepth(int newValue) ;
  int getUserModifierRecursionDepth() ;

  void setUserModifierRatioLineShrink(double newValue) ;
  double getUserModifierRatioLineShrink() ;

  void setUserModifierSpokeMode(SpokeMode newValue) ;

} ; // class SpokeTree

} // namespace js

#endif // SPOKE_TREE_H