CC := gcc
CFLAGS := -c -o 
SQL := -lsqlite3
TARGET ?= servAPP
SRC_DIR = ./src

OBJSs := $(wildcard $(SRC_DIR)/*.c)
OBJSs += $(wildcard *.c)

OBJS := $(patsubst %.c,%.o,$(OBJSs))

all:$(OBJS)
	$(CC) $^ -o $(TARGET) $(SQL) -Wall

$(SRC_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $@  $< -I ./include/ 

%.o:%.c
	$(CC) $(CFLAGS) $@ $< -I ./include/ 

.PHONY:clean

clean:
	rm *.o $(TARGET) $(SRC_DIR)/*.o *.db

