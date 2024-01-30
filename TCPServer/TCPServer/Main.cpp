#include <exception>
#include <iostream>

#include "Network/TcpServer.h"

int main()
{
    TcpServer* Server = new TcpServer;

    try
    {
        Server->Bind(12345);
        Server->Listen();
        Socket* Client = Server->Accept();
        std::cout << "Debug Success" << std::endl;
    }
    catch (std::exception& Exception)
    {
        std::cout << "Program is crushed." << std::endl << Exception.what() << std::endl;
    }


    delete Server;
    return 0;
}
