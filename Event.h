/**************************************************
File:		Event.h
Author:		Trevor Loula
Date:		APR-2018
Course:		Cedarville University
			CS1220 Object Oriented Design w/ C++
			Dr. Keith Shomper
**************************************************/
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "definitions.h"

class Wire;

class Event
{
public:
	// Constructor
	Event(	Wire *wire = nullptr,
			int time = 0,
			int state = UNKNOWN,
			int creationCount = 0);
	// Accessors
	Wire* getWire();
	int getTime()			const;
	int getState()			const;
	int getCreationCount()	const;
	friend bool operator<(const Event &l, const Event &r);
private:
	// Data Members
	Wire *wire;
	int time;
	int state;
	int creationCount;
};