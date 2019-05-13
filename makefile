CC = g++ -std=c++11

all: phase1.out

phase1.out: main.o commandInterface.o post.o get.o delete.o put.o request.o exceptions.o
	$(CC) main.o commandInterface.o post.o get.o delete.o put.o request.o exceptions.o -o phase1.out

main.o: main.cpp commandInterface.h
	$(CC) -c main.cpp

commandInterface.o: commandInterface.cpp commandInterface.h defines.h structs.h post.h get.h delete.h put.h exceptions.h
	$(CC) -c commandInterface.cpp

request.o: request.cpp request.h structs.h defines.h exceptions.h
	$(CC) -c request.cpp

post.o: post.h post.cpp request.h exceptions.h
	$(CC) -c post.cpp

put.o: put.h put.cpp request.h
	$(CC) -c put.cpp

delete.o: delete.h delete.cpp request.h
	$(CC) -c delete.cpp

get.o: get.h get.cpp request.h
	$(CC) -c get.cpp

exceptions.o: exceptions.h
	$(CC) -c exceptions.cpp

.PHONY: clean

clean:
	rm *.o
	rm *.out