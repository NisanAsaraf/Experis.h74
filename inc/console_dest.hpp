#ifndef CONSOLE_DEST
#define CONSOLE_DEST
#include "enc_message.hpp"

namespace comms
{

class ConsoleDest
{
    public:
    enc::Message* operator>>(enc::Message&);
};

}//namespace comms
#endif