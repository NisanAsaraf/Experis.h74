#include "../inc/UDP_client.hpp"
#include "../inc/enc_leet.hpp"
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

    bool UDP_client::sendMessage(Message const& m_message)
    {
        enc::Message* encrypted = new enc::TextMessage(m_message.getText());
        enc::Encoder* L = new enc::Leet;
        L->encrypt(m_message, *encrypted);
        const char* buffer = encrypted->getText().c_str();

        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) 
        {
            std::cerr << "Failed to send message." << '\n';
            return false;
        }
        return true;
    }

    Message* UDP_client::recieveMessage() 
    {
        char buffer[1024];
        struct sockaddr_in serverAddr;
        socklen_t serverAddrLength = sizeof(serverAddr);

        ssize_t bytesRead = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, &serverAddrLength);
        if (bytesRead < 0)
        {
            std::cerr << "Failed to receive message." << '\n';
            return nullptr;
        }

        std::string receivedText(buffer, bytesRead);
        return new TextMessage(receivedText);
    }

}//namespace enc