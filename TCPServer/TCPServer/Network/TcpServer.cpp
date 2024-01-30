#include "TcpServer.h"
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

TcpServer::TcpServer()
{
    WSAData WsaData;
    WSAStartup(MAKEWORD(2, 2), &WsaData);
}

TcpServer::~TcpServer()
{
    WSACleanup();
}
