CXX = clang++
CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../inc/inl

OBJS = utest.o
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
	@$(RM) $(TARGET) $(OBJS)

utest.o: utest.cpp $(INCLUDES_DIR)/vault_secrets.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

vault.hxx: $(SOURCES_DIR)/vault_secrets.hxx
	@echo "Not compiling header file"

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

.PHONY: all clean check recheck clang_check