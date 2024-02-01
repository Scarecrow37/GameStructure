#include "TcpServer.h"

#include <cstdio>
#include <exception>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

TcpServer::TcpServer() : _listenSocket(INVALID_SOCKET), _initialized(false), _bound(false), _listened(false)
{
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
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
    SOCKADDR_IN address = {};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htons(ADDR_ANY);
    address.sin_port = htons(port);
    const int result = bind(_listenSocket, (SOCKADDR*)&address, sizeof(address));
    if (result == 0)
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
    const int result = listen(_listenSocket, backlog);
    if (result == 0)
    {
        _listened = true;
    }
    else
    {
        _listened = false;
        throw GetException("Listen fail.");
    }
}

Socket* TcpServer::Accept() const
{
    SOCKADDR_IN address;
    int addressLength = sizeof(address);
    const SOCKET client = accept(_listenSocket, (SOCKADDR*)&address, &addressLength);
    if (client == INVALID_SOCKET)
    {
        throw GetException("Accept socket is invalid.");
    }
    return new Socket(client);
}

std::exception TcpServer::GetException(const char* message)
{
    const int errorCode = WSAGetLastError();
    const size_t length = 1 + sizeof(int) + strlen(message);
    char* exceptionMessage = new char[length];
    auto _ = sprintf_s(exceptionMessage,length,"[%d] %s", errorCode, message);
    delete[] exceptionMessage;
    return std::exception(exceptionMessage);
}

