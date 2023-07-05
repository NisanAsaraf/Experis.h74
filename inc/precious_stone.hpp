#ifndef STONE
#define STONE
#include "console_source.hpp"
#include "console_dest.hpp"
#include "encoder.hpp"
#include "UDP_server.hpp"
#include "UDP_client.hpp"
#include "file_dest.hpp"

namespace comms
{
class PreciousStone
{
public:
    PreciousStone(ConsoleSource&, FileDestination&, enc::Encoder&);
    void execute();
private:
    ConsoleSource* CS;
    FileDestination* FD;
    enc::Encoder* EC;

};

}//namespace comms
#endif
