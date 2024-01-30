#include <exception>
#include <iostream>

#include "Network/TcpServer.h"

int main()
{
    TcpServer* Server = new TcpServer;

    try
    {
        Server->Bind(12345);
    }
    catch (std::exception& Exception)
    {
        std::cout << "Program is crushed." << std::endl << Exception.what() << std::endl;
    }
    
    delete Server;
    return 0;
}
