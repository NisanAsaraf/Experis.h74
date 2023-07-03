#ifndef _ENC_ROT13_
#define _ENC_ROT13_
#include "../inc/enc_shifter.hpp"
namespace enc
{
class Rot13: public Shifter
{
public:
   Rot13();
    ~Rot13() = default;
    char shift(char c) override;
};

}//namespace enc
#endif
