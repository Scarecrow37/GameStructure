#include "TcpServer.h"

#include <cstdio>
#include <exception>
#include <WinSock2.h>

#include "../Thread/ThreadEx.h"

#pragma comment(lib, "ws2_32")

TcpServer::TcpServer() : _listenSocket(INVALID_SOCKET), _isInitialized(false), _isBound(false), _isListened(false),
                         _isAccepting(false)
{
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}

TcpServer::~TcpServer()
{
    if (_isInitialized)
    {
        closesocket(_listenSocket);
    }
    if (_isAccepting)
    {
        _isAccepting = false;
    }
    WSACleanup();
}

void TcpServer::Initialize()
{
    _listenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_listenSocket == INVALID_SOCKET)
    {
        _isInitialized = false;
        throw GetException("Create listen socket fail.");
    }
    else
    {
        _isInitialized = true;
    }
}

void TcpServer::Bind(const unsigned short port)
{
    if (!_isInitialized)
    {
        _isBound = false;
        throw GetException("Initialize first before bind.");
    }
    SOCKADDR_IN address = {};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htons(ADDR_ANY);
    address.sin_port = htons(port);
    const int result = bind(_listenSocket, (SOCKADDR*)&address, sizeof(address));
    if (result == 0)
    {
        _isBound = true;
    }
    else
    {
        _isBound = false;
        throw GetException("Bind fail.");
    }
}

void TcpServer::Listen(const int backlog)
{
    if (!_isBound)
    {
        _isListened = false;
        throw GetException("Bind socket first before listen.");
    }
    const int result = listen(_listenSocket, backlog);
    if (result == 0)
    {
        _isListened = true;
    }
    else
    {
        _isListened = false;
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

void TcpServer::Start()
{
    _isAccepting = true;
    const ThreadEx* thread = new ThreadEx(AcceptThread);
    thread->Run(this);
}

void TcpServer::Stop()
{
    _isAccepting = false;
}


unsigned TcpServer::AcceptThread(void* args)
{
    TcpServer* server = (TcpServer*)args;
    while (server->_isAccepting)
    {
        Socket* socket = server->Accept();
        socket->StartReceive();
    }
    return 0;
}

