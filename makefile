CC = g++ -std=c++11

all: phase1.out

phase1.out: main.o commandInterface.o defines.h structedInput.h
	$(CC) main.o commandInterface.o -o phase1.out

main.o: main.cpp commandInterface.h defines.h structedInput.h
	$(CC) -c main.cpp

commandInterface.o: commandInterface.cpp commandInterface.h defines.h structedInput.h
	$(CC) -c commandInterface.cpp
