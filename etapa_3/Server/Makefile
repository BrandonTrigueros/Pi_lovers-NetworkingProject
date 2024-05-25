# Linux Makefile
#

CC  := gcc
CXX := g++
CFLAGS := -g -c
CXXFLAGS := -g -c 
LDFLAGS := 
DEPS := Socket.h
TARGETS := main.out

ALL := $(TARGETS)
$(info $$TARGETS = $(TARGETS))

%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) $<

%.out: %.o VSocket.o Socket.o Server.o FileManager.o MirrorClientTest.o
	$(info $$^ = $^)
	$(CXX) $^ FileManager.o $(LDFLAGS) -o $^

main.out:	main.o VSocket.o Socket.o Server.o FileManager.o
	$(CXX) main.o VSocket.o Socket.o Server.o FileManager.o $(LDFLAGS) -o $@

clean:
	rm -f *.o *.out

