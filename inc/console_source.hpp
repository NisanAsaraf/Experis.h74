#include "enc_message.hpp"

namespace comms
{

class ConsoleSource
{
    public:
    void operator<<(enc::Message&);
};

}//namespace comms