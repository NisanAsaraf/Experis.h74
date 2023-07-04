#include "../inc/enc_upper.hpp"
#include "../inc/precious_stone.hpp"
namespace enc
{
void UpperCase::encrypt(Message const& m_original, Message& m_encrypted)
{
    const std::string& text = m_original.getText();
    
    std::string transformedText = text;
    std::transform(transformedText.begin(), transformedText.end(), transformedText.begin(), ::toupper);

    m_encrypted.setText(transformedText);
}
}//namespace enc