#ifndef _ENC_CAESAR_
#define _ENC_CAESAR_
#include "../inc/precious_stone.hpp"

namespace enc
{
class Caesar: public Encoder
{
public:
    ~Caesar() = default;
    void encrypt(Message const& m_original, Message& m_encrypted) override;
};
}//namespace enc
#endif