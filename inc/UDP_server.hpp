#ifndef UDP_SERVER
#define UDP_SERVER

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "../inc/enc_message.hpp"
namespace enc
{
class UDP_server
{
public:
    UDP_server(int port);
    ~UDP_server();
    bool sendMessage(Message const& message, const struct sockaddr_in& clientAddr);
    void start();
    void stop();
private:
    int sockfd;
    struct sockaddr_in serverAddr;
    bool server_stop;
};
}//namespace enc
#endif
