// LyricsSong.h

#ifndef LYRICSSONG_H_
#define LYRICSSONG_H_

#include "Song.h"

const std::string LYRICS_MATCH_SCORE = "lyricsMatchScore";

/**
 *
 */
class LyricsSong: public Song
{
public:
	/**
	 * Initiates the LyricsSong with the given data.
	 * @param title
	 * @param tags
	 * @param lyrics
	 * @param lyricsBy
	 */
	LyricsSong(const std::string title, const std::string tags, const std::string lyrics,
			   const std::string lyricsBy);

	/**
	 * Destructor for the LyricsSong class.
	 */
	virtual ~LyricsSong();

	/**
	 * @return the lyrics of the song
	 */
	inline std::unordered_map<std::string, int> getLyrics()
	{
		return _lyrics;
	}

	/**
	 * @return The writer of the lyrics of the song.
	 */
	virtual std::string getComposer() const;

	/**
	 * Calculating the score for this song, according to the given query.
	 * @param query
	 * @return The score
	 */
	virtual int calculateScore(const std::string query, Parameters& parameters);
private:
	std::unordered_map<std::string, int> _lyrics; /**< lyrics of the song */
	std::string _lyricsBy; /**< who wrote the lyrics */

	/**
	 * Calculating the Lyrics Score of this song for the given query.
	 * @param query
	 * @return The Lyrics Score.
	 */
	int _calculateLyricsScore(const std::string query, int param);
};

#endif /* LYRICSSONG_H_ */
