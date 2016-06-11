// Song.cpp

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Song.
// --------------------------------------------------------------------------------------

#include "Song.h"

/**
 * Initiates the Song object with the given data.
 * @param type The song type
 * @param title The song title
 * @param tags the song tags and their power.
 */
Song::Song(const SongType type, const std::string title, const std::string tags) : _type(type),
		   _title(title)
{
	std::istringstream instream(tags);
	std::string tagName;
	std::string tagPower;
	while (std::getline(instream, tagName, ' '))
	{
		std::getline(instream, tagPower, ' ');
		_tags[tagName] = stoi(tagPower);
	}
}

/**
 * Destructor for the Song class.
 */
Song::~Song()
{
}

/**
 * Calculating the Tags Score of this song for the given query.
 * @param query
 * @return The Tags Score.
 */
int Song::_calculateTagsScore(const std::string query, int param)
{
	int tagScore = 0;
	if(_tags.count(query) > 0)
	{
		tagScore = _tags[query] * param;
	}

	return tagScore;
}
