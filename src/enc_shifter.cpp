#include "../inc/enc_shifter.hpp"
namespace enc
{

Shifter::Shifter(int n)
:shiftAmount(n)
{

}

char Shifter::shift(char c)
{
    return 'A' + (c - 'A' + shiftAmount) % 26;
}

void Shifter::encrypt(Message const& m_original, Message& m_encrypted)
{
    const std::string& text = dynamic_cast<const TextMessage&>(m_original).getText();
    
    std::string transformedText = text;
    std::transform(transformedText.begin(), transformedText.end(), transformedText.begin(), [this](char c) { return this->shift(c); });

    dynamic_cast<TextMessage&>(m_encrypted).setText(transformedText);
}


}//namespace enc