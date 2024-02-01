#include "TcpServer.h"

#include <cstdio>
#include <exception>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

TcpServer::TcpServer() : _listenSocket(INVALID_SOCKET), _initialized(false), _bound(false), _listened(false)
{
    WSAData WsaData;
    WSAStartup(MAKEWORD(2, 2), &WsaData);
}

TcpServer::~TcpServer()
{
    if (_initialized)
    {
        closesocket(_listenSocket);
    }
    WSACleanup();
}

void TcpServer::Initialize()
{
    _listenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_listenSocket == INVALID_SOCKET)
    {
        _initialized = false;
        throw GetException("Create listen socket fail.");
    }
    else
    {
        _initialized = true;
    }
}

void TcpServer::Bind(const unsigned short port)
{
    if (!_initialized)
    {
        _bound = false;
        throw GetException("Initialize first before bind.");
    }
    SOCKADDR_IN Address = {};
    Address.sin_family = AF_INET;
    Address.sin_addr.s_addr = htons(ADDR_ANY);
    Address.sin_port = htons(port);
    const int Result = bind(_listenSocket, (SOCKADDR*)&Address, sizeof(Address));
    if (Result == 0)
    {
        _bound = true;
    }
    else
    {
        _bound = false;
        throw GetException("Bind fail.");
    }
}

void TcpServer::Listen(const int backlog)
{
    if (!_bound)
    {
        _listened = false;
        throw GetException("Bind socket first before listen.");
    }
    const int Result = listen(_listenSocket, backlog);
    if (Result == 0)
    {
        _listened = true;
    }
    else
    {
        _listened = false;
        throw GetException("Listen fail.");
    }
}

Socket* TcpServer::Accept()
{
    SOCKADDR_IN Address;
    int AddressLength = sizeof(Address);
    SOCKET Client = accept(_listenSocket, (SOCKADDR*)&Address, &AddressLength);
    if (Client == INVALID_SOCKET)
    {
        throw GetException("Accept socket is invalid.");
    }
    return new Socket(Client);
}

std::exception TcpServer::GetException(const char* message)
{
    const int errorCode = WSAGetLastError();
    const size_t length = 1 + sizeof(int) + strlen(message);
    char* exceptionMessage = new char[length];
    int result = sprintf_s(exceptionMessage,length,"[%d] %s", errorCode, message);
    return std::exception(exceptionMessage);
}

