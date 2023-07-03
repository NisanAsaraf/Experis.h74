#ifndef _ENC_COM_ROT13_
#define _ENC_COM_ROT13_
#include "../inc/enc_caesar.hpp"
namespace enc
{
class Rot13_comp 
{
public:
    Rot13_comp();
    ~Rot13_comp() = default;

    void encrypt(Message const& m_original, Message& m_encrypted);

private:
    Caesar* caesar;
};
}//namespace enc
#endif
