/**********************************************************************
 *** N-Body Simulation *** ps3b-readme.txt ***
 **********************************************************************/

Name: Joel Savitz
OS: Arch Linux
Machine: A Custom Built PC
Text editor: vscode with vim keybindings
Hours to complete assignment: Probably like 3?
/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
I implemented a drawable physical body class and simulated two-dimensional
physical motion on each of these bodies by iterating over a vector of
smart pointers to body objects. After each iteration of the physics simulation,
I updated the displayed position of the planets.


/**********************************************************************
 *  If you created your own universe for extra credit, describe it
 *  here and why it is interesting.
 **********************************************************************/




/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
None

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
I used and = instead of a += operator at one point and it took me a bit of time to debug.
I was overwriting the position of the planets with their change in position instead of adding it.
I thought I was implementing the simulation mathematics incorrectly, so I did a bunch
of calculations in a spreadsheet, but it the issue turned out to be the incorrect use of the operator.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
 None!