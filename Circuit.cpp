/**************************************************
File:		Circuit.cpp
Author:		Trevor Loula
Date:		APR-2018
Purpose:	Circuit class implementation
Course:		Cedarville University
			CS1220 Object Oriented Design w/ C++
			Dr. Keith Shomper
**************************************************/
#include "Circuit.h"

Circuit::Circuit()
{
	wires.push_back(nullptr);
	currentTime = 0;
	eventCnt = 0;
}

void Circuit::getFilename()
{
	// Get user input and store in tmp
	std::string filename;	// File to open
	printf("What is the name of the circuit test file (base name only):");
	std::cin >> filename;

	// Check if entire circuit name was entered, or just a number; make necessary corrections
	if (filename.length() <= 1) {
		if (atoi(filename.c_str()) >= 0 && atoi(filename.c_str()) <= 8) {
			this->circuitName = "circuit" + filename + ".txt";
			this->vectorName = "circuit" + filename + "_v.txt";
		}
	}
	else {
		this->circuitName = filename + ".txt";
		this->vectorName = filename + "_v.txt";
	}
}

void Circuit::readCircuit() {
	std::ifstream	in;		// File to open
	std::string		line;	// Stores each line from file

	do {					// Continue to ask for filename until file sucessfully opens
		getFilename();

		in.open("CircuitFiles/" + circuitName);

		if (!in.is_open()) {		// If the file failed to open
			in.open(circuitName);	// Check the root directory as well
			if (!in.is_open()) {	// If the file still fails to open
				printf("Error opening circuit file %s.\n", circuitName.c_str());
			}
		}
	} while (!in.is_open());

	// Parse each line of the circuit
	while (!in.eof())
	{
		std::getline(in, line);
		parseCircuit(line.c_str());
	}
	in.close();

	// Fill in missing wires
	// Since it is easier to add a EMPTY wire than to create exception every time I loop through the wires vector
	for (int i = 0; i < wires.size(); i++) {
		if (wires.at(i) == NULL) {
			Wire * w = new Wire("EMPTY", i, UNKNOWN, false);
			insertWire(w);
		}
	}
}

void Circuit::readVector()
{
	std::ifstream	in;		// File to open
	std::string		line;	// Stores each line from file

	in.open("CircuitFiles/"+vectorName);

	if (!in.is_open()) {		// If the file failed to open
		in.open(vectorName);	// Check the root directory as well
		if (!in.is_open()) {	// If the file still fails to open
			printf("Error opening vector file %s.\n", vectorName.c_str());
			system("pause");
			exit(1);
		}
	}

	// Parse each line of the vector
	while (!in.eof())
	{
		std::getline(in, line);
		parseVector(line);
	}
	in.close();
}

