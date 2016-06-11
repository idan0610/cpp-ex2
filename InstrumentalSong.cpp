// InstrumentalSong.cpp

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class InstrumentalSong.
// --------------------------------------------------------------------------------------

#include "InstrumentalSong.h"

/**
 * Initiates the InstrumentalSong with the given data.
 * @param title
 * @param tags
 * @param instruments
 * @param performedBy
 * @param bpm
 */
InstrumentalSong::InstrumentalSong(const std::string title, const std::string tags,
								   const std::string instruments, const std::string performedBy,
								   const double bpm) : Song(INSTRUMENTAL_SONG, title, tags),
								   _performedBy(performedBy), _bpm(bpm)
{
	std::istringstream instream(instruments);
	std::string instrument = "";
	while (std::getline(instream, instrument, ' '))
	{
		_instruments.insert(instrument);
	}
}

/**
 * Destructor for the InstrumentalSong class.
 */
InstrumentalSong::~InstrumentalSong()
{
}

/**
 * Calculating the score for this song, according to the given query.
 * @param query
 * @return The score
 */
int InstrumentalSong::calculateScore(const std::string query, Parameters& parameters)
{
	std::unordered_map<std::string, int>& songsParams = parameters.getSongsParams();
	std::unordered_map<std::string, BpmValues>& knownWords = parameters.getKnownWords();

	int tagsScore = _calculateTagsScore(query, songsParams[TAG_MATCH_SCORE]);
	int instrumentsScore = _calculateInstrumentsScore(query, songsParams[INSTRUMENTS_MATCH_SCORE]);
	int bpmWeight = _calculateBpmWeight(query, songsParams[BPM_LIKELIHOOD_WEIGHT], knownWords);

	return tagsScore + instrumentsScore + bpmWeight;
}

/**
 * @return who performed this song.
 */
std::string InstrumentalSong::getComposer() const
{
	return _performedBy;
}

/**
 * Calculating the Instruments Score of this song for the given query.
 * @param query
 * @return The Lyrics Score.
 */
int InstrumentalSong::_calculateInstrumentsScore(const std::string query, int param) const
{
	if (_instruments.count(query))
	{
		return param;
	}

	return 0;
}

/**
 * Calculating the Bpm likelihood weight of this song for the given query.
 * @param query
 * @return The Lyrics Score.
 */
int InstrumentalSong::_calculateBpmWeight(const std::string query, int param,
										  std::unordered_map<std::string, BpmValues>& knownWords)
										  const
{
	if (_bpm != 0 && knownWords.count(query) > 0)
	{
		// expCalc is calculated by the given formula from the targil instructions.
		double expCalc = exp(- pow(_bpm - knownWords[query]._average, 2) /
					  (2 * pow(knownWords[query]._deviation, 2)));

		return (int)floor(param * expCalc);
	}

	return 0;
}
