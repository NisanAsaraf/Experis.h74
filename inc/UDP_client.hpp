#ifndef UDP_CLIENT
#define UDP_CLIENT

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "../inc/enc_message.hpp"
namespace enc
{
class UDP_client
{
public:
    UDP_client(int serverPort);
    ~UDP_client();
    bool sendMessage(Message const& message);
private:
    int sockfd;
    struct sockaddr_in serverAddr;
};
}//namespace enc
#endif