#ifndef _ENC_MESSAGE_
#define _ENC_MESSAGE_

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>
#include <cstring>
#include <unordered_map>

namespace enc
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
    TextMessage(const char* text);
    TextMessage(std::string text);
    std::string::iterator begin() override;
    std::string::iterator end() override;
    std::string getText()const;
    void setText(const char* text);
    void setText(std::string text);

    void print()const;
};
}//namespace enc
#endif