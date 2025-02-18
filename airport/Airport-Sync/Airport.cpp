/**
*  Airport driver program
*/

#include <iostream>
#include <thread>
#include <vector>

#include "AirportServer.h"
#include "AirportRunways.h"
#include "Airplane.h"

using namespace std;

int main(void)
{
	AirportServer as;

	vector<thread> apths; // Airplane threads

						  // Create and launch the individual Airplane threads
	for (int i = 1; i <= AirportRunways::NUM_AIRPLANES; i++)
	{
		Airplane* ap = new Airplane(i, &as);

		apths.push_back(thread([](Airplane * ap){ap->land();}, ap));
	}

	// Wait for all Airplane threads to terminate (shouldn't happen!)
	for (auto& th : apths)
	{
		th.join();
	}

	return 0;

} // end main
