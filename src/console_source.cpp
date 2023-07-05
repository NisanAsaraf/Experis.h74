#include "console_source.hpp"
#include <iostream>

namespace comms
{
void ConsoleSource::operator<<(enc::Message& m_message) const
{
    std::string text;
    std::string line;
    do
    {
        std::getline(std::cin, line);
        text += line;
    } while (!line.empty());
    m_message.setText(text);
}

}//namespace comms