#include <exception>
#include <iostream>
#include <process.h>

#include "Database/MySql.h"
#include "Network/TcpServer.h"
#include "Models/User.h"


int main()
{ 
    TcpServer* server = new TcpServer;
    MySql& mySql = MySql::GetInstance();

    try
    {
        // Database Initialize
        mySql.Connect("127.0.0.1", "root", "1234");
        mySql.SetSchema("game");
        mySql.InitializeStatements();

        // Server Initialize
        server->Initialize();
        server->Bind(12345);
        server->Listen();

        server->Start();

        std::cin.get();
    }
    catch (std::exception& exception)
    {
        std::cout << "Program is crushed." << std::endl << exception.what() << std::endl;
    }
    delete server;
    return 0;
}