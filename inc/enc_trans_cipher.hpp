#ifndef _ENC_TRANS_CIPHER_
#define _ENC_TRANS_CIPHER_
#include "../inc/encoder.hpp"

namespace enc
{
class Trans_Cipher: public Encoder
{
public:
    Trans_Cipher(std::string const&);
    Trans_Cipher(char* const&);
    ~Trans_Cipher() = default;
    void encrypt(Message const& m_original, Message& m_encrypted) override;

protected:
    std::string m_key;
};

}//namespace enc
#endif