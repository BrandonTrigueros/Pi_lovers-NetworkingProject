OBJS	= MasterIntemediate.o Socket.o VSocket.o main.o
SOURCE	= MasterIntemediate.cpp Socket.cc VSocket.cc main.cpp
HEADER	= MasterIntermediate.h Socket.h VSocket.h
OUT	= MasterIntermediate.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

MasterIntemediate.o: MasterIntemediate.cpp
	$(CC) $(FLAGS) MasterIntemediate.cpp 

Socket.o: Socket.cc
	$(CC) $(FLAGS) Socket.cc 

VSocket.o: VSocket.cc
	$(CC) $(FLAGS) VSocket.cc 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)