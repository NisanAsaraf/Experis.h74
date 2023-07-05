#include "precious_stone.hpp"
#include "enc_message.hpp"
#include <thread>

namespace comms
{
    PreciousStone::PreciousStone(ConsoleSource& cs, FileDestination& fd, enc::Encoder& ec)
    : CS(&cs)
    , FD(&fd)
    , EC(&ec)
    {
    }

    void PreciousStone::execute()
    {
        enc::Message* original = new enc::TextMessage();
        enc::Message* encrypted = new enc::TextMessage();
        std::cout << "Enter a message:\n";
        *CS << *original;
        (*FD).SaveToFile(original);

        enc::UDP_server* server = new enc::UDP_server(8088);

        std::thread serverThread([&server]()
        {//lambda the server class on a different thread , so to not write another test to split the process's...
            server->start(); 
        }); 

        enc::UDP_client client(8080);
        client.sendMessage(*original);  
        EC->encrypt(*original, *encrypted);

        encrypted = client.recieveMessage();
        //encrypted->print();
        
        serverThread.join();
        server->stop();
    }
}
