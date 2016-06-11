// Parser.cpp

// --------------------------------------------------------------------------------------
// This file contains the implementation of the parsing songs file functions.
// --------------------------------------------------------------------------------------

#include "SongsParser.h"

const std::string SEPARATOR = "=";
const std::string END_OF_SONGS = "***";
const std::string TITLE = "title";
const std::string TAGS = "tags";
const std::string LYRICS = "lyrics";
const std::string LYRICS_BY = "lyricsBy";
const std::string INSTRUMENTS = "instruments";
const std::string PERFORMED_BY = "performedBy";
const std::string BPM = "bpm";

/**
* return all the line between {}
*/
std::string getWordList(const std::string line)
{

    size_t pos1 = line.find("{");
    size_t pos2 = line.find("}");

    return line.substr(pos1 + 1, pos2 - pos1 - 1);
}

/**
* Parsing the songs file with the given stream to the file.
* @param instream stream to the songs file
* @return vector of pointers for the songs.
*/
std::vector<Song*> readSongsFromFile(std::ifstream& instream)
{
    std::vector<Song*> songs;

    std::string line = "";

    int lastSong = 0;

    while(instream.good() && !lastSong)
    {
        if (line.compare(SEPARATOR) != 0)
        {
            getline(instream, line);
            // Expect a line of "="
            if (END_OF_SONGS.compare(line) == 0)
            {
                lastSong = 1;
                break;
            }

        }

        getline(instream, line);
        // Expect a line of "title: ..."
        size_t pos = TITLE.size() + 2;
        std::string title = line.substr(pos);

        getline(instream, line);
        // Expect a line of "tags: {...}"
        std::string tags = getWordList(line);

        std::string lyrics = "";
        std::string lyricsBy = "";
        std::string instruments = "";
        std::string performedBy = "";
        std::string bpmStr = "";

        getline(instream, line);
        // Expect either lyrics or instruments.
        if (line.substr(0, LYRICS.size()).compare(LYRICS) == 0)
        {
            // Then we have a lyric song

            // Lets get the lyrics:
            lyrics = getWordList(line);

            // Lets get the lyricsBy:
            getline(instream, line);
            pos = LYRICS_BY.size() + 2;
            lyricsBy = line.substr(pos);

            // Initiate a new LyricsSong with the parsed arguments and add them to the songs vector.
            LyricsSong* song = new LyricsSong(title, tags, lyrics, lyricsBy);
            songs.push_back(song);
        }
        else
        {
            // Then we have an instrumental song

            // Lets get the instruments:
            instruments = getWordList(line);

            // Lets get the performedBy:
            getline(instream, line);
            pos = PERFORMED_BY.size() + 2;
            performedBy = line.substr(pos);

            // Lets see if we have bpm:
            if (!instream.good())
            {
                break;
            }
            getline(instream, line);
            if (END_OF_SONGS.compare(line) == 0)
            {
                lastSong = 1;
            }

            InstrumentalSong* song;

            if (line.substr(0, BPM.size()).compare(BPM) == 0)
            {

                pos = BPM.size() + 2;
                bpmStr = line.substr(pos);

                // Initiate a new InstrumentalSong with the parsed arguments and add them to the
                // songs vector (with bpm value).
                song = new InstrumentalSong(title, tags, instruments, performedBy, stod(bpmStr));
            }
            else
            {
                 assert ( (line.compare(SEPARATOR) == 0) || (line.compare(END_OF_SONGS) == 0));

                 // Initiate a new InstrumentalSong with the parsed arguments and add them to the
                 // songs vector (without bpm value).
                 song = new InstrumentalSong(title, tags, instruments, performedBy);

            }
            songs.push_back(song);
        }
    }

    return songs;
}

