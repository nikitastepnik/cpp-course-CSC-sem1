CC=g++
CFLAGS=-Wall -Werror -std=c++20
OBJ_FLAG=-o
SRC_DIR=./src
.PHONY: smoke_task_1 smoke_task_2 smoke_task_3

smoke_task_1:
	$(CC) $(CFLAGS) $(SRC_DIR)/task_1/hello.cpp $(SRC_DIR)/task_1/test.cpp $(OBJ_FLAG) test1
	exit 0

smoke_task_2:
	$(CC) $(CFLAGS) $(SRC_DIR)/task_2/fizzbuzz.cpp $(SRC_DIR)/task_2/test.cpp $(OBJ_FLAG) test2
	exit 0

smoke_task_3:
	$(CC) $(CFLAGS) $(SRC_DIR)/task_3/compute_fib.cpp $(SRC_DIR)/task_3/test.cpp $(OBJ_FLAG) test3
	exit 0