void Circuit::parseCircuit(std::string line)
{
	if (!line.empty()) {				// Don't run if line is empty

		try {

			Wire* w;
			Gate* g;

			const char *row = line.c_str();	// Entire line being scanned

			// Gate and Wire Variables
			char description[25];
			char type[6];
			char name[20];
			char delay[5];
			int index;
			int in1;
			int in2;
			int out;

			if (line.find("CIRCUIT") != std::string::npos) {				// Get description of circuit from first line
				sscanf(row, "CIRCUIT %s", description);
				this->circuitDescription = description;
			}
			else if (line.find("INPUT") != std::string::npos) {			// INPUT

				sscanf(row, "INPUT %s%i", name, &index);					// Scan line into respective variables
				w = new Wire(name, index, UNKNOWN, false);					// Create new wire with data
				insertWire(w);												// Push new wire into wire vector
			}
			else if (line.find("OUTPUT") != std::string::npos) {		// OUTPUT
				sscanf(row, "OUTPUT %s%i", name, &index);					// Scan line into respective variables
				w = new Wire(name, index, UNKNOWN, true);					// Create new wire with data
				insertWire(w);												// Push new wire into wire vector
			}
			else if (line.find("NOT") != std::string::npos) {			// NOT GATE
				sscanf(row, "%s%s%i%i", type, delay, &in1, &out);			// Scan line into respective variables

				internalWire(in1, 0, out);										// Create any necessary internal wires

				std::string d = delay;											// Save delay as string in order to use string member functions

				if (computeGateType(type) != UNKNOWN) {
					g = new Gate(wires.at(in1), wires.at(in1), wires.at(out), std::stoi(d.substr(0, d.size() - 2)), computeGateType(type));	// Create new gate with data
					this->gates.push_back(g);									// Push new gate into gate vector
					this->wires.at(in1)->pushDrives(g);							// Update wire drives
				}
			}
			else {																// All other gates
				sscanf(row, "%s%s%i%i%i", type, delay, &in1, &in2, &out);		// Scan line into respective variables

				internalWire(in1, in2, out);									// Create any necessary internal wires

				std::string d = delay;											// Save delay as string in order to use string functions

				if (computeGateType(type) != UNKNOWN) {
					g = new Gate(wires.at(in1), wires.at(in2), wires.at(out), std::stoi(d.substr(0, d.size() - 2)), computeGateType(type));	// Create new gate with data
					this->gates.push_back(g);									// Push new gate into gate vector
					this->wires.at(in1)->pushDrives(g);							// Update wire drives
					this->wires.at(in2)->pushDrives(g);
				}
			}
		}
		catch (...) {
			printf("Invalid line in circuit file: %s\n", circuitName.c_str());
		}
	}
}

void Circuit::parseVector(std::string line)
{
	try {
		Event e;
		Wire* w = wires.at(0);

		// Added = wires.at(0) on APR-26-2020 to fix "potentially uninitialized local pointer variable 'w' used" error

		const char *row = line.c_str();

		// INPUT Variable-s
		char name[20];
		int time;
		char origState;
		int state;

		if (line.find("VECTOR") != std::string::npos) {				// Ignore first line
			return;
		}
		else if (line.find("INPUT") != std::string::npos) {			// INPUT

			sscanf(row, "INPUT %s %i %c", name, &time, &origState);	// Scan line into respective variables

			// Find the wire that the vector is referencing
			std::string wName = name;
			for (int i = 1; i < wires.size(); i++) {
				if (wires.at(i)->getName() == wName) {
					w = wires.at(i);
				}
			}

			// Account for unknown state in the vector
			if (origState == 'X') {
				state = UNKNOWN;
			}
			else {
				state = origState - 48;
			}

			e = Event(w, time, state, eventCnt++);			// Create event and increment eventCnt
			this->q.push(e);								// Push new event into queue
		}
		else if (line.empty()) {							// Ignore blank lines
		}
		else {
			printf("Invalid line in vector file: %s\n", getVectorName().c_str());
		}
	}
	catch (...){
		printf("Invalid line in vector file: %s\n", getVectorName().c_str());
	}
}

void Circuit::simulate() {

	printf("\nSimulating %s: %s\n\n", getCircuitName().c_str(), getCircuitDescription().c_str());

	Event e;
	Gate *g;
	Wire *w;

	while (!q.empty()) {
		e = q.top();										// Grab the top event from the queue
		q.pop();
		w = e.getWire();									// Wire effected by event
		w->setState(e.getState());							// Set current state of wire based off event state

		for (int i = 0; i < w->getDrives().size(); i++) {	// Loop through all the gates that the wire is driving
			g = w->getDrives().at(i);						// Grab a gate from the vector, g is gate effected by wire change
			int eval = g->evaluate(g->getIn1()->getState(), g->getIn2()->getState());			// Evaluate gate with new input

			if (e.getTime() + g->getDelay() <= 60) {											// Stop adding events to queue if their time exceeds 60
				Event ne = Event(g->getOut(), e.getTime() + g->getDelay(), eval, eventCnt++);	// Create a new event
				q.push(ne);																		// Add new event to queue
			}													
		}
		if (!w->getHistory().empty()) {									// If the history isn't empty, check last event
			if (w->getHistory().back().getState() != e.getState()) {	// Only push event onto wire history if it changed the state
				if (w->getHistory().back().getTime() == e.getTime()) {	// If the last event on the wire's history is at the same time as the new event, delete the last event and push the new event
					w->popHistory();
					w->pushHistory(e);
				}
				else {
					w->pushHistory(e);
				}
			}
		}
		else {															// History is empty, push event
			w->pushHistory(e);
		}
	}
}

