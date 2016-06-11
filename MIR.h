// MIR.h

#ifndef MIR_H_
#define MIR_H_

#include "SongsParser.h"
#include "SortHelper.h"

/**
 * This class represents the driver of this MIR software.
 */
class MIR
{
public:
	/**
	 * Initiates the driver with the given ifstream references to the parameters and songs files.
	 * @paramsStream stream to the parameters file
	 * @songsStream stream to the songs file
	 */
	MIR(std::ifstream& paramsStream, std::ifstream& songsStream);

	/**
	 * Destructor for the MIR driver. Delete all songs from the songs vector.
	 */
	~MIR();

	/**
	 * Calculate for every word in the queries file the score of each song from the songs vector.
	 * Prints the songs whose score is positive.
	 * @param queries stream to the queries file.
	 */
	void calculateScores(std::ifstream& queriesStream);

	/**
	 * Checking if the given stream opened correctly.
	 * @param instream the given stream
	 * @param fileName the name of the file
	 * @return true if the file opened correctly, false otherwise.
	 */
	static bool checkStream(std::ifstream& instream, const std::string fileName);

private:
	Parameters _parameteres; /**< The songs parameters learned before */
	std::vector<Song*> _songs; /**< The songs details */
};
#endif /* MIR_H_ */
