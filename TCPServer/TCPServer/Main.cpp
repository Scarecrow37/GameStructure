#include <exception>
#include <iostream>

#include "Database/MySql.h"
#include "Network/TcpServer.h"
#include "Models/User.h"

int main()
{
    TcpServer* server = new TcpServer;
    MySql* mySql = new MySql;

    try
    {
        mySql->Connect("127.0.0.1", "root", "1234");
        mySql->SetSchema("game");
        mySql->CreateStatement();
        User user = mySql->FindUser("AUserId");

        std::cout << user.Password;
        // Server->Initialize();
        // Server->Bind(12345);
        // Server->Listen();
        // Socket* Client = Server->Accept();
        // std::cout << "Debug Success" << std::endl;
    }
    catch (std::exception& exception)
    {
        std::cout << "Program is crushed." << std::endl << exception.what() << std::endl;
    }


    delete mySql;
    delete server;
    return 0;
}
