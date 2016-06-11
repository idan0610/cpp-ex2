// Parser.h

#ifndef SONGSPARSER_H_
#define SONGSPARSER_H_

#include <string>
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include "LyricsSong.h"
#include "InstrumentalSong.h"

/**
* return all the line between {}
*/
std::string getWordList(const std::string line);

/**
* Parsing the songs file with the given stream to the file.
* @param instream stream to the songs file
* @return vector of pointers for the songs.
*/
std::vector<Song*> readSongsFromFile(std::ifstream& instream);

#endif /* SONGSPARSER_H_ */
