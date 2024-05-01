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
	./main.out BobOmb

test2:
	./main.out Car
  
test3:
	./main.out DogHouse

test4:
	./main.out Dragon

test5:
	./main.out Jovani

test6:
	./main.out SantaClaus

test7:
	./main.out TieFighter


test: test1 test2 test3 test4 test5 test6 test7