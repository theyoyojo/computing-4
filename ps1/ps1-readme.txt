/**********************************************************************
 *  ps1-readme template                                                   
 *  Recursive Graphics (Pythagoras tree)                       
 **********************************************************************/

Your name: Joel Savitz

Operating system you're using (Linux, OS X, or Windows): Linux (Arch distribution)

If Windows, which solution?:

Text editor or IDE you're using: vscode

Hours to complete assignment: ~1-3

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
I drew upon my experience implementing the sierpinski triangle and another
recursive SFML graphic program inspired by the previous years' ps1 assignment
in order to create this program. I wrote a program that draws the Pythagoras
tree and also allows the user to manipulate a key parameter via the keyboard
in order to make the entire design bend and wave. I also implemented two animations,
both of which are triggerable via the keyboard.

 /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
I used a class to contain all necessary information to draw the Pythagoras
tree recursively, and I also created a helper class I called Square as an
abstraction to conveniently generate squares. The calculations for the transformation
of the shapes were done manually using basic trigonometry.

/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
  In order to draw an arbitrary square, I created a Square class that took
  as parameters to it's constructor an ordered pair I called "origin" and another
  ordered pair I called "offsetVector," both represented using the sf::Vector2f type
  The first pair defines the coordinates from which to begin drawing and the second
  pair defines a magnitude (in pixels) and a direction (in radians) that defines use in order to calculate
  the location of the vertex opposite the origin point in relative terms. 
  
  The following code segment is used to determine the three the coordinates of on-origin points :
  
  _branchBottom = sf::Vector2f(origin.x + _sideLength * cos(offsetDirectionRadians - M_PI/4 ), origin.y - _sideLength * sin(offsetDirectionRadians - M_PI/4)) ;
  _branchTop = sf::Vector2f(origin.x + _sideLength * cos(offsetDirectionRadians + M_PI/4), origin.y - _sideLength * sin(offsetDirectionRadians + M_PI/4)) ;
  _terminal = sf::Vector2f(origin.x + offsetMagnitude * cos(offsetDirectionRadians),  origin.y - offsetMagnitude * sin(offsetDirectionRadians)) ;

  The code can be found in the Square() constructor in PTree.cpp

  I will skip over the details of how I exactly implemented the Pythagoras tree, as I'm sure that
  whomever is reading this is fairly tired of seeing that same description over and over, but I will
  mention that I calculate the placement of the two child squares based on a single angle between
  the left child square and it's parent. By manipulating that value, I was able to spin the entire animation

  The following code was used to cause the Pythagoras Tree to wave back and forth, as if in the wind:

  // Retain the value of psi between function calls
  static double psi = 0 ;

  // Animation should have period of 4 seconds, so each second, psi should increment by 2pi/4
  const double deltaPsiPerSecond = M_PI / 2 ;

  // Using psi, calculate the change in angle for the current frame
  double deltaTheta = sin(psi) / 1024 ;
  
  // Apply the shift in angle
  shift(deltaTheta) ;

  // increment psi using the delta per second divided by the frames per second (change per frame)
  psi += deltaPsiPerSecond / FPS ;

  // If psi has gone around the circle, reset it
  if (psi >= 2 * M_PI) {
    psi = 0 ;
  }

  This is the entire body of the updateWaveAnimation() function which can be found in PTree.cpp
  The shift() function applies the change in angle to the angle discussed above.

  By taking the sine of a second angle variable that behaves like a line spinning around a unit circle,
  I can simulate a sort of breathing sequence, causing the tree to wave back and forth in a semi-natural manner

  The wave animation can be activated by pressing the "A" key on the keyboard

 /**********************************************************************
 *  Briefly explain what you learned in the assignment.
 **********************************************************************/
 I was able to develop and refine my general object-oriented software
 development skills.


/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
I did not need any help. I did, of course, consult the SFML wiki.


/**********************************************************************
 *  Describe any serious problems you encountered.  
 *  If you didn't complete any part of any assignment, 
 *  the things that you didn't do, or didn't get working.                  
 **********************************************************************/
Working with an inverted y-axis was a bit tricky at first, but I adjusted.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

ACTUAL DOCUMENTATION OF THE PROGRAM:

I will describe how to use the functionality I have implemented outside of the
assignment specification.

The additional functionality of the program can be controlled using the keyboard.

Q:
  Quits the program

Left:
  Shifts the tree to the left by a small around (and will go all the way back around).

Right:
  Shifts the tree to the right by a small around (and will go all the way back around).

A:
  Triggers the rotation animation mode. While in this mode, the tree will spin clockwise.

B:
  Triggers the wave animation mode. While in this mode, the tree will wave back and forth
  a small amount with a period of 4 seconds to complete a full wave.

Space:
  Ends all animations.

Note: Manual shifting of the tree using the arrow keys will still work while an animation is active