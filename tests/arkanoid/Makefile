CXX = g++
CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17 
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR)

SFML_LIBS =  -lsfml-graphics -lsfml-window -lsfml-system 
SFML_LIB_DIR = /usr/lib  

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o window.o animations.o player.o UI.o paddle.o ball.o block.o scenes.o collisions.o leaderboard.o
TARGET = utest

all: $(TARGET)

check: $(TARGET)
	@./$(TARGET) -v
	@make

valgrind_check: $(TARGET)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

recheck: clean check

g++_check: CXX = g++
g++_check: check

clean:
	@$(RM) $(TARGET) $(OBJS)

utest.o: utest.cpp 
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

window.o: $(SOURCES_DIR)/window.cpp $(INCLUDES_DIR)/window.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

animations.o: $(SOURCES_DIR)/animations.cpp $(INCLUDES_DIR)/animations.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@	

player.o: $(SOURCES_DIR)/player.cpp $(INCLUDES_DIR)/player.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

UI.o: $(SOURCES_DIR)/UI.cpp $(INCLUDES_DIR)/UI.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

paddle.o: $(SOURCES_DIR)/paddle.cpp $(INCLUDES_DIR)/paddle.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

ball.o: $(SOURCES_DIR)/ball.cpp $(INCLUDES_DIR)/ball.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

block.o: $(SOURCES_DIR)/block.cpp $(INCLUDES_DIR)/block.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

scenes.o: $(SOURCES_DIR)/scenes.cpp $(INCLUDES_DIR)/scenes.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@	

collisions.o: $(SOURCES_DIR)/collisions.cpp $(INCLUDES_DIR)/collisions.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@	

leaderboard.o: $(SOURCES_DIR)/leaderboard.cpp $(INCLUDES_DIR)/leaderboard.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@	

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(SFML_LIBS) -L$(SFML_LIB_DIR)

.PHONY: all clean check recheck g++_check
