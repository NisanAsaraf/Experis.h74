CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o precious_stone.o
TARGET = utest

all: $(TARGET)

check: $(TARGET)
	@./$(TARGET) -v
	@make clean

valgrind_check: $(TARGET)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

recheck: clean check

clang_check: CXX = clang++
clang_check: check

clean:
	@$(RM) ./$(TARGET) $(OBJS)

utest.o: utest.cpp $(INCLUDES_DIR)/precious_stone.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

precious_stone.o: $(SOURCES_DIR)/precious_stone.cpp $(INCLUDES_DIR)/precious_stone.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TARGET): utest.o precious_stone.o $(INCLUDES_DIR)/precious_stone.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

.PHONY: all clean check recheck clang_check
