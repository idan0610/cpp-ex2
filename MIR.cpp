// MIR.cpp

// --------------------------------------------------------------------------------------
// This file contains the implementation of the MIR driver.
// --------------------------------------------------------------------------------------

#include "MIR.h"

const std::string EMPTY_LINE = "";
const std::string SEPERATION_LINE = "----------------------------------------";
const std::string QUERY_WORD = "Query word: ";
const std::string PERFORMED_BY = "performed by: ";
const std::string LYRICS_BY = "lyrics by: ";

/**
 * Initiates the driver with the given ifstream references to the parameters and songs files.
 * @paramsStream stream to the parameters file
 * @songsStream stream to the songs file
 */
MIR::MIR(std::ifstream& paramsStream, std::ifstream& songsStream) : _parameteres(paramsStream),
		 _songs(readSongsFromFile(songsStream))
{
}

/**
 * Destructor for the MIR driver. Delete all songs from the songs vector.
 */
MIR::~MIR()
{
	for (std::vector<Song*>::iterator it = _songs.begin(); it != _songs.end(); ++it)
	{
		delete *it;
	}
}

/**
 * Calculate for every word in the queries file the score of each song from the songs vector.
 * Prints the songs whose score is positive.
 * @param queries stream to the queries file.
 */
void MIR::calculateScores(std::ifstream& queriesStream)
{
	std::string query = "";
	int currentScore = 0;

	while (queriesStream.good() && getline(queriesStream, query))
	{
		// For each query, find the score of this query for every song. Use SortHelper to sort
		// the scores by size.
		if (query.compare(EMPTY_LINE) == 0)
		{
			continue;
		}
		std::vector<int> scores;
		SortHelper sorted;
		for (unsigned int i = 0; i < _songs.size(); i++)
		{
			currentScore = _songs[i]->calculateScore(query, _parameteres);
			scores.push_back(currentScore);
			sorted.addItem(currentScore);
		}

		std::vector<int> sortedScores = sorted.getSortedOrderInVector();

		// Print the results for each query, by the given format.
		std::cout << SEPERATION_LINE << std::endl;
		std::cout << QUERY_WORD << query << std::endl;
		std::cout << std::endl;
		int songIndex = 0;
		for (unsigned int j = 0; j < sortedScores.size(); j++)
		{
			// Print only the songs whose score is positive.
			songIndex = sortedScores[j];
			if (scores[songIndex] > 0)
			{
				std::cout << _songs[songIndex]->getTitle() << "\t";
				std::cout << scores[songIndex] << "\t";
				if (_songs[songIndex]->getType() == LYRICS_SONG)
				{
					std::cout << LYRICS_BY;
				}
				else if (_songs[songIndex]->getType() == INSTRUMENTAL_SONG)
				{
					std::cout << PERFORMED_BY;
				}
				std::cout << _songs[songIndex]->getComposer() << std::endl;
			}
		}
	}
}

/**
 * Checking if the given stream opened correctly.
 * @param instream the given stream
 * @param fileName the name of the file
 * @return true if the file opened correctly, false otherwise.
 */
bool MIR::checkStream(std::ifstream& instream, const std::string fileName)
{
	if (!instream.is_open())
	{
		std::cerr << "Error! Can't open file: " << fileName << "." << std::endl;
		return false;
	}

	return true;
}

/**
 * The main function. Runs the driver for this MIR software.
 * @param argc number of command arguments
 * @param argv the command arguments
 * @return 0 to end the running of this program.
 */
int main(int argc, char* argv[])
{
	// Check if the number of given arguments is wrong.
	if (argc != 4)
	{
		std::cerr << "Error! Wrong number of arguments" << std::endl;
		exit(1);
	}

	// Open streams for the songs and parameters files and check if they opened successfully.
	std::ifstream songsStream(argv[1]);
	std::ifstream paramsStream(argv[2]);
	if (!MIR::checkStream(songsStream, argv[1]) || !MIR::checkStream(paramsStream, argv[2]))
	{
		paramsStream.close();
		songsStream.close();
		exit(1);
	}

	// Initiate the MIR driver with the streams, and close them.
	MIR driver(paramsStream, songsStream);

	paramsStream.close();
	songsStream.close();

	// Open stream for the queries file and check if it opened successfully.
	std::ifstream queriesStream(argv[3]);
	if (!MIR::checkStream(queriesStream, argv[3]))
	{
		queriesStream.close();
		exit(1);
	}

	// Calculate and print the scores of each query, and close the queries stream.
	driver.calculateScores(queriesStream);

	queriesStream.close();

	return 0;
}
