#pragma once
#ifndef __MYSQL_H__
#define __MYSQL_H__

#include <jdbc/cppconn/sqlstring.h>

namespace sql
{
    class PreparedStatement;
}

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
    MySql();
    MySql(const MySql& ref);
    MySql& operator=(const MySql& ref);
    ~MySql();

public:
    static MySql& GetInstance()
    {
        static MySql mySql;
        return mySql;
    }
    
    void Connect(const sql::SQLString& hostName, const sql::SQLString& userName, const sql::SQLString& password);

    void SetSchema(const sql::SQLString& catalog);

    void InitializeStatements();

    User FindUser(const sql::SQLString& id) const;

    void CreateAccount(const User& user) const;

protected:
    static std::exception GetException(const char* message);

    void CreateStatement();

    void CreateFindUserStatement();

    void CreateCreateAccountStatement();

private:
    sql::Driver* _driver;
    sql::Connection* _connection;
    sql::Statement* _statement;
    sql::PreparedStatement* _findUserPreparedStatement;
    sql::PreparedStatement* _createAccountPreparedStatement;

    bool _isConnected;
    bool _isSetSchema;
    bool _isCreatedStatement;
};
#endif
