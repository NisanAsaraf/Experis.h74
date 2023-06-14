CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o stack.o minimum_stack.o
TARGET = utest

all: $(TARGET)

check: $(TARGET)
	@./$(TARGET) -v
	
valgrind_check: $(TARGET)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

recheck: clean check

clang_check: CXX = clang++
clang_check: check

clean:
	@$(RM) ./$(TARGET) $(OBJS)

utest.cpp: $(INCLUDES_DIR)/stack.hpp $(INCLUDES_DIR)/minimum_stack.hpp

$(SOURCES_DIR)/stack.o: $(SOURCES_DIR)/stack.cpp $(INCLUDES_DIR)/stack.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(SOURCES_DIR)/minimum_stack.o: $(SOURCES_DIR)/minimum_stack.cpp $(INCLUDES_DIR)/minimum_stack.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TARGET): utest.o $(SOURCES_DIR)/stack.o $(SOURCES_DIR)/minimum_stack.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

.PHONY: all clean check recheck clang_check
