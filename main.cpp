/**************************************************
File:		main.cpp
Author:		Trevor Loula
Date:		APR-2018
Purpose:	Main startup program
Course:		Cedarville University
			CS1220 Object Oriented Design w/ C++
			Dr. Keith Shomper
**************************************************/
#include "Circuit.h"

int main() {

	std::string restart;

	do {

		Circuit c;

		// 1. parse the circuit description to build the circuit
		c.readCircuit();

		// 2. Parse the vector description to set up the simulation
		c.readVector();

		// 3. Run simulation
		c.simulate();

		// 4. Print output
		c.printTraces();

		do {
			printf("Would you like to run again? [y/n]\n");
			std::cin >> restart;
		} while ((restart != "y") && (restart != "n"));

	} while (restart == "y");

	return 0;
}