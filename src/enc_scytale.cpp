#include "../inc/enc_scytale.hpp"
namespace enc
{

char scytale_enc(char c)
{
    double p = 3;
    int numRows = std::ceil(26.0 / p);
    int index = c - 'A';
    int row = index % numRows;
    int col = index / numRows;
    int newIndex = row * p + col;   //can be changed to whatever, this is the "key"

    return static_cast<char>(newIndex + 'A');
}

void Scytale::encrypt(Message const& m_original, Message& m_encrypted)
{
    const std::string& text = dynamic_cast<const TextMessage&>(m_original).getText();
    
    std::string transformedText = text;
    std::transform(transformedText.begin(), transformedText.end(), transformedText.begin(), scytale_enc);

    dynamic_cast<TextMessage&>(m_encrypted).setText(transformedText);
}

}//namespace enc