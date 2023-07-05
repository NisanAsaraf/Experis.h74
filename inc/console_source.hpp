#ifndef CONSOLE_SRC
#define CONSOLE_SRC
#include "enc_message.hpp"

namespace comms
{

class ConsoleSource
{
public:
    ConsoleSource() = default;
    void operator<<(enc::Message&) const;
};

}//namespace comms
#endif