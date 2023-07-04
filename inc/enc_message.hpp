#ifndef _ENC_MESSAGE_
#define _ENC_MESSAGE_

#include <iostream>
#include <string>
namespace enc
{
class Message 
{
public:
    virtual ~Message() = default;
    virtual std::string::iterator begin() = 0;
    virtual std::string::iterator end() = 0;
    virtual void print() const = 0;
    virtual std::string getText()const = 0;
    virtual void setText(const char* text) = 0;
    virtual void setText(std::string const& text) = 0;
};

class TextMessage : public Message 
{
public:
    ~TextMessage() override = default;
    TextMessage(const char* text);
    TextMessage(std::string text);
    std::string::iterator begin() override;
    std::string::iterator end() override;
    std::string getText() const override ;
    void setText(const char* text) override ;
    void setText(std::string const& text) override;
    void print()const;

private:
    std::string m_text;
};
}//namespace enc
#endif