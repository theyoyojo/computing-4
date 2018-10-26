/**********************************************************************
 *  N-Body Simulation ps3a-readme.txt
 **********************************************************************/

Name: Joel Savitz
OS: Arch Linux
Text editor: Microsoft Visual Studio Code
Hours to complete assignment: Probably around 2ish?

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
I implemented a class to represent a physical body in 2 dimensional space
I implemented a simple mechanism to load body properties from stdin
I implemented a mechanism to convert coordinates relative to the center of
a canvas scaled to a given "universe size" to coordinates that will display
a body in the correct position.

  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
The only relatively tricky aspect of this assignment was  the coordinate conversion.
I first divided a coordinate by the universe size to get the ratio of the position of
the body to the size of canvas (relative to the size of the central origin)
Then, I multiplied that value by half of the window dimension in that particular direction to scale
the ratio to a quadrant of the window, and finally I added half of the window dimension to that value to
get the coordinate relative to the top-left corner of the window.


/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
What follows is the code that implements the algorithm described in the previous section:

displayCoordinates.x = Body::windowWidth/2 + Body::windowWidth/2 * ( (cartesianCoordinates.x) / Body::universeSize ) ;
displayCoordinates.y = (Body::windowHeight/2 + Body::windowHeight/2 * ( (cartesianCoordinates.y) / Body::universeSize ) ) ;

I also overloaded the input stream operator in body.hpp, like so:


  friend std::istream& operator >>(std::istream& istream, Body& body) {

    istream >> body._xPosition ;
    istream >> body._yPosition ;
    istream >> body._xVelocity;
    istream >> body._yVelocity;
    istream >> body._mass ;
    istream >> body._spriteFilename ;

    return istream ;
  }

/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
None

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
Some namespace errors but they were not very serious.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
None