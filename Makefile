CC = g++ -std=c++11
FLAGS = -Wextra -Wall
.PHONY: MIR clean tar

MIR: MIR.o SongsParser.o LyricsSong.o InstrumentalSong.o Song.o Parameters.o SortHelper.o
	$(CC) $(FLAGS) $^ -o MIR

MIR.o: MIR.cpp MIR.h SongsParser.h LyricsSong.h Song.h Parameters.h BpmKnownWords.h \
InstrumentalSong.h SortHelper.h
	$(CC) $(FLAGS) -c $<

SongsParser.o: SongsParser.cpp SongsParser.h LyricsSong.h Song.h Parameters.h BpmKnownWords.h \
InstrumentalSong.h
	$(CC) $(FLAGS) -c $<
	
LyricsSong.o: LyricsSong.cpp LyricsSong.h Song.h Parameters.h BpmKnownWords.h
	$(CC) $(FLAGS) -c $<

InstrumentalSong.o: InstrumentalSong.cpp InstrumentalSong.h Song.h Parameters.h BpmKnownWords.h
	$(CC) $(FLAGS) -c $<
	
Song.o: Song.cpp Song.h Parameters.h BpmKnownWords.h
	$(CC) $(FLAGS) -c $<

Parameters.o: Parameters.cpp Parameters.h BpmKnownWords.h
	$(CC) $(FLAGS) -c $<
	
SortHelper.o: SortHelper.cpp SortHelper.h
	$(CC) $(FLAGS) -c $<
	
clean:
	rm -f *.o MIR

tar:
	tar -cvf ex2.tar MIR.cpp MIR.h Song.cpp Song.h LyricsSong.cpp LyricsSong.h InstrumentalSong.cpp \
	InstrumentalSong.h Parameters.cpp Parameters.h SongsParser.cpp SongsParser.h SortHelper.cpp \
	SortHelper.h BpmKnownWords.h README Makefile