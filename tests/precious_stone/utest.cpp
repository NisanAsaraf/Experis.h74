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
    ENC::Message* p = new ENC::TextMessage(text);
    ENC::Encryption* UP = new ENC::UpperCase;
    ENC::Message* encryptedMessage = UP->encrypt(*p);
    encryptedMessage->print();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(vowels)
    std::string text = "hello Javaestas!";
    ENC::Message* p = new ENC::TextMessage(text);
    ENC::Encryption* V = new ENC::Vowels;
    ENC::Message* encryptedMessage = V->encrypt(*p);
    encryptedMessage->print();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(caesar)
    std::string text = "hello Javaestas!";
    ENC::Message* p = new ENC::TextMessage(text);
    ENC::Encryption* C = new ENC::Caesar;
    ENC::Message* encryptedMessage = C->encrypt(*p);
    encryptedMessage->print();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(leet)
    std::string text = "hello Javaestas!";
    ENC::Message* p = new ENC::TextMessage(text);
    ENC::Encryption* L = new ENC::Leet;
    ENC::Message* encryptedMessage = L->encrypt(*p);
    encryptedMessage->print();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(scytale)
    std::string text = "hello Javaestas!";
    ENC::Message* p = new ENC::TextMessage(text);
    ENC::Encryption* S = new ENC::Scytale;
    ENC::Message* encryptedMessage = S->encrypt(*p);
    encryptedMessage->print();
    ASSERT_THAT(true);
END_TEST


TEST_SUITE(決して道から外れてはいけません)
TEST(UPPER)
TEST(vowels)
TEST(caesar)
TEST(leet)
TEST(scytale)
END_SUITE
