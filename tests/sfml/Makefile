CXX = g++
CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17 
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR)

SFML_LIBS =  -lsfml-graphics -lsfml-window -lsfml-system
SFML_LIB_DIR = /usr/lib  

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o
TARGET = utest

all: $(TARGET)

check: $(TARGET)
	@./$(TARGET) -v
	@make clean

valgrind_check: $(TARGET)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

recheck: clean check

g++_check: CXX = g++
g++_check: check

clean:
	@$(RM) $(TARGET) $(OBJS)

utest.o: utest.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(SFML_LIBS) -L$(SFML_LIB_DIR)

.PHONY: all clean check recheck g++_check
