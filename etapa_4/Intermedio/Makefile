OBJS	= Intermediate.o RequestQueue.o VSocket.o Socket.o ResponseQueue.o main.o
SOURCE	= Intermediate.cpp RequestQueue.cpp VSocket.cc Socket.cc ResponseQueue.cpp main.cpp
HEADER	= ResponseQueue.h Intermediate.h RequestQueue.h VSocket.h Socket.h
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

VSocket.o: VSocket.cc
	$(CC) $(FLAGS) VSocket.cc 

Socket.o: Socket.cc
	$(CC) $(FLAGS) Socket.cc 

ResponseQueue.o: ResponseQueue.cpp
	$(CC) $(FLAGS) ResponseQueue.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)