CXX=g++
CXXFLAGS=-Wall -Werror -std=c++20 -fsanitize=address
SRC_DIR=./src
OBJ_FLAG=-o
.PHONY: smoke_task_1 smoke_task_2 smoke_task_3 smoke_task_4

smoke_task_1:
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/task_1/test.cpp $(SRC_DIR)/task_1/concat.cpp $(OBJ_FLAG) test1
	cp test1 ./smoke_task_1
	exit 0

smoke_task_2:
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/task_2/test.cpp $(SRC_DIR)/task_2/int_vector.cpp $(OBJ_FLAG) test2
	cp test2 ./smoke_task_2
	exit 0

smoke_task_3:
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/task_3/test.cpp $(SRC_DIR)/task_3/node_utils.cpp -fsanitize=address $(OBJ_FLAG)  test3
	cp test3 ./smoke_task_3
	exit 0

smoke_task_4:
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/task_4/test.cpp $(SRC_DIR)/task_4/first.cpp $(SRC_DIR)/task_4/second.cpp $(SRC_DIR)/task_4/singleton.cpp $(OBJ_FLAG) test4
	cp test4 ./smoke_task_4
	exit 0
