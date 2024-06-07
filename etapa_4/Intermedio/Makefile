OBJS	= Intemediate.o main.o Socket.o VSocket.o
SOURCE	= Intemediate.cpp main.cpp Socket.cc VSocket.cc
HEADER	= Intermediate.h Socket.h VSocket.h
OUT	= main.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Intemediate.o: Intemediate.cpp
	$(CC) $(FLAGS) Intemediate.cpp -lcrypto

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp  -lcrypto

Socket.o: Socket.cc
	$(CC) $(FLAGS) Socket.cc  -lcrypto

VSocket.o: VSocket.cc
	$(CC) $(FLAGS) VSocket.cc -lcrypto


clean:
	rm -f $(OBJS) $(OUT)