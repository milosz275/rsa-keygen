CC = g++

CFLAGS = -std=c++20 -Wall -Wextra -pedantic $(INCLUDES)

LDFLAGS = -lgmpxx -lgmpxx


BUILD_DIR = BUILD_DIR
SRC_DIR = SRC_DIR
INC_DIR = INCLUDES
INCLUDES = -I.



TARGET = output

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
				
				