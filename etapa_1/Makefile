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

main.out: main.o VSocket.o Socket.o SSLSocket.o
	$(CXX) main.o VSocket.o Socket.o SSLSocket.o $(LDFLAGS) -o $@

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

test: test1 test2 test3 test4