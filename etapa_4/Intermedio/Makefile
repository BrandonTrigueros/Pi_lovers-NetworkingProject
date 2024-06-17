OBJS	= Intermediate.o RequestQueue.o Socket.o VSocket.o main.o
SOURCE	= Intermediate.cpp RequestQueue.cpp Socket.cc VSocket.cc main.cpp
HEADER	= RequestQueue.h Socket.h VSocket.h Intermediate.h
OUT	= Intermediate.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Intermediate.o: Intermediate.cpp
	$(CC) $(FLAGS) Intermediate.cpp 

RequestQueue.o: RequestQueue.cpp
	$(CC) $(FLAGS) RequestQueue.cpp 

Socket.o: Socket.cc
	$(CC) $(FLAGS) Socket.cc 

VSocket.o: VSocket.cc
	$(CC) $(FLAGS) VSocket.cc 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)