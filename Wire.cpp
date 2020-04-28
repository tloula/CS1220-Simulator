/**************************************************
File:		Wire.cpp
Author:		Trevor Loula
Date:		APR-2018
Purpose:	Wire class implementation
Course:		Cedarville University
			CS1220 Object Oriented Design w/ C++
			Dr. Keith Shomper
**************************************************/
#include "Wire.h"

Wire::Wire(std::string name, int index, int state, bool isOutput)
{
	this->name = name;
	this->index = index;
	this->state = state;
	this->isOutput = isOutput;
}

std::string Wire::getName() const
{
	return this->name;
}

int Wire::getIndex() const
{
	return this->index;
}

int Wire::getState() const
{
	return this->state;
}

std::vector<Gate* > Wire::getDrives() const
{
	return this->drives;
}

std::vector<Event > Wire::getHistory() const
{
	return this->history;
}

bool Wire::getIsOutput() const
{
	return this->isOutput;
}

void Wire::setState(int state)
{
	this->state = state;
}

void Wire::pushDrives(Gate * d)
{
	this->drives.push_back(d);
}

void Wire::pushHistory(Event e)
{
	this->history.push_back(e);
}

void Wire::popHistory()
{
	this->history.pop_back();
}

void Wire::pushFrontHistory(Event e)
{
	this->history.insert(this->history.begin(), e);
}