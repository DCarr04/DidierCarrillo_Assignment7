#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <libmysqlcppconn.lib>

#include <iostream> //to use output and input

sql::mysql::MySQL_Driver *driver; //MySQL_Driver which provides an interface
sql::Connection *con; //to establish connection
sql::Statement *stmt; //to execute SQL statement
sql::ResultSet *res; //to store the results of the executeQuery statements
driver = sql::mysql::get_mysql_driver_instance(); //sets druver to instance of driver to get connection
con = driver->connect("mysql.eecs.ku.edu", "348s25_d020c696", "aek4Thai"); //to connect driver pointer to database on the cycle servers
stmt = con->createStatement(); //to connect stmt to database and send commands
stmt->execute("USE" 348s25_d020c696); //"USE" command to access my database which is named like my username

stmt->execute("SELECT StdFirstName, StdLastName \
    FROM Student \
    WHERE Student.StdMajor = "IS";");

//
stmt->execute("SELECT s.StdFirstName, s.StdLastName \
    FROM Student s \
    JOIN ( \
        SELECT StdNo, \
        COUNT(DISTINCT OfferNo) AS course_count \
        FROM Enrollment \
        GROUP BY StdNo \
        HAVING COUNT(DISTINCT OfferNo) > 2) e ON s.StdNo = e.StdNo;");

//
stmt->execute("SELECT s.StdMajor AS Department, \
    COUNT(DISTINCT e.StdNo) AS TotalStudents \
    FROM Enrollment e \
    JOIN Student s ON e.StdNo = s.StdNo \
    GROUP BY s.StdMajor \
    HAVING COUNT(DISTINCT e.StdNo) > 50;");
//
stmt->execute("SELECT count(FacHireDate), FacDept \
    FROM Faculty \
    WHERE FacDept = "PHY" \
    HAVING COUNT(2019-08-26 - FacHireDate) > 5;");

//
stmt->execute("SELECT c.CourseNo, c.CrsDesc AS CourseName \
    FROM Course c \
    JOIN Offering o ON c.CourseNo = o.CourseNo \
    JOIN Faculty f ON o.FacNo = f.FacNo \
    WHERE c.CrsDesc LIKE '%Data%' AND f.FacLastName = 'Johnson';")
//
stmt->execute("SELECT s.StdFirstName, s.StdLastName \
    FROM Student s \
    WHERE s.StdNo NOT IN ( \
        SELECT DISTINCT e.StdNo \
        FROM Enrollment e \
        JOIN Offering o ON e.OfferNo = o.OfferNo \
        WHERE (o.OffYear = 2020 AND o.OffTerm IN ('SPRING', 'SUMMER')) -- Most recent two semesters in sample data \
    );");
//
int a = 0;
res = stmt->executeQuery("SELECT stdGPA FROM Student ORDER BY stdGPA DESC;");
while(res->next()){
    if(a == 1){
        std::cout << res->getString("stdGPA") << std::endl;
    }
    a++;
};

//
stmt->execute("SELECT s.StdFirstName, s.StdLastName \
    FROM Student s \
    JOIN Faculty f ON s.StdNo = f.FacNo \
    WHERE s.StdGPA > 3.5;");
//
stmt->execute("");
//
res = stmt->executeQuery("SELECT FacFirstName, FacLastName, FacSalary FROM Faculty ORDER BY FacSalary DESC;");
for(int i = 0; i < 3; i++){
    std::cout << res->getString("FacFirstName") << res->getString("FacLastName") << res->getString("FacSalary") << std::endl;
};
delete res;
delete stmt;
delete con;
delete con;