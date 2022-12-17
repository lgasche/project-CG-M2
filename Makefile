OBJS	= main.o LvlReader.o Treasure.o
SOURCE	= main.cpp LvlReader.cpp Treasure.cpp
HEADER	= LvlReader.hpp Treasure.hpp
OUT	= out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lstdc++fs

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: src/main.cpp
	$(CC) $(FLAGS) src/main.cpp 

LvlReader.o: src/LvlReader.cpp
	$(CC) $(FLAGS) src/LvlReader.cpp 

Treasure.o: src/Treasure.cpp
	$(CC) $(FLAGS) src/Treasure.cpp 


clean:
	rm -f $(OBJS) $(OUT)
