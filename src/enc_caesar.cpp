#include "../inc/enc_caesar.hpp"

namespace enc
{
char Caesar_enc(char c)
{
    return 'A' + (c - 'A' + 3) % 26;
}

void Caesar::encrypt(Message const& m_original, Message& m_encrypted)
{
    const std::string& text = dynamic_cast<const TextMessage&>(m_original).getText();
    
    std::string transformedText = text;
    std::transform(transformedText.begin(), transformedText.end(), transformedText.begin(), Caesar_enc);

    dynamic_cast<TextMessage&>(m_encrypted).setText(transformedText);
}

}//namespace enc