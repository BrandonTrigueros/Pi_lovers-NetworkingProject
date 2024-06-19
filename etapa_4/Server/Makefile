OBJS	= FileManager.o main.o Server.o Socket.o VSocket.o
SOURCE	= FileManager.cc main.cc Server.cc Socket.cc VSocket.cc
HEADER	= Server.h Socket.h VSocket.h FileManager.h
OUT	= Server.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

FileManager.o: FileManager.cc
	$(CC) $(FLAGS) FileManager.cc 

main.o: main.cc
	$(CC) $(FLAGS) main.cc 

Server.o: Server.cc
	$(CC) $(FLAGS) Server.cc 

Socket.o: Socket.cc
	$(CC) $(FLAGS) Socket.cc 

VSocket.o: VSocket.cc
	$(CC) $(FLAGS) VSocket.cc 


clean:
	rm -f $(OBJS) $(OUT)