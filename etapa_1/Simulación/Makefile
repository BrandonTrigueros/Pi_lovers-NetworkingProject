OBJS	= ClientSide.o IntermediateServerSide.o ServerSide.o main.o
SOURCE	= ClientSide.cc IntermediateServerSide.cc ServerSide.cc main.cc
HEADER	= ServerSide.h legoFigures.h ClientSide.h IntermediateServerSide.h ThreadData.h
OUT	= Simulation.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

ClientSide.o: ClientSide.cc
	$(CC) $(FLAGS) ClientSide.cc 

IntermediateServerSide.o: IntermediateServerSide.cc
	$(CC) $(FLAGS) IntermediateServerSide.cc 

ServerSide.o: ServerSide.cc
	$(CC) $(FLAGS) ServerSide.cc 

main.o: main.cc
	$(CC) $(FLAGS) main.cc 


clean:
	rm -f $(OBJS) $(OUT)