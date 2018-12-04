/**********************************************************************
 *  Airport-readme template                                                   
 *  Airport Simulation (C++11 Concurrency)                       
 **********************************************************************/

Your name:

Operating system you're using (Linux, OS X, or Windows): Arch Linux

If Windows, which solution?: N/A

Text editor or IDE you're using: VSCode

Hours to complete assignment: 1-2

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
I used mutex locks to synchronize simulated airplane landings at an airport while avoiding crashes


 /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
I made sure to lock and unlock mutexes in a total ordering to avoid deadlocks.


/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
Based on the requested resource/runway, each thread would request the lock on different runways needed to avoid crashes.

I implemented this using a switch statement:

		switch(runway) {
			case AirportRunways::RUNWAY_4L:
				mutex4L.lock() ;
				mutex15L.lock() ;
				mutex15R.lock() ;
				break ;
			case AirportRunways::RUNWAY_4R:
				mutex4R.lock() ;
				mutex9.lock() ;
				mutex15L.lock() ;
				mutex15R.lock() ;
				break ;
			case AirportRunways::RUNWAY_9:
				mutex4R.lock() ;
				mutex9.lock() ;
				mutex15R.lock() ;
				break ;
			case AirportRunways::RUNWAY_14:
				mutex14.lock() ;
				break ;
			case AirportRunways::RUNWAY_15L:
				mutex4L.lock() ;
				mutex4R.lock() ;
				mutex15L.lock() ;
				break ;
			case AirportRunways::RUNWAY_15R:
				mutex4L.lock() ;
				mutex4R.lock() ;
				mutex9.lock() ;
				mutex15R.lock() ;
				break ;
		}

Notice that the locks are always ordered in the same order as the runways are listed in the switch statement.

The unlocks are done using the same method, but with the unlock member function being called.

 /**********************************************************************
 *  Briefly explain what you learned in the assignment.
 **********************************************************************/
Total ordering is important for mutexes in synchronized multi-threaded code.


/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
I spoke to Dr. Wilkes in his office a few times and he gave me good advice and guidance.


/**********************************************************************
 *  Describe any serious problems you encountered.  
 *  If you didn't complete any part of any assignment, 
 *  the things that you didn't do, or didn't get working.                  
 **********************************************************************/
No crashes yet...


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
I ran the program overnight to test it.