void Circuit::printTraces() {

	printf("Wire traces:\n");

	std::vector<Event> ve;								// Vector containg all the current wire's events
	Event e;											// Current event
	Event ne;											// Next event
	int maxTime = 0;									// Max time of simulation in ns

	// Find the max trace time
	for (int i = 1; i < wires.size(); i++) {			// i being wire index
		ve = wires.at(i)->getHistory();
		for (int j = 0; j < ve.size(); j++) {			// j being event index
			if (ve.at(j).getTime() > maxTime) {			// If the curent events time is farther than the max
				maxTime = ve.at(j).getTime();			// Update max, add on 2 so that the print shows the last event
			}
		}
	}
	++maxTime;											// Incriment max time so that the traces show the last event

	// Find out how long the longest wire name is in order to line up all the wire traces
	int longestName = 0;
	for (int i = 1; i < wires.size(); i++) {				// Loop through all wires
		if (wires.at(i)->getName().size() > longestName && wires.at(i)->getName() != "InternalWire" && wires.at(i)->getName() != "EMPTY") {	// If the current wire's name is longer
			longestName = wires.at(i)->getName().size();	// Set longest name to the current wire's name's length
		}
	}

	for (int i = 1; i < wires.size(); i++) {				// Loop through all the wires, i is the wires index
		if (wires.at(i)->getName() != "InternalWire" && wires.at(i)->getName() != "EMPTY") {		// Ignore ghost and EMPTY wires

			for (int j = 0; j < longestName - wires.at(i)->getName().size(); j++)	// Print possible spaces before wireName
			{
				printf(" ");
			}

			printf("%s: ", wires.at(i)->getName().c_str());		// Print wire name i.e. "A: "

			int currentEventIndex = 0;
			int currentEventTime = 0;
			int timeLimit;

			if (wires.at(i)->getHistory().size() > 0) {							// If there are events in the vector, check to see if the first event is at time zero
				if (wires.at(i)->getHistory().at(0).getTime() != 0) {			// If the first event doesn't start at time zero, everything before it is unknown
					Event unknown = Event(wires.at(i), 0, UNKNOWN, eventCnt++);	// Create event to display unknown values before real events start
					wires.at(i)->pushFrontHistory(unknown);						// Insert new event to the front of the vector
				}
			}
			else {															// If there are no events, add unknown event
				Event unknown = Event(wires.at(i), 0, UNKNOWN, eventCnt++);	// Create event to display unknown values before real events start
				wires.at(i)->pushFrontHistory(unknown);						// Insert new event to the front of the vector
			}

			ve = wires.at(i)->getHistory();										// Vector of Events

			if (ve.size() > 1) {							// If there is more than one event
				timeLimit = ve.at(1).getTime();				// Set the time limit to the time of the second event
			} else {
				timeLimit = maxTime;						// If not, set the time limit to the max time
			}

			for (int j = 0; j < maxTime; j++) {				// Loops through each ns, j being each ns
				if (j < timeLimit) {						// If the current time is less than the next event
					printState(ve.at(currentEventIndex));	// Print Output
				} else {									// Time limit reached
					++currentEventIndex;					// Load the next event
					if (currentEventIndex + 1 < ve.size()) {// If there are still more events, check the next one
						timeLimit = ve.at(currentEventIndex + 1).getTime();	// Set the time limit to the time of the next event
						printState(ve.at(currentEventIndex));	// Print Output
					} else {
						timeLimit = maxTime;					// If there are no more events, then the time limit is the max
						printState(ve.at(currentEventIndex));	// Print Output
					}
				}
			}
			printf("\n\n");
		}
	}
	for (int j = 0; j < longestName; j++)	// Print spaces to align numbers with wire traces
	{
		printf(" ");
	}
	printf("  ");
	for (int i = 0; i < maxTime; i++) {		// Print timing numbers (i.e. 0    5    0    5)
		if (i%5 == 0) {
			printf("%i", i%10);
		} else {
			printf(" ");
		}
	}
	printf("\n");
}

