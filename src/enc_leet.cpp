#include "../inc/enc_leet.hpp"

namespace enc
{
char leet_enc(char c)
{   
     switch(toupper(c)) 
     {
        case 'A': return '4';
        case 'B': return '8';
        case 'C': return '(';
        case 'E': return '3';
        case 'G': return '6';
        case 'H': return '#';
        case 'I': return '1';
        case 'L': return '!';
        case 'O': return '0';
        case 'S': return '5';
        case 'T': return '7';
        case 'Z': return '2';
        default: return c;
    }
}

void Leet::encrypt(Message const& m_original, Message& m_encrypted)
{
    const std::string& text = dynamic_cast<const TextMessage&>(m_original).getText();
    
    std::string transformedText = text;
    std::transform(transformedText.begin(), transformedText.end(), transformedText.begin(), leet_enc);

    dynamic_cast<TextMessage&>(m_encrypted).setText(transformedText);
}
}//namespace enc