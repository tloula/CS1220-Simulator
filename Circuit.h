/**************************************************
File:		Circuit.h
Author:		Trevor Loula
Date:		APR-2018
Purpose:	Circuit class specification
Course:		Cedarville University
			CS1220 Object Oriented Design w/ C++
			Dr. Keith Shomper
**************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "definitions.h"
#include "Wire.h"
#include "Gate.h"
#include "Event.h"

typedef std::priority_queue<Event> Queue;

class Circuit
{
public:
	// Default Constructor
	Circuit();
	// Get user input
	void getFilename();
	// Read data from circuit and vector files
	void readCircuit();
	void readVector();
	// Simulate
	void simulate();
	// Print wire traces
	void printTraces();
	// Accessors
	std::string getCircuitName()		const;
	std::string getVectorName()			const;
	std::string	getCircuitDescription()	const;
	int			getCurrentTime()		const;
	// Mutators
	void setCircuitName			(std::string name = "");
	void setVectorName			(std::string name = "");
	void setCircuitDescription	(std::string description = "");
	void setCurrentTime			(int time = 0);
private:
	// Functions
	int computeGateType(const char *t);
	void printState(Event e);
	void insertWire(Wire* w);
	void internalWire(int in1 = 0, int in2 = 0, int out = 0);
	// Parse circuit and vector Files
	void parseCircuit(std::string line);
	void parseVector(std::string line);
	// Data Members
	std::string	circuitName;
	std::string	vectorName;
	std::string circuitDescription;
	std::vector <Wire *> wires;
	std::vector <Gate *> gates;
	int			currentTime;
	int			eventCnt;
	Queue		q;
};
