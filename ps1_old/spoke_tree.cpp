#include <math.h>
#include "spoke_tree.hpp"

using namespace js ;

// Default color of lines
const sf::Color SpokeTree::_COLOR_LINES_DEFAULT = sf::Color::Black ;

// Ratio of the length of the first line to the side length of the square window
const double SpokeTree::_RATIO_FIRST_LINE_TO_WINDOW = 0.5f ;

// Ratio of a line's length to the lengths of its parent
const double SpokeTree::_RATIO_LINE_SHRINK = 0.8f ;

// Not really mathematical ray, but rather more of a drawable and relative vector
// I named the class Ray due to the similarities, they both have starting point and continue in a direction
// A true mathematical ray could be represented using this class by simply using the terminal coordinates
// as a definition of the direction but without paying any attention to the implied magnitude
struct Ray : public sf::Drawable {

  const static int nEndpoints = 2 ;

  sf::Vector2f origin ;
  sf::Vector2f terminal ;

  sf::Vertex line[nEndpoints] ;

  Ray(double originX, double originY, double terminalX, double terminalY) :
    origin(sf::Vector2f(originX, originY)),
    terminal(sf::Vector2f(terminalX, terminalY)) {
    line[0] = origin ;
    line[1] = terminal ;
  }

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(line, nEndpoints, sf::Lines) ;
  }

} ; // struct Ray 

SpokeTree::SpokeTree(unsigned int windowSideLength, unsigned int recursionDepthMax, sf::Color color) :
  _colorLines(color),
  _lengthWindowSide(windowSideLength),
  _maxRecursionDepth(recursionDepthMax)
{
  _userModifierRadialSpokes = 0 ;
  _userModifierRecursionDepth = 0 ;
  _userModifierRatioLineShrink = 0.f ;
  _userModifierSpokeMode = FIXED ;
}

void SpokeTree::draw_fractal(sf::RenderTarget& target, sf::Vector2f cursor, unsigned int recursionDepth, double radBaseAngle) const {

  // Exit if max stack height is reached (confusingly labeled as "depth")
  if (recursionDepth >= _maxRecursionDepth + _userModifierRecursionDepth) return ;

  double radNewAngleReceiver, radAngleBetweenSpokes ;
  sf::Vector2f terminalCoordsTemp ;

  // Calculate the angle betwen spokes for this recursion depth
  radAngleBetweenSpokes = calculateRadAngleBetweenSpokes(recursionDepth) ;

  // For each spoke in the fractal...
  for(unsigned int iterationsRadialSpokes = 0; iterationsRadialSpokes < calculateRadialSpokesMax(recursionDepth); iterationsRadialSpokes++) {
    // Calculate the terminal coordinates of a new spoke
    terminalCoordsTemp = calculateDestinationCoordinates(
      recursionDepth,
      iterationsRadialSpokes,
      cursor,
      radBaseAngle,
      radNewAngleReceiver,
      radAngleBetweenSpokes,
      calculateLengthNextLine(recursionDepth)
    ) ;

    // Draw a Ray for each spoke    
    Ray spoke(cursor.x, cursor.y, terminalCoordsTemp.x, terminalCoordsTemp.y) ;
    target.draw(spoke) ;

    // Draw the fractal at each endpoint
    draw_fractal(
      target,
      terminalCoordsTemp,
      recursionDepth + 1, // Increment recursion depth
      radNewAngleReceiver
    ) ;
  }
}

void SpokeTree::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // Calculate inital spoke length from window height
  double xOrigin, xTerminal, yOrigin, yTerminal ;

  // Center horizontally
  xOrigin = xTerminal = _lengthWindowSide / 2 ;

  // Start from the bottom
  yOrigin = _lengthWindowSide ;

  // Use a constant ratio to determine the length of the first line
  yTerminal = _lengthWindowSide - calculateLengthNextLine(0) ;

  // Create the first line using class Ray : public Drawable
  Ray r(xOrigin, yOrigin, xTerminal, yTerminal) ;

  // Draw the rest of the fractal lmao
  // TODO: try 0 instead of 1
  // TODO: make this look nice
  draw_fractal(target,sf::Vector2f(xTerminal,yTerminal),1,M_PI/2) ;

  target.draw(r) ;
}

double SpokeTree::calculateRatioLineShrink(unsigned int recursionDepth) const {
  // Idea: approach 1? or pass 1?
  // TODO:: complete stub (or not?)
  return _RATIO_LINE_SHRINK + _userModifierRatioLineShrink ;
  //return (double)recursionDepth/(recursionDepth+2);
}

