#ifndef _ENC_VOWELS_
#define _ENC_VOWELS_
#include "../inc/precious_stone.hpp"

namespace enc
{

class Vowels: public Encoder
{
public:
    ~Vowels() = default;
    void encrypt(Message const& m_original, Message& m_encrypted) override;
};

}//namespace enc
#endif