#ifndef _ENC_UPPER_
#define _ENC_UPPER_
#include "../inc/encoder.hpp"

namespace enc
{
class UpperCase : public Encoder
{
public:
    ~UpperCase() = default;
    void encrypt(Message const& m_original, Message& m_encrypted) override;
};

}//namespace enc
#endif