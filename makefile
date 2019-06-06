CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
BCKEND = backendCode
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/myServer.o: $(BCKEND)/network.h code/myServer.hpp code/myServer.cpp
	$(CC) $(CF) -c code/myServer.cpp -o $(BUILD_DIR)/myServer.o

$(BUILD_DIR)/main.o: code/main.cpp code/myServer.hpp
	$(CC) $(CF) -c code/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/handlers.o: code/handlers.hpp code/handlers.cpp
	$(CC) $(CF) -c code/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/myReq.o: $(BCKEND)/myReq.cpp $(BCKEND)/myReq.h $(BCKEND)/structs.h $(BCKEND)/defines.h $(BCKEND)/exceptions.h
	$(CC) $(CF) -c $(BCKEND)/myReq.cpp -o $(BUILD_DIR)/myReq.o

$(BUILD_DIR)/post.o: $(BCKEND)/post.h $(BCKEND)/post.cpp $(BCKEND)/myReq.h $(BCKEND)/exceptions.h
	$(CC) $(CF) -c $(BCKEND)/post.cpp -o $(BUILD_DIR)/post.o

$(BUILD_DIR)/get.o: $(BCKEND)/get.h $(BCKEND)/get.cpp $(BCKEND)/myReq.h
	$(CC) $(CF) -c $(BCKEND)/get.cpp -o $(BUILD_DIR)/get.o

$(BUILD_DIR)/exceptions.o: $(BCKEND)/exceptions.h
	$(CC) $(CF) -c $(BCKEND)/exceptions.cpp -o $(BUILD_DIR)/exceptions.o

$(BUILD_DIR)/film.o: $(BCKEND)/exceptions.h $(BCKEND)/publisher.h $(BCKEND)/comment.h $(BCKEND)/structs.h $(BCKEND)/film.h $(BCKEND)/film.cpp
	$(CC) $(CF) -c $(BCKEND)/film.cpp -o $(BUILD_DIR)/film.o

$(BUILD_DIR)/network.o: $(BCKEND)/network.h $(BCKEND)/network.cpp $(BCKEND)/film.h $(BCKEND)/user.o $(BCKEND)/publisher.h $(BCKEND)/structs.h $(BCKEND)/defines.h $(BCKEND)/exceptions.h $(BCKEND)/recommender.h
	$(CC) $(CF) -c $(BCKEND)/network.cpp -o $(BUILD_DIR)/network.o

$(BUILD_DIR)/publisher.o: $(BCKEND)/publisher.cpp $(BCKEND)/publisher.h $(BCKEND)/user.h $(BCKEND)/film.h $(BCKEND)/structs.h $(BCKEND)/defines.h
	$(CC) $(CF) -c $(BCKEND)/publisher.cpp -o $(BUILD_DIR)/publisher.o

$(BUILD_DIR)/user.o: $(BCKEND)/user.cpp $(BCKEND)/user.h $(BCKEND)/film.h $(BCKEND)/structs.h
	$(CC) $(CF) -c $(BCKEND)/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/comment.o: $(BCKEND)/comment.cpp $(BCKEND)/comment.h $(BCKEND)/user.h $(BCKEND)/film.h
	$(CC) $(CF) -c $(BCKEND)/comment.cpp -o $(BUILD_DIR)/comment.o

$(BUILD_DIR)/recommender.o: $(BCKEND)/recommender.h $(BCKEND)/recommender.cpp $(BCKEND)/user.h $(BCKEND)/film.h
	$(CC) $(CF) -c $(BCKEND)/recommender.cpp -o $(BUILD_DIR)/recommender.o

myserver.out: $(BUILD_DIR)/myServer.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/myReq.o $(BUILD_DIR)/post.o $(BUILD_DIR)/get.o $(BUILD_DIR)/exceptions.o $(BUILD_DIR)/film.o $(BUILD_DIR)/network.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/user.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/recommender.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/myServer.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/myReq.o $(BUILD_DIR)/post.o $(BUILD_DIR)/get.o $(BUILD_DIR)/exceptions.o $(BUILD_DIR)/film.o $(BUILD_DIR)/network.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/user.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/recommender.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  -o myserver.out



.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
