 
OBJS	= source.o
SOURCE	= source.cpp
HEADER	= 
OUT	= source
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

source.o: source.cpp
	$(CC) $(FLAGS) source.cpp 

clean:
	rm -f $(OBJS) $(OUT)