#pragma once
#include <string>

#include "Packet.h"

class PacketManager
{
public:
    static Header BytesToHeader(const char* bytes);
    static RequestLoginData BytesToRequestLoginData(const char* bytes);
    static RequestCreateAccountData BytesToRequestCreateAccountData(const char* bytes);

private:
    static char* BytesToChar(const char* in, int count);
};
