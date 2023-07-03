#ifndef _ENC_CAESAR_
#define _ENC_CAESAR_
#include "../inc/enc_shifter.hpp"
namespace enc
{
class Caesar: public Shifter
{
public:
    Caesar();
    ~Caesar() = default;
    char shift(char c) override;
};

}//namespace enc
#endif
