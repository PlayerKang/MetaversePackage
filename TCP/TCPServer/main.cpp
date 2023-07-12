#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

//---C
#include <WinSock2.h>
//---C++
#include <iostream>
#include <string.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/prepared_statement.h>
//---Plugin Library
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "vs14/mysqlcppconn.lib")

using namespace std;

const string DBIP = "127.0.0.1:3306";					//MySQL IP
const string DBID = "root";								//MySQL ID
const string DBPass = "393939ok";							//MySQL Pass
sql::Driver* DB_Driver = nullptr;							//MySQL 드라이버
sql::Connection* DB_Connection = nullptr;					//MySQL 데이터베이스 연결
sql::Statement* DB_Statement = nullptr;						//MySQL 데이터베이스에 대한 SQL 을 실행하는데 사용
sql::PreparedStatement* DB_PreparedStatement = nullptr;		//MySQL 데이터베이스에 미리 컴파일된 SQL 을 실행하는데 사용
sql::ResultSet* DB_ResultSet = nullptr;						//MySQL 데이터베이스에서 반환된 결과 집합
