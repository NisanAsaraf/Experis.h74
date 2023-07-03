#include "../inc/enc_message.hpp"
namespace enc
{
TextMessage::TextMessage(const char* text) 
:m_text{text} 
{
}

TextMessage::TextMessage(std::string text)
:m_text{text} 
{
}

std::string::iterator TextMessage::begin()
{
return m_text.begin(); 
}

std::string::iterator TextMessage::end()
{
return m_text.end(); 
}
std::string TextMessage::getText() const
{
return m_text;
}

void TextMessage::setText(const char* text)
{
m_text = text;
}
void TextMessage::setText(std::string text)
{
m_text = text;
}

void TextMessage::print() const
{
std::cout << m_text << '\n';
};

}//namespace enc