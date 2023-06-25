#include "mu_test.h"
#include <string>

#include "../../inc/frequency_table.hpp"

BEGIN_TEST(split_words)
std::string text = "It was in July, 1805, and the speaker was the well-known Anna Pavlovna Scherer, maid of honor and favorite of the Empress Marya Fedorovna.";
ds::WordCounter wordCounter;
std::vector<std::string> words = wordCounter.split_words(text);

ASSERT_THAT(words.at(0) == "it");
ASSERT_THAT(words.at(5) == "the");
END_TEST

BEGIN_TEST(word_frequency_vector)
std::string text = "It was in July, 1805, and the speaker was the well-known Anna Pavlovna Scherer, maid of honor and favorite of the Empress Marya Fedorovna.";
ds::WordCounter wordCounter;
std::vector<std::pair<std::string, int>> words = wordCounter.word_frequency_vector(text);
// std::cout << words[0].first << ": " << words[0].second << '\n';
ASSERT_THAT(words.at(0).first == "the");

END_TEST


TEST_SUITE(決して道から外れてはいけません)
TEST(split_words)
TEST(word_frequency_vector)
END_SUITE
