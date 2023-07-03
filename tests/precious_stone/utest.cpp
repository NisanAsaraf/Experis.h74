#include "mu_test.h"
#include <string>
#include "../inc/precious_stone.hpp"
#include "../inc/enc_upper.hpp"
#include "../inc/enc_vowels.hpp"
#include "../inc/enc_caesar.hpp"
#include "../inc/enc_leet.hpp"
#include "../inc/enc_scytale.hpp"

BEGIN_TEST(UPPER)
    std::string text = "hello Javaestas!";
    enc::Message* original = new enc::TextMessage(text);
    enc::Message* encrypted = new enc::TextMessage(text);
    enc::Encoder* UP = new enc::UpperCase;
    UP->encrypt(*original, *encrypted);
    encrypted->print();    
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(vowels)
    std::string text = "hello Javaestas!";
    enc::Message* original = new enc::TextMessage(text);
    enc::Message* encrypted = new enc::TextMessage(text);
    enc::Encoder* V = new enc::Vowels;
    V->encrypt(*original, *encrypted);
    encrypted->print();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(caesar)
    std::string text = "hello Javaestas!";
    enc::Message* original = new enc::TextMessage(text);
    enc::Message* encrypted = new enc::TextMessage(text);
    enc::Encoder* C = new enc::Caesar;
    C->encrypt(*original, *encrypted);
    encrypted->print();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(leet)
    std::string text = "hello Javaestas!";
    enc::Message* original = new enc::TextMessage(text);
    enc::Message* encrypted = new enc::TextMessage(text);
    enc::Encoder* L = new enc::Leet;
    L->encrypt(*original, *encrypted);
    encrypted->print();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(scytale)
    std::string text = "hello Javaestas!";
    enc::Message* original = new enc::TextMessage(text);
    enc::Message* encrypted = new enc::TextMessage(text);
    enc::Encoder* S = new enc::Scytale;
    S->encrypt(*original, *encrypted);
    encrypted->print();    
    ASSERT_THAT(true);
END_TEST

TEST_SUITE(決して道から外れてはいけません)
TEST(UPPER)
TEST(vowels)
TEST(caesar)
TEST(leet)
TEST(scytale)
END_SUITE
