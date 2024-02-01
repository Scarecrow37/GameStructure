#pragma once
#ifndef __MYSQL_H__
#define __MYSQL_H__

#include <jdbc/cppconn/sqlstring.h>

struct User;

namespace std
{
    class exception;
}

namespace sql
{
    class Driver;
    class Connection;
    class Statement;
}


class MySql
{
public:
    MySql();

    void Connect(const sql::SQLString& hostName, const sql::SQLString& userName, const sql::SQLString& password);

    void SetSchema(const sql::SQLString& catalog);

    void CreateStatement();

    User FindUser(const sql::SQLString& id) const;

protected:
    static std::exception GetException(const char* message);

private:
    sql::Driver* _driver;
    sql::Connection* _connection;
    sql::Statement* _statement;

    bool _isConnected;
    bool _isSetSchema;
    bool _isCreatedStatement;
};
#endif
