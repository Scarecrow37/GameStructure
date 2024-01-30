#include "TcpServer.h"

#include <exception>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

TcpServer::TcpServer() : Bound(false), Listened(false)
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

void TcpServer::Listen(const int Backlog)
{
    if (!Bound)
    {
        Listened = false;
        throw GetException("Bind socket first before listen.");
    }
    const int Result = listen(ListenSocket, Backlog);
    if (Result == 0)
    {
        Listened = true;
    }
    else
    {
        Listened = false;
        throw GetException("Listen fail.");
    }
}

void TcpServer::Accept()
{
    SOCKADDR_IN Address;
    int AddressLength = sizeof(Address);
    SOCKET Client = accept(ListenSocket, (SOCKADDR*)&Address, &AddressLength);
    if (Client == INVALID_SOCKET)
    {
        throw GetException("Accept socket is invalid.");
    }
    // TODO Return Socket.
}

std::exception TcpServer::GetException(const char* Message)
{
    const int ErrorCode = WSAGetLastError();
    return std::exception('[' + ErrorCode + ']' + Message);
}

