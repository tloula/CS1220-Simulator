/**************************************************
File:		definitions.h
Author:		Trevor Loula
Date:		APR-2018
Purpose:	Define gate and wire types
Course:		Cedarville University
			CS1220 Object Oriented Design w/ C++
			Dr. Keith Shomper
**************************************************/
#pragma once

// Wire States
#define NULLWIRE	-2
#define UNKNOWN		-1
#define LOW			0
#define	HIGH		1

// Common Error
#define ERROR		2

// Gate Types
#define NOT			3
#define AND			4
#define OR			5
#define NAND		6
#define NOR			7
#define XOR			8
#define XNOR		9

// Wires
#define INPUT		10
#define OUTPUT		11