CC  := gcc
CXX := g++
CFLAGS := -g -c
CXXFLAGS := -g -c 
LDFLAGS := -lssl -lcrypto
DEPS := Socket.h
TARGETS := main.cc


ALL := $(TARGETS)
$(info $$TARGETS = $(TARGETS))

%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) $<

%.out: %.o Socket.o
	$(info $$^ = $^)
	$(CXX) $^ Socket.o $(LDFLAGS) -o $^

main.out: main.o VSocket.o Socket.o SSLSocket.o Client.o
	$(CXX) main.o VSocket.o Socket.o SSLSocket.o  Client.o $(LDFLAGS) -o $@


clean:
	rm -f *.o *.out


test1:
	./main.out giraffe 1

test2:
	./main.out lion 2

test3:
	./main.out dragon 3 

test4:
	./main.out camel 4 

test5:
	./main.out shark 5

test6:
	./main.out roadrunner

test7:
	./main.out ape

test8:
	./main.out clownfish

test: test1 test2 test3 test4 test5 test6 test7 test8