#ifndef _ENC_SCYTALE_
#define _ENC_SCYTALE_
#include "../inc/encoder.hpp"

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