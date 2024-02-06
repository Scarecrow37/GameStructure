#pragma once
#ifndef __HEADER_H__
#define __HEADER_H__

enum PacketType : unsigned short
{
    RequestLogin = 10,
    ResponseLogin = 20,
    Max
};

#pragma pack(push, 1)
struct Header
{
    unsigned short Size;
    PacketType Type;
};

struct RequestLoginData
{
    char Id[20];
    char Password[20];
};

struct ResponseLoginData
{
    bool IsSuccess;
    char Nickname[20];
};
#pragma pack(pop)

#endif