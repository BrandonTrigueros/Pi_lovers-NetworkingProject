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
	./main.out giraffe

test2:
	./main.out lion

test3:
	./main.out dragon

test4:
	./main.out camel

test5:
	./main.out shark

test6:
	./main.out blacksheep

test7:
	./main.out whitesheep

test8:
	./main.out roadrunner

test9:
	./main.out ape

test10:
	./main.out clownfish

test: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10