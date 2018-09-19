/**********************************************************************
 *  ps0-readme template                                                   
 *  Hello World Assignment                       
 **********************************************************************/

Your name: Joel Savitz

Operating system you're using (Linux, OS X, or Windows): Arch Linux (WM: i3)

If Windows, which solution?: N/A

Text editor or IDE you're using: vscode (with vim keybindings)

Hours to complete assignment: Around 1 to 2

/**********************************************************************
 *  List some information (optionally) to help me get to know you.
 **********************************************************************/

Did you take Computing I at UML? Yes, I did.

 - If yes, who was your instructor? Dr. David Adams

 - If no, where did you transfer from?



/**********************************************************************
 *  Part of Assignment 0 is to read the information on Academic
 *  Integrity at the course home page.
 *
 *  If you haven't done this, please do so now.
 *
 *  Follow the link to the University policy on Academic Integrity,
 *  and answer the following question:
 *
 * There are six examples of academic misconduct, labeled (a) through
 * (f). Other than (a), "Seeks to claim credit for the work or efforts
 * of another without authorization or citation," which of these do you
 * think would most apply to this class, and why? Write approx. 100
 * words.
 *
 * Note: there is no single correct answer to this. I am looking for
 * your opinion.
 **********************************************************************/
In my opinion, the final item, "(f) Assists other students in any of these acts."
is the most applicable to this class, as it not only includes items (a) through (e),
but it creates a culture of academic dishonesty that discredits class as a whole,
the integrity of the instructor's work, and the reputation of the computer science
department as a whole. People tend to follow each other's example when deciding
how to behave.


/**********************************************************************
 *  List whatever help (if any) you received from TAs, the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
None. Just the SFML documentation.


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
None


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

Dependencies: SFML, GNU Make

How to build
cd into project directory
$ make
The resulting binary is called "app"

To run the app:
$./app 

Documentation:

This program demonstrates the basic capabilities of SFML using a soccer ball
sprite that bounces around the window.

Left arrow key: Increase horizontal velocity by 10

Right arrow key: Decrease horizontal velocity by 10

Down arrow key: Increase vertical velocity by 10 (down is the positive direction)

Up arrow key: Decrease vertical velocity by 10

The program will print current velocity values to stdout after every refresh of the
SFML window.

Explanation of stdout output
Vx = horizontal velocity
Vy = vertical velocity
Units:

How this program fulfils the spec:
1 pt file name correct
> Source file is named main.cpp

1 pt for SFML window being displayed
> The window will be displayed when the application is executed

1 pt for image
> I included a soccer ball

1 pt for image being in moving sprite
> The sprite changes it's velocity when the user presses arrow keys (see Documentation above)

1 pt for sprite changing direction or somehow responding to keystrokes
> Same response as last item

1 pt for additional feature (explain in README)
> The sprite will continue to change it's position after every refresh according to the data
stored in it's Ball object representation. It also bounces off the window borders.

2 pt screenshot of just SFML window included
> See screenshot_tearing_due_to_simulated_motion.png

2 pt README complete
> See all of the above