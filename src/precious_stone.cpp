#include "../inc/enc_upper.hpp"
#include "../inc/enc_vowels.hpp"

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


}//namespace ENC