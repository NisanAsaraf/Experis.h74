#ifndef UDP_SERVER
#define UDP_SERVER

#include "../inc/UDP_server.hpp"
#include "../inc/enc_leet.hpp"
#include "inc/console_dest.hpp"
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
            close(sockfd);
            return;
        }
        server_stop = false;
    }

    UDP_server::~UDP_server()
    {
        close(sockfd);
    }

    bool UDP_server::sendMessage(Message const& m_message, const struct sockaddr_in& clientAddr)
    {
        enc::Message* encrypted = new enc::TextMessage(m_message.getText());
        enc::Encoder* L = new enc::Leet;
        L->encrypt(m_message, *encrypted);//needs to be decrypt basically
        const char* buffer = encrypted->getText().c_str();

        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) < 0) 
        {
            std::cerr << "Failed to send message." <<'\n';
            return false;
        }
        return true;
    }

    void UDP_server::start()
    {
        char buffer[1024];
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLength = sizeof(clientAddr);

        while (!server_stop)
        {
            ssize_t bytesRead = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&clientAddr, &clientAddrLength);
            if (bytesRead < 0)
            {
                std::cerr << "Failed to receive message." << '\n';
                break;
            }

            buffer[bytesRead] = '\0';
            std::string receivedMessage(buffer);
            std::cout << "Received message from client: " << receivedMessage << '\n';

            if (!sendMessage(TextMessage(receivedMessage), clientAddr))
            {
                std::cerr << "Failed to send echo message." << '\n';
                break;
            }
        }
    }

    void UDP_server::stop()
    {
        server_stop = true;
    }    
}//namespace enc
#endif
