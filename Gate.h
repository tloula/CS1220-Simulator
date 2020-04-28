/**************************************************
File:		Gate.h
Author:		Trevor Loula
Date:		APR-2018
Purpose:	Gate class specification
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

class Gate {
	public:
		// Constructor
		Gate(	Wire *in1 = nullptr,
				Wire *in2 = nullptr,
				Wire *out = nullptr,
				int delay = 0,
				int type = UNKNOWN
		);
		// Accessors
		Wire*	getIn1()	const;
		Wire*	getIn2()	const;
		Wire*	getOut()	const;
		int		getDelay()	const;
		int		getType()	const;
		// Evaluate Gate Type And Execute Gate Function
		int		evaluate(int in1, int in2);
	private:
		// Gate Type Functions
		int notGate	(int in1);			// NOT	Gate Function
		int andGate	(int in1, int in2);	// AND	Gate Function
		int orGate	(int in1, int in2);	// OR	Gate Function
		int nandGate(int in1, int in2);	// NAND	Gate Function
		int norGate	(int in1, int in2);	// NOR	Gate Function
		int xorGate	(int in1, int in2);	// XOR	Gate Function
		int xnorGate(int in1, int in2);	// XNOR	Gate Function
		// Wires
		Wire *in1, *in2;	// Inputs as specified in the circuit file
		Wire *out;			// Output as specified in the circuit file
		// Gate Specs
		int delay;			// Delay as specified in the circuit file
		int type;			// Gate type as specified in the circuit file
};