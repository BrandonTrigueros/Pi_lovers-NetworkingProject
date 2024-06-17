OBJS	= Client.o Socket.o VSocket.o main.o
SOURCE	= Client.cc Socket.cc VSocket.cc main.cc
HEADER	= Client.h Socket.h VSocket.h
OUT	= Client.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =   

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Client.o: Client.cc
	$(CC) $(FLAGS) Client.cc 

Socket.o: Socket.cc
	$(CC) $(FLAGS) Socket.cc 

VSocket.o: VSocket.cc
	$(CC) $(FLAGS) VSocket.cc 

main.o: main.cc
	$(CC) $(FLAGS) main.cc 

clean:
	rm -f $(OBJS) $(OUT)
