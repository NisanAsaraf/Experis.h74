CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = .

OBJS = utest.o freq.o
TARGET = utest
TARGET_FREQ = freq

all: $(TARGET) $(TARGET_FREQ)

check: $(TARGET)
	@./$(TARGET) -v
	@make clean

valgrind_check: $(TARGET)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

recheck: clean check

clang_check: CXX = clang++
clang_check: check

clean:
	@$(RM) ./$(TARGET) ./$(TARGET_FREQ) $(OBJS)

utest.o: $(INCLUDES_DIR)/frequency_table.hpp

freq.o: $(INCLUDES_DIR)/frequency_table.hpp

$(TARGET): utest.o $(INCLUDES_DIR)/frequency_table.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

$(TARGET_FREQ): freq.o $(INCLUDES_DIR)/frequency_table.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

.PHONY: all clean check recheck clang_check
