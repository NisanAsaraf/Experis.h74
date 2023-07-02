#ifndef __precious_stone__
#define __precious_stone__

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>
#include <cstring>
#include <unordered_map>

namespace ENC
{
class Message 
{
public:
    virtual ~Message() = default;
    virtual std::string::iterator begin() = 0;
    virtual std::string::iterator end() = 0;
    virtual void print() const = 0;
};

class TextMessage : public Message 
{
    std::string m_text;
public:
    ~TextMessage() override = default;
    TextMessage(const char* text) : m_text{text} {}
    TextMessage(std::string text) : m_text{text} {}
    std::string::iterator begin() override { return m_text.begin(); }
    std::string::iterator end() override { return m_text.end(); }
    std::string getText()const{return m_text;}
    void print() const override {std::cout << m_text << '\n';};
};

class Encryption 
{
public:
    virtual ~Encryption() = default;
    virtual Message* encrypt(Message const&) = 0;
protected:
    Encryption() = default;
    Encryption(Encryption const&) = default;
    Encryption& operator=(Encryption const&) = default;
};

}//namespace ENC
#endif