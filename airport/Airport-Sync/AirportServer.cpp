#include <iostream>
#include <thread>
#include <condition_variable>

#include "AirportServer.h"

mutex AirportServer::mutex4L ;
mutex AirportServer::mutex4R ;
mutex AirportServer::mutex9 ;
mutex AirportServer::mutex14 ;
mutex AirportServer::mutex15L ;
mutex AirportServer::mutex15R ; 

/**
*  Called by an Airplane when it wishes to land on a runway
*/
void AirportServer::reserveRunway(int airplaneNum, AirportRunways::RunwayNumber runway)
{
	// Acquire runway(s)
	{  // Begin critical region

		//unique_lock<mutex> runwaysLock(runwaysMutex);

		//runwaysMutex.lock() ;

		/**
		 *  ***** Add your synchronization here! *****
		 */

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
		//cout << "TEST2" << endl ;

		// Check status of the airport for any rule violations
		AirportRunways::checkAirportStatus(runway);

		//runwaysLock.unlock();

	} // End critical region

	// obtain a seed from the system clock:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	// Taxi for a random number of milliseconds
	std::uniform_int_distribution<int> taxiTimeDistribution(1, MAX_TAXI_TIME);
	int taxiTime = taxiTimeDistribution(generator);

	{
		lock_guard<mutex> lk(AirportRunways::checkMutex);

		cout << "Airplane #" << airplaneNum << " is taxiing on Runway " << AirportRunways::runwayName(runway)
			 << " for " << taxiTime << " milliseconds\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(taxiTime));

} // end AirportServer::reserveRunway()


 /**
  *  Called by an Airplane when it is finished landing
  */
void AirportServer::releaseRunway(int airplaneNum, AirportRunways::RunwayNumber runway)
{
	// Release the landing runway and any other needed runways
	{ // Begin critical region

		//unique_lock<mutex> runwaysLock(runwaysMutex);

		{
			lock_guard<mutex> lk(AirportRunways::checkMutex);

			cout << "Airplane #" << airplaneNum << " is releasing any needed runway(s) after landing on Runway "
				 << AirportRunways::runwayName(runway) << endl;
		}

		/**
		*  ***** Add your synchronization here! *****
		*/

		// Update the status of the airport to indicate that the landing is complete
		AirportRunways::finishedWithRunway(runway);

		switch(runway) {
			case AirportRunways::RUNWAY_4L:
				mutex4L.unlock() ;
				mutex15L.unlock() ;
				mutex15R.unlock() ;
				break ;
			case AirportRunways::RUNWAY_4R:
				mutex4R.unlock() ;
				mutex9.unlock() ;
				mutex15L.unlock() ;
				mutex15R.unlock() ;
				break ;
			case AirportRunways::RUNWAY_9:
				mutex4R.unlock() ;
				mutex9.unlock() ;
				mutex15R.unlock() ;
				break ;
			case AirportRunways::RUNWAY_14:
				mutex14.unlock() ;
				break ;
			case AirportRunways::RUNWAY_15L:
				mutex4L.unlock() ;
				mutex4R.unlock() ;
				mutex15L.unlock() ;
				break ;
			case AirportRunways::RUNWAY_15R:
				mutex4L.unlock() ;
				mutex4R.unlock() ;
				mutex9.unlock() ;
				mutex15R.unlock() ;
				break ;
		}

		//runwaysLock.unlock();
		//runwaysMutex.unlock() ;

	} // End critical region

	// obtain a seed from the system clock:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	// Wait for a random number of milliseconds before requesting the next landing for this Airplane
	std::uniform_int_distribution<int> waitTimeDistribution(1, MAX_WAIT_TIME);
	int waitTime = waitTimeDistribution(generator);

	{
		lock_guard<mutex> lk(AirportRunways::checkMutex);

		cout << "Airplane #" << airplaneNum << " is waiting for " << waitTime << " milliseconds before landing again\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));

} // end AirportServer::releaseRunway()
