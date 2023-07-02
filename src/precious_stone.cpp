#include "../inc/enc_upper.hpp"
#include "../inc/enc_vowels.hpp"
#include "../inc/enc_caesar.hpp"
#include "../inc/enc_leet.hpp"
#include "../inc/enc_scytale.hpp"
namespace ENC
{
Message* UpperCase::encrypt(Message const& m_msg)
{
    const std::string& text = dynamic_cast<const TextMessage&>(m_msg).getText();
    
    std::string transformedText = text;
    std::transform(transformedText.begin(), transformedText.end(), transformedText.begin(), ::toupper);

    return new TextMessage(transformedText);
}


char vowel_replace_char(char c)
{
    std::string vowels = "aeiouyw";

    if (vowels.find(std::tolower(c)) != std::string::npos)
    {
        return '*';
    }
    return c;
}

Message* Vowels::encrypt(Message const& m_msg)
{
    const std::string& text = dynamic_cast<const TextMessage&>(m_msg).getText();
    
    std::string transformedText = text;
    std::transform(transformedText.begin(), transformedText.end(), transformedText.begin(), vowel_replace_char);

    return new TextMessage(transformedText);
}

char Caesar_enc(char c)
{
    return 'A' + (c - 'A' + 3) % 26;
}


Message* Caesar::encrypt(Message const& m_msg)
{
    const std::string& text = dynamic_cast<const TextMessage&>(m_msg).getText();
    
    std::string transformedText = text;
    std::transform(transformedText.begin(), transformedText.end(), transformedText.begin(), Caesar_enc);

    return new TextMessage(transformedText);
}


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

Message* Leet::encrypt(Message const& m_msg)
{
    const std::string& text = dynamic_cast<const TextMessage&>(m_msg).getText();
    
    std::string transformedText = text;
    std::transform(transformedText.begin(), transformedText.end(), transformedText.begin(), leet_enc);
    return new TextMessage(transformedText);
}

char scytale_enc(char c)
{
    double pi = 3.14;
    int numRows = std::ceil(26.0 / pi);
    int index = c - 'A';
    int row = index % numRows;
    int col = index / numRows;
    int newIndex = row * pi + col;

    return static_cast<char>(newIndex + 'A');
}

Message* Scytale::encrypt(Message const& m_msg)
{
    const std::string& text = dynamic_cast<const TextMessage&>(m_msg).getText();
    
    std::string transformedText = text;
    std::transform(transformedText.begin(), transformedText.end(), transformedText.begin(), scytale_enc);
    return new TextMessage(transformedText);
}

}//namespace ENC