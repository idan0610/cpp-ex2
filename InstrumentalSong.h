// InstrumentalSong.h

#ifndef INSTRUMENTALSONG_H_
#define INSTRUMENTALSONG_H_

#include "Song.h"

const std::string INSTRUMENTS_MATCH_SCORE = "instrumentMatchScore";
const std::string BPM_LIKELIHOOD_WEIGHT = "bpmLikelihoodWeight";

/**
 *
 */
class InstrumentalSong : public Song
{
public:
	/**
	 * Initiates the InstrumentalSong with the given data.
	 * @param title
	 * @param tags
	 * @param instruments
	 * @param performedBy
	 * @param bpm
	 */
	InstrumentalSong(const std::string title, const std::string tags, const std::string instruments,
					 const std::string performedBy, const double bpm = 0);

	/**
	 * Destructor for the InstrumentalSong class.
	 */
	virtual ~InstrumentalSong();

	/**
	 * @return who performed this song.
	 */
	virtual std::string getComposer() const;

	/**
	 * Calculating the score for this song, according to the given query.
	 * @param query
	 * @return The score
	 */
	virtual int calculateScore(const std::string query, Parameters& parameters);

private:
	std::unordered_set<std::string> _instruments; /**< The instruments of the song */
	std::string _performedBy; /**< Who performed this song */
	double _bpm; /**< The bpm of the song */

	/**
	 * Calculating the Instruments Score of this song for the given query.
	 * @param query
	 * @return The Lyrics Score.
	 */
	int _calculateInstrumentsScore(const std::string query, int param) const;

	/**
	 * Calculating the Bpm likelihood weight of this song for the given query.
	 * @param query
	 * @return The Lyrics Score.
	 */
	int _calculateBpmWeight(const std::string query, int param,
							std::unordered_map<std::string, BpmValues>& knownWords) const;
};

#endif /* INSTRUMENTALSONG_H_ */
