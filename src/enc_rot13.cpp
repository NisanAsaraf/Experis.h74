#include "../inc/enc_rot13.hpp"

namespace enc
{
Rot13::Rot13()
:Shifter(13)
{

}

char Rot13::shift(char c)
{
    return 'A' + (c - 'A' + shiftAmount) % 26;
}

}//namespace enc