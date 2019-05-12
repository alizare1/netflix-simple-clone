CC = g++ -std=c++11

all: phase1.out

phase1.out: main.o commandInterface.o post.o get.o delete.o put.o request.o
	$(CC) main.o commandInterface.o post.o get.o delete.o put.o request.o -o phase1.out

main.o: main.cpp commandInterface.h
	$(CC) -c main.cpp

commandInterface.o: commandInterface.cpp commandInterface.h defines.h structedInput.h post.h get.h delete.h put.h
	$(CC) -c commandInterface.cpp

request.o: request.cpp request.h structedInput.h defines.h
	$(CC) -c request.cpp

post.o: post.h post.cpp request.h
	$(CC) -c post.cpp

put.o: put.h put.cpp request.h
	$(CC) -c put.cpp

delete.o: delete.h delete.cpp request.h
	$(CC) -c delete.cpp

get.o: get.h get.cpp request.h
	$(CC) -c get.cpp
