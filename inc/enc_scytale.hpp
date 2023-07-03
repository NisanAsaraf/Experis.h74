#ifndef _ENC_SCYTALE_
#define _ENC_SCYTALE_
#include "../inc/precious_stone.hpp"

namespace enc
{
class Scytale: public Encoder
{
public:
    ~Scytale() = default;
    void encrypt(Message const& m_original, Message& m_encrypted) override;
};

}//namespace enc
#endif