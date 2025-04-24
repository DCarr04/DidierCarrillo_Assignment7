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

stmt->execute("SELECT s.StdFirstName, s.StdLastName FROM Student s
JOIN (
    SELECT StdNo, COUNT(DISTINCT OfferNo) AS course_count
    FROM Enrollment
    GROUP BY StdNo
    HAVING COUNT(DISTINCT OfferNo) > 2
) e ON s.StdNo = e.StdNo");

stmt->execute("SELECT FacFirstName, FacLastName FROM Faculty WHERE Faculty.FacDept = "PHY";")


delete stmt;
delete con;
delete con;