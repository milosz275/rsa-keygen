CC = g++
CFLAGS = -std=c++20 -Wall -Werror -Wextra -pedantic $(INCLUDES)
LDFLAGS = -lgmpxx -lgmp

BUILD_DIR = build
SRC_DIR = src
INC_DIR = include
INCLUDES = -I.

TARGET = rsa-keygen
OBJECTS = $(addprefix $(BUILD_DIR)/, keygen.o main.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/keygen.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/keygen.o: $(SRC_DIR)/keygen.cpp $(INC_DIR)/keygen.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean