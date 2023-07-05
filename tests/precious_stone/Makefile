CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o enc_message.o enc_shifter.o enc_com_rot13.o enc_rot13.o enc_caesar.o enc_leet.o enc_scytale.o enc_upper.o enc_vowels.o enc_trans_cipher.o UDP_server.o UDP_client.o console_source.o
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

enc_message.o:$(SOURCES_DIR)/enc_message.cpp $(INCLUDES_DIR)/enc_message.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

enc_shifter.o: $(SOURCES_DIR)/enc_shifter.cpp $(INCLUDES_DIR)/enc_shifter.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

enc_caesar.o: $(SOURCES_DIR)/enc_caesar.cpp $(INCLUDES_DIR)/enc_caesar.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

enc_rot13.o: $(SOURCES_DIR)/enc_rot13.cpp $(INCLUDES_DIR)/enc_rot13.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

enc_com_rot13.o: $(SOURCES_DIR)/enc_com_rot13.cpp $(INCLUDES_DIR)/enc_com_rot13.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

enc_leet.o: $(SOURCES_DIR)/enc_leet.cpp $(INCLUDES_DIR)/enc_leet.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

enc_scytale.o: $(SOURCES_DIR)/enc_scytale.cpp $(INCLUDES_DIR)/enc_scytale.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

enc_upper.o: $(SOURCES_DIR)/enc_upper.cpp $(INCLUDES_DIR)/enc_upper.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

enc_vowels.o: $(SOURCES_DIR)/enc_vowels.cpp $(INCLUDES_DIR)/enc_vowels.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

enc_trans_cipher.o: $(SOURCES_DIR)/enc_trans_cipher.cpp $(INCLUDES_DIR)/enc_trans_cipher.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

UDP_server.o: $(SOURCES_DIR)/UDP_server.cpp $(INCLUDES_DIR)/UDP_server.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

UDP_client.o: $(SOURCES_DIR)/UDP_client.cpp $(INCLUDES_DIR)/UDP_client.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

console_source.o: $(SOURCES_DIR)/console_source.cpp $(INCLUDES_DIR)/console_source.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TARGET): utest.o enc_message.o enc_shifter.o enc_rot13.o enc_com_rot13.o enc_caesar.o enc_leet.o enc_scytale.o enc_upper.o enc_vowels.o enc_trans_cipher.o UDP_client.o UDP_server.o console_source.o $(INCLUDES_DIR)/precious_stone.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

.PHONY: all clean check recheck clang_check
