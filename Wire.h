/**************************************************
File:		Wire.h
Author:		Trevor Loula
Date:		APR-2018
Purpose:	Wire class specification
Course:		Cedarville University
			CS1220 Object Oriented Design w/ C++
			Dr. Keith Shomper
**************************************************/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Event.h"
#include "definitions.h"

class Gate;

class Wire {
	public:
		// Constructor
		Wire(	std::string name = "",
				int index = 0,
				int state = UNKNOWN,
				bool isOutput = false);
		// Accessors
		std::string			getName()		const;
		int					getIndex()		const;
		int					getState()		const;
		std::vector<Gate *>	getDrives()		const;
		std::vector<Event >	getHistory()	const;
		bool				getIsOutput()	const;
		// Mutators
		void setState			(int state = UNKNOWN);
		void pushDrives			(Gate * d);
		void pushHistory		(Event e);
		void popHistory			();
		void pushFrontHistory	(Event e);
		// Smart Accessors
	private:
		// Wire Specs
		std::string			name;			// Name as specified in the circuit file
		int					index;			// Index as specified in the circuit file
		int					state;			// State as specified in the vecor file
		std::vector<Gate *> drives;			// Gates driven by wire
		std::vector<Event > history;		// History of the wires events
		bool				isOutput;
};