// Parameters.cpp

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Parameters.
// --------------------------------------------------------------------------------------

#include <iostream>
#include "Parameters.h"

#define NUM_OF_PARAMETERS 4
const std::string EMPTY_LINE = "";

/**
 * Initiates the Parameters object with the given stream to the parameters file.
 * @param instream stream to the parameters file.
 */
Parameters::Parameters(std::ifstream& instream)
{
	// First read the songs parameters from the parameters file.
	std::string line = "", param = "";
	int value = 0;
	int i = 0;

	while (instream.good() && i < NUM_OF_PARAMETERS)
	{
		getline(instream, line);
		if (line.compare(EMPTY_LINE) != 0) // Skip on empty lines
		{
			size_t pos = line.find(":");
			param = line.substr(0, pos);
			value = stoi(line.substr(pos + 1));
			_songsParams[param] = value;
			i++;
		}
	}

	// Now read the known bpm words from the parameters file.
	std::string word = "";
	double average = 0, deviation = 0;

	while(instream.good() && getline(instream, line))
	{
		if (line.compare(EMPTY_LINE) != 0) // Skip on empty lines
		{
			size_t pos1 = line.find(":");
			size_t pos2 = line.find(",");
			word = line.substr(0, pos1);
			average = stod(line.substr(pos1 + 2, pos2 - 1));
			deviation = stod(line.substr(pos2 + 2));
			_knownWords[word] = {average, deviation};
		}
	}
}

/**
 * Destructor for the Parameters class.
 */
Parameters::~Parameters()
{
}

