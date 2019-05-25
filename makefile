CC = g++ -std=c++11

all: phase2.out

phase2.out: main.o commandInterface.o film.o comment.o recommender.o network.o publisher.o user.o post.o get.o request.o exceptions.o
	$(CC) main.o commandInterface.o film.o comment.o network.o recommender.o publisher.o user.o post.o get.o request.o exceptions.o -o phase2.out

main.o: main.cpp commandInterface.h
	$(CC) -c main.cpp

commandInterface.o: commandInterface.cpp commandInterface.h defines.h structs.h post.h get.h exceptions.h
	$(CC) -c commandInterface.cpp

request.o: request.cpp request.h structs.h defines.h exceptions.h
	$(CC) -c request.cpp

post.o: post.h post.cpp request.h exceptions.h
	$(CC) -c post.cpp

get.o: get.h get.cpp request.h
	$(CC) -c get.cpp

exceptions.o: exceptions.h
	$(CC) -c exceptions.cpp

film.o: exceptions.h publisher.h comment.h structs.h film.h film.cpp
	$(CC) -c film.cpp

network.o: network.h network.cpp film.h user.o publisher.h structs.h defines.h exceptions.h recommender.h
	$(CC) -c network.cpp

publisher.o: publisher.cpp publisher.h user.h film.h structs.h defines.h
	$(CC) -c publisher.cpp

user.o: user.cpp user.h film.h structs.h
	$(CC) -c user.cpp

comment.o: comment.cpp comment.h user.h film.h
	$(CC) -c comment.cpp

recommender.o: recommender.h recommender.cpp user.h film.h
	$(CC) -c recommender.cpp

.PHONY: clean

clean:
	rm *.o
	rm *.out