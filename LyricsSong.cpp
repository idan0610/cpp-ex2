// LyricsSong.cpp

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class LyricsSong.
// --------------------------------------------------------------------------------------

#include "LyricsSong.h"

/**
 * Initiates the LyricsSong with the given data.
 * @param title
 * @param tags
 * @param lyrics
 * @param lyricsBy
 */
LyricsSong::LyricsSong(const std::string title, const std::string tags, const std::string lyrics,
					   const std::string lyricsBy) : Song(LYRICS_SONG, title, tags),
					   _lyricsBy(lyricsBy)
{
	std::istringstream instream(lyrics);
	std::string word = "";
	while (std::getline(instream, word, ' '))
	{
		if (_lyrics.count(word) > 0)
		{
			_lyrics[word]++;
		}
		else
		{
			_lyrics[word] = 1;
		}
	}
}

/**
 * Destructor for the LyricsSong class.
 */
LyricsSong::~LyricsSong()
{
}

/**
 * Calculating the score for this song, according to the given query.
 * @param query
 * @return The score
 */
int LyricsSong::calculateScore(const std::string query, Parameters& parameters)
{
	std::unordered_map<std::string, int>& params = parameters.getSongsParams();
	int tagsScore = _calculateTagsScore(query, params[TAG_MATCH_SCORE]);
	int lyricsScore = _calculateLyricsScore(query, params[LYRICS_MATCH_SCORE]);

	return tagsScore + lyricsScore;
}

/**
 * @return The writer of the lyrics of the song.
 */
std::string LyricsSong::getComposer() const
{
	return _lyricsBy;
}

/**
 * Calculating the Lyrics Score of this song for the given query.
 * @param query
 * @return The Lyrics Score.
 */
int LyricsSong::_calculateLyricsScore(const std::string query, int param)
{
	int occurences = 0;
	if (_lyrics.count(query) > 0)
	{
		occurences = _lyrics[query];
	}

	return occurences * param;
}
