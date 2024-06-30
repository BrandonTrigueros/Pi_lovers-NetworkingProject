OBJS	= Intermediate.o VSocket.o Socket.o main.o
SOURCE	= Intermediate.cpp VSocket.cc Socket.cc main.cpp
HEADER	= Intermediate.h VSocket.h Socket.h
OUT	= Intermediate.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Intermediate.o: Intermediate.cpp
	$(CC) $(FLAGS) Intermediate.cpp 

VSocket.o: VSocket.cc
	$(CC) $(FLAGS) VSocket.cc 

Socket.o: Socket.cc
	$(CC) $(FLAGS) Socket.cc 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)