// Song.h

#ifndef SONG_H_
#define SONG_H_

#include <sstream>
#include <unordered_set>
#include <cmath>
#include "Parameters.h"

const std::string TAG_MATCH_SCORE = "tagMatchScore";

enum SongType
{
	LYRICS_SONG,
	INSTRUMENTAL_SONG
};

/**
 * This abstract class represents a song read from the songs file.
 */
class Song
{
public:
	/**
	 * Initiates the Song object with the given data.
	 * @param type The song type
	 * @param title The song title
	 * @param tags the song tags and their power.
	 */
	Song(const SongType type, const std::string title, const std::string tags);

	/**
	 * Destructor for the Song class.
	 */
	virtual ~Song();

	/**
	 * @return The song type.
	 */
	inline SongType getType() const
	{
		return _type;
	}

	/**
	 * @return The song title.
	 */
	inline std::string getTitle() const
	{
		return _title;
	}

	/**
	 * Calculating the score for this song, according to the given query.
	 * @param query
	 * @return The score
	 */
	virtual int calculateScore(const std::string query, Parameters& parameters) = 0;

	/**
	 *
	 */
	virtual std::string getComposer() const = 0;

protected:
	SongType _type; /**< The song type */
	std::string _title; /**< The song title */
	std::unordered_map<std::string, int> _tags; /** The song tags. The keys are the tags name and
												the values are their powers */

	/**
	 * Calculating the Tags Score of this song for the given query.
	 * @param query
	 * @return The Tags Score.
	 */
	int _calculateTagsScore(const std::string query, int param);
};

#endif /* SONG_H_ */
