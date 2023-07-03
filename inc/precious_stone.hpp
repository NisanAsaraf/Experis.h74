#ifndef _ENCODER_
#define _ENCODER_

#include "enc_message.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>
#include <cstring>
#include <unordered_map>

namespace enc
{
class Encoder
{
public:
    virtual ~Encoder() = default;
    virtual void encrypt(Message const& m_original, Message& m_encrypted) = 0;
protected:
    Encoder() = default;
    Encoder(Encoder const&) = default;
    Encoder& operator=(Encoder const&) = default;
};

}//namespace enc
#endif