#include "../inc/UDP_server.hpp"
namespace enc
{
  UDP_server::UDP_server(int port)
    {
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) 
        {
            std::cerr << "Failed to create socket." <<'\n';
            return;
        }

        std::memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) 
        {
            std::cerr << "Failed to bind socket to address." <<'\n';
            return;
        }
    }

    UDP_server::~UDP_server()
    {
        close(sockfd);
    }

    bool UDP_server::sendMessage(const char* message, const struct sockaddr_in& clientAddr)
    {
        if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) < 0) 
        {
            std::cerr << "Failed to send message." <<'\n';
            return false;
        }
        return true;
    }

}//namespace enc