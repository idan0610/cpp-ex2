/*
 * Parameters.h
 *
 *  Created on: 2 בספט׳ 2015
 *      Author: Maayan
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <fstream>
#include <unordered_map>
#include "BpmKnownWords.h"

/**
 * This class stores the parameters given by the parameters file.
 */
class Parameters
{
public:
	/**
	 * Initiates the Parameters object with the given stream to the parameters file.
	 * @param instream stream to the parameters file.
	 */
	Parameters(std::ifstream& instream);

	/**
	 * Destructor for the Parameters class.
	 */
	~Parameters();

	/**
	 * @return reference to the songs parameters map.
	 */
	inline std::unordered_map<std::string, int>& getSongsParams()
	{
		return _songsParams;
	}

	/**
	 * @return reference to the known bpm words map.
	 */
	inline std::unordered_map<std::string, BpmValues>& getKnownWords()
	{
		return _knownWords;
	}

private:
	std::unordered_map<std::string, int> _songsParams; /**< The system parameters */
	std::unordered_map<std::string, BpmValues> _knownWords; /**< bpm words and their values */
};

#endif /* PARAMETERS_H_ */
