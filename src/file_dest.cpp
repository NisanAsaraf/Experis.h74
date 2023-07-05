#include "file_dest.hpp"
#include <fstream>


namespace comms
{
    FileDestination::FileDestination(std::string const& fileName)
        : m_filename(fileName)
    {

    }

    void FileDestination::SaveToFile(enc::Message* const& message)
    {
        std::ofstream outputFile(m_filename, std::ios::app);
        std::string text = message->getText();
        if (outputFile.is_open())
        {
            outputFile << text << '\n';
            outputFile.close();
        }
    }
}
