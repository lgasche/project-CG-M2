OBJS	= main.o LvlReader.o
SOURCE	= main.cpp LvlReader.cpp
HEADER	= LvlReader.hpp
OUT	= DungeonMaster
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: src/main.cpp
	$(CC) $(FLAGS) src/main.cpp -std=c++17

LvlReader.o: src/LvlReader.cpp
	$(CC) $(FLAGS) src/LvlReader.cpp -std=c++17


clean:
	rm -f $(OBJS) $(OUT)
