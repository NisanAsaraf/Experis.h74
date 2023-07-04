#include "mu_test.h"
#include <string>
#include "../inc/UDP_client.hpp"
#include "../inc/UDP_server.hpp"
#include "../inc/enc_trans_cipher.hpp"
#include "../inc/enc_message.hpp"
#include "../inc/precious_stone.hpp"
#include "../inc/enc_com_rot13.hpp"
#include "../inc/enc_shifter.hpp"
#include "../inc/enc_upper.hpp"
#include "../inc/enc_vowels.hpp"
#include "../inc/enc_caesar.hpp"
#include "../inc/enc_rot13.hpp"
#include "../inc/enc_leet.hpp"
#include "../inc/enc_scytale.hpp"
#include <thread>
#include <iostream>
#include <fstream>

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
    enc::Encoder* C = new enc::Caesar(3);
    C->encrypt(*original, *encrypted);
    encrypted->print();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(rot13)
    std::string text = "hello Javaestas!";
    enc::Message* original = new enc::TextMessage(text);
    enc::Message* encrypted = new enc::TextMessage(text);
    enc::Encoder* C = new enc::Rot13;
    C->encrypt(*original, *encrypted);
    encrypted->print();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(rot13_comp)
    std::string text = "hello Javaestas!";
    enc::Message* original = new enc::TextMessage(text);
    enc::Message* encrypted = new enc::TextMessage(text);
    enc::Rot13_comp* C = new enc::Rot13_comp();
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

BEGIN_TEST(trans_cipher)
    std::string text = "hello Javaestas!";
    enc::Message* original = new enc::TextMessage(text);
    enc::Message* encrypted = new enc::TextMessage(text);
    std::string key = "MONEY";
    enc::Encoder* T = new enc::Trans_Cipher(key);
    T->encrypt(*original, *encrypted);
    encrypted->print();    
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(server_test)
    std::string text;
    std::ofstream outputFile("client_source.txt",std::ios::app);
    std::cout << "Enter text:" << '\n';
    std::cin >> text;
    outputFile << text << '\n';
    outputFile.close();


    enc::Message* original = new enc::TextMessage(text);
    enc::UDP_server server(8080);

    std::thread serverThread([&server]()
    {//lambda the server class on a different thread , so to not write another test to split the process's...
        server.start(); 
    }); 

    enc::UDP_client client(8080);
    client.sendMessage(*original);  
    server.stop();

    serverThread.join();
    ASSERT_THAT(true);
END_TEST


TEST_SUITE(決して道から外れてはいけません)

IGNORE_TEST(UPPER)
IGNORE_TEST(vowels)
IGNORE_TEST(caesar)
IGNORE_TEST(rot13)
IGNORE_TEST(rot13_comp)
IGNORE_TEST(leet)
IGNORE_TEST(scytale)
IGNORE_TEST(trans_cipher)
TEST(server_test)

END_SUITE
