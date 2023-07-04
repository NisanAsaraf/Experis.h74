#include "inc/UDP_client.hpp"

namespace enc
{
    UDP_client::UDP_client(int serverPort)
    {
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) 
        {
            std::cerr << "Failed to create socket." << '\n';
            return;
        }

        std::memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    }

    UDP_client::~UDP_client()
    {
        close(sockfd);
    }

    bool UDP_client::sendMessage(const char* message)
    {
        if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) 
        {
            std::cerr << "Failed to send message." << '\n';
            return false;
        }
        return true;
    }

}//namespace enc