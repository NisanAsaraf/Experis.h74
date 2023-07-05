#ifndef _ENC_LEET_
#define _ENC_LEET_
#include "../inc/encoder.hpp"

namespace enc
{
class Leet: public Encoder
{
public:
    ~Leet() = default;
    void encrypt(Message const& m_original, Message& m_encrypted) override;
};

}//namespace enc
#endif