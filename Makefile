CC = g++ -g -Wall
CFLAGS = `pkg-config --cflags OGRE-Overlay OIS` -I./
LIBS = -lboost_system -lboost_program_options `pkg-config --libs OGRE-Overlay OIS`

SRC_DIR = src/
OBJ_DIR = ./
SRC_FILES = $(wildcard $(SRC_DIR)*.cpp)
OBJ_FILES = $(addprefix $(OBJ_DIR),$(notdir $(SRC_FILES:.cpp=.o)))

TARGET = rocky_shores

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(LIBS) -o $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(SRC_DIR)*.h
	$(CC) -c $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf *.o
	rm -rf $(TARGET)
	rm -rf $(TEST_TARGET)
	rm -rf $(TEST_OBJ_DIR)*.o

#######################################################################
#                    put all test stuff down here                     #
#######################################################################

TEST_TARGET = rocky_shores_test

TEST_SRC_DIR = test/
TEST_OBJ_DIR = test/

TEST_CFLAGS = -I./$(TEST_SRC_DIR) -I./$(SRC_DIR) -I./include

TEST_SRC_FILES = $(wildcard $(TEST_SRC_DIR)*.cpp)
TEST_OBJ_FILES = $(addprefix $(TEST_OBJ_DIR),$(notdir $(TEST_SRC_FILES:.cpp=.o)))
OBJ_FILES_NO_MAIN = $(filter-out $(OBJ_DIR)main.o,$(OBJ_FILES))

test: $(TARGET) $(TEST_TARGET)

run_test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ_FILES)
	$(CC) $(LIBS) -o $@ $^ $(OBJ_FILES_NO_MAIN)

$(TEST_OBJ_DIR)%.o: $(TEST_SRC_DIR)%.cpp
	$(CC) -c $(CFLAGS) $(TEST_CFLAGS) -o $@ $<
