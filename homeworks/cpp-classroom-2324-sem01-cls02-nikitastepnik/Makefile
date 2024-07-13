CC=gcc
CFLAGS=-Wall -Werror
CXX=g++
CXXFLAGS=$(CFLAGS) -std=c++20
SOURCE_FLAG=-c
OBJ_FLAG=-o
SRC_DIR=./src
.PHONY: smoke_task_1_strcmp smoke_task_1_nearest_same smoke_task_2 smoke_task_3

smoke_task_1_strcmp:
	# use src/task_1/test_strcmp.cpp
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/task_1/test_strcmp.cpp $(SRC_DIR)/task_1/strcmp.cpp $(OBJ_FLAG) test1_1
	cp test1_1 ./smoke_task_1_strcmp
	exit 0

smoke_task_1_nearest_same:
	# use src/task_1/test_find_nearest_same.cpp
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/task_1/test_find_nearest_same.cpp $(SRC_DIR)/task_1/find_nearest_same.cpp $(OBJ_FLAG) test1_2
	cp test1_2 ./smoke_task_1_nearest_same
	exit 0

smoke_task_2:
	# use src/task_2/test.cpp
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/task_2/test.cpp $(SRC_DIR)/task_2/array_utils.cpp $(OBJ_FLAG) test2
	cp test2 ./smoke_task_2
	exit 0

smoke_task_3:
	# use src/task_3/test.cpp, CXX and CC
	$(CXX) $(CXXFLAGS) $(SOURCE_FLAG) $(SRC_DIR)/task_3/test.cpp $(OBJ_FLAG) test.o
	$(CC)  $(SOURCE_FLAG) $(SRC_DIR)/task_3/sum.c $(OBJ_FLAG) sum.o
	$(CXX) test.o sum.o $(OBJ_FLAG) test3
	cp test3 ./smoke_task_3
	exit 0
