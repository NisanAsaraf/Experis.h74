#ifndef STONE
#define STONE
#include "../inc/console_source.hpp"
#include "../inc/console_dest.hpp"
#include "../inc/encoder.hpp"
#include "../inc/UDP_server.hpp"
#include "../inc/UDP_client.hpp"
#include "../inc/file_dest.hpp"

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