// Duplicate non-const qualified function
double SpokeTree::calculateRatioLineShrink(unsigned int recursionDepth) {
  return _RATIO_LINE_SHRINK + _userModifierRatioLineShrink ;
}

// Abstraction of a common operation: Does a map contain a given key or not?
template <class KeyType,class ValueType>
bool mapContainsKey(std::map<KeyType, ValueType> map, KeyType key) {
  return map.find(key) != map.end() ;
}

double SpokeTree::calculateRadAngleBetweenSpokes(unsigned int recursionDepth) {
  if (!mapContainsKey(_radAngleBetweenSpokesGivenRecursionDepth, recursionDepth)) {
    _radAngleBetweenSpokesGivenRecursionDepth[recursionDepth] = (2 * M_PI) / (calculateRadialSpokesMax(recursionDepth) + 1) ;
  }
  return _radAngleBetweenSpokesGivenRecursionDepth[recursionDepth] ;
}

double SpokeTree::calculateRadAngleBetweenSpokes(unsigned int recursionDepth) const {
  return (2 * M_PI) / (calculateRadialSpokesMax(recursionDepth) + 1) ;
}

double SpokeTree::calculateLengthNextLine(unsigned int recursionDepth) {
  // Case: lengthNextLine has not been previously calculated
  if (!mapContainsKey(_lengthLineNextGivenRecursionDepth,recursionDepth)){
    _lengthLineNextGivenRecursionDepth[recursionDepth] = calculateRatioLineShrink(recursionDepth) * calculateLengthNextLine(recursionDepth - 1) ;
  }
  // At this point, we can be sure that key recursionDepth has a proper value in the map
  return _lengthLineNextGivenRecursionDepth[recursionDepth] ;
}

double SpokeTree::calculateLengthNextLine(unsigned int recursionDepth) const {
  if (recursionDepth < 1) return (_lengthWindowSide * _RATIO_FIRST_LINE_TO_WINDOW)  ;

  return calculateRatioLineShrink(recursionDepth) * calculateLengthNextLine(recursionDepth - 1) ;
}

unsigned int SpokeTree::calculateRadialSpokesMax(unsigned int recursionDepth) const {
  switch(_userModifierSpokeMode) {
    case ARITHMETIC:
      return recursionDepth + _userModifierRadialSpokes ;
    case GEOMETRIC:
      return recursionDepth * _userModifierRadialSpokes ;
    case FIXED:
    default:
      return _userModifierRadialSpokes ;
  }
}

sf::Vector2f SpokeTree::calculateDestinationCoordinates(unsigned int recursionDepth, unsigned int iterationsRadialSpokes, sf::Vector2f& cursor, double radBaseAngle, double& radNewAngle, double radAngleBetweenSpokes, double lengthNextLine) const {

  radNewAngle = ( radAngleBetweenSpokes - (M_PI - radBaseAngle) ) + iterationsRadialSpokes * radAngleBetweenSpokes ;

  double destinationX = cursor.x + lengthNextLine * cos(radNewAngle) ;

  // Subtract because y-axis increases in opposite direction of basic cartesian system
  double destinationY = cursor.y - lengthNextLine * sin(radNewAngle) ;

  return sf::Vector2f(destinationX, destinationY) ;
}

// Public below this

void SpokeTree::setUserModifierRadialSpokes(int newValue) {
  printf("Set _userModifierRadialSpokes to %d\n", newValue) ;
  _userModifierRadialSpokes = newValue ;
}
int SpokeTree::getUserModifierRadialSpokes() {
  return _userModifierRadialSpokes ;
}

void SpokeTree::setUserModifierRecursionDepth(int newValue) {
  printf("Set _userModifierRecursionDepth to %d\n", newValue) ;
  _userModifierRecursionDepth = newValue ;
}

int SpokeTree::getUserModifierRecursionDepth() {
  return _userModifierRecursionDepth ;
}

void SpokeTree::setUserModifierRatioLineShrink(double newValue) {
  printf("Set _userModifierRatioLineShrink to %f\n", newValue) ;
  _userModifierRatioLineShrink = newValue ;
}
double SpokeTree::getUserModifierRatioLineShrink() {
  return _userModifierRatioLineShrink ;
}

void SpokeTree::setUserModifierSpokeMode(SpokeMode newValue) {
  _userModifierSpokeMode = newValue ;
}