CC := gcc
CFLAGS := -c -o
TARGET ?= clientAPP
SRC_DIR = ./src

OBJSs := $(wildcard $(SRC_DIR)/*.c)
OBJSs += $(wildcard *.c)

OBJS := $(patsubst %.c,%.o,$(OBJSs))

all:$(OBJS)
	$(CC) $^ -o $(TARGET)

$(SRC_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $@ $< -I ./include/ 

%.o:%.c
	$(CC) $(CFLAGS) $@ $< -I ./include/ 

.PHONY:clean

clean:
	rm *.o $(TARGET) $(SRC_DIR)/*.o


