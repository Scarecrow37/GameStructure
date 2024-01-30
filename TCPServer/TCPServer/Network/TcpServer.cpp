#include "TcpServer.h"

#include <exception>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

TcpServer::TcpServer() : Bound(false)
{
    WSAData WsaData;
    WSAStartup(MAKEWORD(2, 2), &WsaData);
    ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
}

TcpServer::~TcpServer()
{
    closesocket(ListenSocket);
    WSACleanup();
}

void TcpServer::Bind(const unsigned short Port)
{
    SOCKADDR_IN Address = {};
    Address.sin_family = AF_INET;
    Address.sin_addr.s_addr = htons(ADDR_ANY);
    Address.sin_port = htons(Port);
    const int Result = bind(ListenSocket, (SOCKADDR*)&Address, sizeof(Address));
    if (Result == 0)
    {
        Bound = true;
    }
    else
    {
        Bound = false;
        throw GetException("Bind fail.");
    }
}

std::exception TcpServer::GetException(const char* Message)
{
    const int ErrorCode = WSAGetLastError();
    return std::exception('[' + ErrorCode + ']' + Message);
}