// Accessors
std::string Circuit::getCircuitName() const
{
	return this->circuitName;
}

std::string Circuit::getVectorName() const
{
	return this->vectorName;
}

std::string Circuit::getCircuitDescription() const
{
	return this->circuitDescription;
}

int Circuit::getCurrentTime() const
{
	return this->currentTime;
}

// Mutators
void Circuit::setCircuitName(std::string name)
{
	this->circuitName = name;
}

void Circuit::setVectorName(std::string name)
{
	this->vectorName = name;
}

void Circuit::setCircuitDescription(std::string description)
{
	this->circuitDescription = description;
}

void Circuit::setCurrentTime(int time)
{
	this->currentTime = time;
}

int Circuit::computeGateType(const char *t) {
	std::string type = t;
	if (type == "NOT")
		return NOT;
	else if (type == "AND")
		return AND;
	else if (type == "OR")
		return OR;
	else if (type == "NAND")
		return NAND;
	else if (type == "NOR")
		return NOR;
	else if (type == "XOR")
		return XOR;
	else if (type == "XNOR")
		return XNOR;
	else {
		printf("Invalid gate type: %s.\nIgnoring gate.\n", t);
		return UNKNOWN;
	}
}

void Circuit::printState(Event e)
{
	switch (e.getState())
	{
	case NULLWIRE:
		printf("N");
		break;
	case LOW:
		printf("_");
		break;
	case HIGH:
		printf("-");
		break;
	case ERROR:
		printf("E");
		break;
	case UNKNOWN:
		printf("x");
		break;
	default:
		printf("D");
		break;
	}
}

void Circuit::insertWire(Wire* w) {
	// The purpose of this function is to ensure that all the wires are in the wire vector with their vector index matching the index in the circuit desctiption

	if (this->wires.size() <= w->getIndex()) {	// If the wire's index won't fit in the vector
		this->wires.resize(w->getIndex() + 1);	// Resize the vector so that it will fit
	}
	this->wires.at(w->getIndex()) = w;			// Since we know that the wire will fit at its proper index now, go ahead and insert it
}

void Circuit::internalWire(int in1, int in2, int out) {
	// Check each wire (in1, in2, out) to make sure that they exist, if they don't, create a new InternalWire
	// If the wires index doesn't exist, create index
	if (in1 >= wires.size()) {
		wires.resize(in1 + 1);
	}
	if (in2 >= wires.size()) {
		wires.resize(in2 + 1);
	}
	if (out >= wires.size()) {
		wires.resize(out + 1);
	}
	// If a wire doesn't exist at the index, create wire
	if (in1 != 0 && this->wires.at(in1) == 0) {
		Wire * w = new Wire("InternalWire", in1, UNKNOWN, false);
		insertWire(w);
	}
	if (in2 != 0 && this->wires.at(in2) == 0) {
		Wire * w = new Wire("InternalWire", in2, UNKNOWN, false);
		insertWire(w);
	}
	if (out != 0 && this->wires.at(out) == 0) {
		Wire * w = new Wire("InternalWire", out, UNKNOWN, false);
		insertWire(w);
	}
}