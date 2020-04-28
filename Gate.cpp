/**************************************************
File:		Gate.cpp
Author:		Trevor Loula
Date:		APR-2018
Purpose:	Gate class implementation
Course:		Cedarville University
			CS1220 Object Oriented Design w/ C++
			Dr. Keith Shomper
**************************************************/
#include "Gate.h"
#include "Wire.h"

Gate::Gate(Wire * in1, Wire * in2, Wire * out, int delay, int type)
{
	this->in1 = in1;
	this->in2 = in2;
	this->out = out;
	this->delay = delay;
	this->type = type;
}

Wire * Gate::getIn1() const
{
	return this->in1;
}

Wire * Gate::getIn2() const
{
	return this->in2;
}

Wire * Gate::getOut() const
{
	return this->out;
}

int Gate::getDelay() const
{
	return this->delay;
}

int Gate::getType() const
{
	return this->type;
}

int Gate::evaluate(int in1, int in2)
{
	switch (this->type)
	{
	case NOT:
		return notGate(in1);
		break;
	case AND:
		return andGate(in1, in2);
		break;
	case OR:
		return orGate(in1, in2);
		break;
	case NAND:
		return nandGate(in1, in2);
		break;
	case NOR:
		return norGate(in1, in2);
		break;
	case XOR:
		return xorGate(in1, in2);
		break;
	case XNOR:
		return xnorGate(in1, in2);
	default:
		printf("Invalid Gate Type.");
		return ERROR;
		break;
	}
}

int Gate::notGate(int in1)
{
	if (in1 == HIGH)	return LOW;
	if (in1 == LOW)		return HIGH;
	if (in1 == UNKNOWN)	return UNKNOWN;
						return ERROR;
}

int Gate::andGate(int in1, int in2)
{
	// Dr. Shomper's Three-Value Truth Table
	if (in1 == LOW && in2 == LOW)			return LOW;
	if (in1 == LOW && in2 == HIGH)			return LOW;
	if (in1 == LOW && in2 == UNKNOWN)		return LOW;
	if (in1 == HIGH && in2 == LOW)			return LOW;
	if (in1 == HIGH && in2 == HIGH)			return HIGH;
	if (in1 == HIGH && in2 == UNKNOWN)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == LOW)		return LOW;
	if (in1 == UNKNOWN && in2 == HIGH)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == UNKNOWN)	return UNKNOWN;
											return ERROR;
}

int Gate::orGate(int in1, int in2)
{
	// Dr. Shomper's Three-Value Truth Table
	if (in1 == LOW && in2 == LOW)			return LOW;
	if (in1 == LOW && in2 == HIGH)			return HIGH;
	if (in1 == LOW && in2 == UNKNOWN)		return UNKNOWN;
	if (in1 == HIGH && in2 == LOW)			return HIGH;
	if (in1 == HIGH && in2 == HIGH)			return HIGH;
	if (in1 == HIGH && in2 == UNKNOWN)		return HIGH;
	if (in1 == UNKNOWN && in2 == LOW)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == HIGH)		return HIGH;
	if (in1 == UNKNOWN && in2 == UNKNOWN)	return UNKNOWN;
											return ERROR;
}

int Gate::nandGate(int in1, int in2)
{
	if (in1 == LOW && in2 == LOW)			return HIGH;
	if (in1 == LOW && in2 == HIGH)			return HIGH;
	if (in1 == LOW && in2 == UNKNOWN)		return HIGH;
	if (in1 == HIGH && in2 == LOW)			return HIGH;
	if (in1 == HIGH && in2 == HIGH)			return LOW;
	if (in1 == HIGH && in2 == UNKNOWN)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == LOW)		return HIGH;
	if (in1 == UNKNOWN && in2 == HIGH)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == UNKNOWN)	return UNKNOWN;
	return ERROR;
}

int Gate::norGate(int in1, int in2)
{
	if (in1 == LOW && in2 == LOW)			return HIGH;
	if (in1 == LOW && in2 == HIGH)			return LOW;
	if (in1 == LOW && in2 == UNKNOWN)		return UNKNOWN;
	if (in1 == HIGH && in2 == LOW)			return LOW;
	if (in1 == HIGH && in2 == HIGH)			return LOW;
	if (in1 == HIGH && in2 == UNKNOWN)		return LOW;
	if (in1 == UNKNOWN && in2 == LOW)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == HIGH)		return LOW;
	if (in1 == UNKNOWN && in2 == UNKNOWN)	return UNKNOWN;
	return ERROR;
}

int Gate::xorGate(int in1, int in2)
{
	if (in1 == LOW && in2 == LOW)			return LOW;
	if (in1 == LOW && in2 == HIGH)			return HIGH;
	if (in1 == LOW && in2 == UNKNOWN)		return UNKNOWN;
	if (in1 == HIGH && in2 == LOW)			return HIGH;
	if (in1 == HIGH && in2 == HIGH)			return LOW;
	if (in1 == HIGH && in2 == UNKNOWN)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == LOW)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == HIGH)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == UNKNOWN)	return UNKNOWN;
	return ERROR;
}

int Gate::xnorGate(int in1, int in2)
{
	if (in1 == LOW && in2 == LOW)			return HIGH;
	if (in1 == LOW && in2 == HIGH)			return LOW;
	if (in1 == LOW && in2 == UNKNOWN)		return UNKNOWN;
	if (in1 == HIGH && in2 == LOW)			return LOW;
	if (in1 == HIGH && in2 == HIGH)			return HIGH;
	if (in1 == HIGH && in2 == UNKNOWN)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == LOW)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == HIGH)		return UNKNOWN;
	if (in1 == UNKNOWN && in2 == UNKNOWN)	return UNKNOWN;
	return ERROR;
}