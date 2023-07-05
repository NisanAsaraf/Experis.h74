#include "console_dest.hpp"
#include <iostream>

namespace comms
{

enc::Message* ConsoleDest::operator>>(enc::Message& m_message)
{
    std::string text = m_message.getText();
    std::cout<<text<<'\n';
}

}//namespace comms