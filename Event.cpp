/**************************************************
File:		Event.cpp
Author:		Trevor Loula
Date:		APR-2018
Purpose:	Event class implementation
Course:		Cedarville University
			CS1220 Object Oriented Design w/ C++
			Dr. Keith Shomper
**************************************************/
#include "Event.h"

Event::Event(Wire* wire, int time, int state, int creationCount)
{
	this->wire = wire;
	this->time = time;
	this->state = state;
	this->creationCount = creationCount;
}

Wire* Event::getWire()
{
	return this->wire;
}

int Event::getTime() const
{
	return this->time;
}

int Event::getState() const
{
	return this->state;
}

int Event::getCreationCount() const
{
	return this->creationCount;
}

bool operator<(const Event & l, const Event & r)
{
	if (l.time == r.time) {
		return l.creationCount > r.creationCount;
	}
	else {
		return l.time > r.time;
	}
}
