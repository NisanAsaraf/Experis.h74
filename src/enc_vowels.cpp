#include "../inc/enc_vowels.hpp"

namespace enc
{
char vowel_replace_char(char c)
{
    std::string vowels = "aeiouyw";

    if (vowels.find(std::tolower(c)) != std::string::npos)
    {
        return '*';
    }
    return c;
}

void Vowels::encrypt(Message const& m_original, Message& m_encrypted)
{
    const std::string& text = dynamic_cast<const TextMessage&>(m_original).getText();
    
    std::string transformedText = text;
    std::transform(transformedText.begin(), transformedText.end(), transformedText.begin(), &vowel_replace_char);

    dynamic_cast<TextMessage&>(m_encrypted).setText(transformedText);
}

}//namespace enc