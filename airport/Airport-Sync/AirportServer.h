/**
*  AirportServer.h
*  This class defines the methods called by the Airplanes
*/

#ifndef AIRPORT_SERVER_H
#define AIRPORT_SERVER_H

#include <mutex>
#include <random>

#include "AirportRunways.h"
#include <condition_variable>



class AirportServer
{
public:

	/**
	*  Default constructor for AirportServer class
	*/
	AirportServer()
	{
		// ***** Initialize any Locks and/or Condition Variables here as necessary *****

	} // end AirportServer default constructor


	  /**
	  *  Called by an Airplane when it wishes to land on a runway
	  */
	void reserveRunway(int airplaneNum, AirportRunways::RunwayNumber runway);

	/**
	*  Called by an Airplane when it is finished landing
	*/
	void releaseRunway(int airplaneNum, AirportRunways::RunwayNumber runway);


private:

	// Constants and Random number generator for use in Thread sleep calls
	static const int MAX_TAXI_TIME = 10; // Maximum time the airplane will occupy the requested runway after landing, in milliseconds
	static const int MAX_WAIT_TIME = 100; // Maximum time between landings, in milliseconds

	/**
	*  Declarations of mutexes and condition variables
	*/
	mutex runwaysMutex; // Used to enforce mutual exclusion for acquiring & releasing runways

	/**
	 *  ***** Add declarations of your own Locks and Condition Variables here *****
	 */

	static mutex mutex4L, mutex4R, mutex9, mutex14, mutex15L, mutex15R ;

	static mutex mutexLandingRequests ;
	static condition_variable cvLandingRequests ;

}; // end class AirportServer

#endif
