#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

#include <iostream>

sql::mysql::MySQL_Driver *driver;
sql::Connection *con; //to establish connection
sql::Statement *stmt; //to execute SQL statement
driver = sql::mysql::get_mysql_driver_instance();
con = driver->connect("mysql.eecs.ku.edu", "348s25_d020c696", "aek4Thai");
stmt = con->createStatement();
//your MySQL database is named the same as your username
stmt->execute("USE" 348s25_d020c696);

stmt->execute("SELECT StdFirstName, StdLastName FROM Student WHERE Student.StdMajor = "IS"");


delete stmt;
delete con;
delete con;