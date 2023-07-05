#ifndef FILE_DEST
#define FILE_DEST
#include <string>
#include <fstream>
#include <iostream>
#include "../inc/enc_message.hpp"

namespace comms
{

class FileDestination
{
public:
explicit FileDestination(std::string const& m_fileName);

void SaveToFile(enc::Message* const& message);

private:
    std::string m_filename;
};

}


#endif