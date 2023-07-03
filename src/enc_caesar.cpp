#include "../inc/enc_caesar.hpp"

namespace enc
{
Caesar::Caesar()
:Shifter(3)
{

}

char Caesar::shift(char c)
{
    return 'A' + (c - 'A' + shiftAmount) % 26;
}

}//namespace enc