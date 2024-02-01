#pragma once
#ifndef __MYSQL_H__
#define __MYSQL_H__

#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/connection.h>


class MySql
{
public:
    MySql();

    void Connect(const char* hostName, const char* userName, const char* password);

protected:
    static std::exception GetException(const char* message);

private:
    sql::Driver* _driver;
    sql::Connection* _connection;

    bool _connected;
};
#endif
