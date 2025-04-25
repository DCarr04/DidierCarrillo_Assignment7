/*
-DidierCarrillo_Assignment7
-Executes SQL queries using database 348s25_d020c696. 
 The database includes tables: Student, Course, Enrollment, Offering, and Faculty.
 Most of the queries are about selecting/displaying elements from the tables above that fit into
 specific parameters. There is an insertion and an update query as well.
-Inputs: 348s25_d020c696 tables: Student, Course, Enrollment, Offering, and Faculty
-Outputs: SQL query results(or nothing if no elements fitting the parameters can be found)
-Collaborators: Dr. David Johnson('RBD Coding(MySQL & C++)' slides), Deepseek AI
-Didier Carrillo
-April 20, 2024
*/
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

//selects students first and last names (attributes StdFirstName and StdLastName)
//from Student table (s)
//where that student's major is "IS"
stmt->execute("SELECT s.StdFirstName, s.StdLastName \
    FROM Student s\
    WHERE s.StdMajor = "IS";");


//selects students first and last names (attributes StdFirstName and StdLastName)
//from Student table (s)
//joins StdNo from Enrollment and Student tables
//selects StdNo
//counts each OfferNo once from the Enrollment table
//Groups the joined table by StdNo 
//where the OfferNo counted was > 2 and Student StdNo equaled the Enrollment StdNo
//This query was Sourced from Deepseek AI; I wasn't sure how to use JOIN
stmt->execute("SELECT s.StdFirstName, s.StdLastName \
    FROM Student s \
    JOIN ( \
        SELECT StdNo, \
        COUNT(DISTINCT OfferNo) \
        FROM Enrollment \
        GROUP BY StdNo \
        HAVING COUNT(DISTINCT OfferNo) > 2) e ON s.StdNo = e.StdNo;");

//selects students' major (attribute StdMajor)
//from Student table (s)
//Counts unique student numbers
//from Enrollment table (e)
//Joins Enrollment table with Student table s on shared column StdNo
//Groups joined table by StdMajor where count of unique StdNo from e is greater than 50
stmt->execute("SELECT s.StdMajor \
    FROM Student s \
    COUNT(DISTINCT e.StdNo) \
    FROM Enrollment e \
    JOIN s ON e.StdNo = s.StdNo \
    GROUP BY s.StdMajor \
    HAVING COUNT(DISTINCT e.StdNo) > 50;");

//selects faculty's first and last names (attributes FacFirstName and FacLastName)
//from Faculty table (f)
//counts the hire dates of the faculty
//where the Faculty department is "PHY" for physics
//groups faculty by their hire date 
//when the difference of 2019 and their hire date(using number infront of '-' and doesn't have anything in front of it) is greater than 5
stmt->execute("SELECT f.FacFirstName, f.FacLastName \
    FROM Faculty f \
    COUNT(f.FacHireDate) \
    WHERE f.FacDept = "PHY" \
    GROUP BY f.FacHireDate \
    HAVING COUNT(2020 - FacHireDate LIKE '%-') > 5;");

//selects course number, course description from Course table c
//joins table c with Offering table o by shared column CourseNo
//joins table o with Faculty table f by shared column FacNo
//where the course description contains the word data and the proffesor last name is 'Johnson'
//This query was sourced from Deepseek AI; I hadn't figured how to layer/do multiple JOIN commands
stmt->execute("SELECT c.CourseNo, c.CrsDesc \
    FROM Course c \
    JOIN Offering o ON c.CourseNo = o.CourseNo \
    JOIN Faculty f ON o.FacNo = f.FacNo \
    WHERE c.CrsDesc LIKE '%Data%' AND f.FacLastName = 'Johnson';")

//selects students' first and last names from Student table s
//where their StdNo is not in the following joined table
//Selects unique StdNo from Enrollment table e
//joins table e with Offering table o by shared column OfferNo
//where the year a course's offered in is 2020 and and the the offered term was in the spring or summer(the last two semesters)
stmt->execute("SELECT s.StdFirstName, s.StdLastName \
    FROM Student s \
    WHERE s.StdNo NOT IN ( \
        SELECT DISTINCT e.StdNo \
        FROM Enrollment e \
        JOIN Offering o ON e.OfferNo = o.OfferNo \
        WHERE (o.OffYear = 2020 AND o.OffTerm IN ('SPRING', 'SUMMER')) \
    );"); //end of NOT IN statement and end of execute

int a = 0; //counter variable initialized as 0
res = stmt->executeQuery("SELECT s.StdGPA FROM Student s ORDER BY s.StdGPA DESC;"); //sql query that selects student's GPA from Student table s and orders the results by the GPAs in descending order
while(res->next()){ //while there is a next line in res
    if(a == 1){ //if a is 1; this is to only get the second highest GPA printed
        std::cout << res->getString("stdGPA") << std::endl; //prints the GPA
    } //end of if statement
    a++; //increments a
}; //end of while loop- I added a semi-colon to the end b/c some pointers below weren't their regular light blue color in VS code

//selects Students' first and last names from Student table s
//joins table s with Faculty table f in the instance that a student number equals a faculty number
//where the student's GPA is greater than 3.5
stmt->execute("SELECT s.StdFirstName, s.StdLastName \
    FROM Student s \
    JOIN Faculty f ON s.StdNo = f.FacNo \
    WHERE s.StdGPA > 3.5;");

//selects students first and last names from Student tables and selects a courses description from Course table c
//joins Student table s with Enrollment table e by shared column StdNo
//joins table e with Offering table o by shared column OfferNo
//joins table o with Course table c by shared column CourseNo
//where a course's offered year is greater than 2022
stmt->execute("SELECT s.StdFirstName, s.StdLastname, c.CrsDesc \
    FROM Student s \
    JOIN Enrollment e ON s.StdNo = e.StdNo \
    JOIN Offering o ON e.OfferNo = o.OfferNo \
    JOIN Course c ON o.CourseNo = c.CourseNo \
    WHERE o.OffYear > 2022;");

//executeQuery result goes in res
//select faculty members first and last names and their salary from Faculty table f
//Orders the selected elements by their salary in descending order
res = stmt->executeQuery("SELECT f.FacFirstName, f.FacLastName, f.FacSalary FROM Faculty f ORDER BY FacSalary DESC;");
for(int i = 0; i < 3; i++){ //for loop will go through the first three lines of res and get the top 3 highest paid faculty and their salaries
    std::cout << res->getString("FacFirstName") << res->getString("FacLastName") << res->getString("FacSalary") << std::endl; //prints faculty member's first and last name and their salary
} //end of for loop

//inserts into Student table
//Alice Smith from Topeka,KS, 66610 who is a JR and a CS major with a GPA of 3.85
stmt->execute("INSERT INTO Student(StdNo, StdFirstName, StdLastName, StdCity, StdState, StdZip, StdClass, StdMajor, StdGPA) VALUES('888-88-8888', 'Alice', 'Smith', 'Topeka', 'KS', '66610', 'JR', 'CS', 3.85);");
stmt->execute("SELECT * FROM Student;"); //displays all information in Student table

//Updates Student table by setting the StdCity to Overland Park and the StdZip to 66204 where a student's last name is Norbert
stmt->execute("UPDATE Student SET StdCity = 'Overland Park', StdZip = '66204' WHERE StdLastName = 'Norbert';");
stmt->execute("SELECT * FROM Student;"); //displays all information in Student table

delete res; //deletes res pointer
delete stmt; //deletes stmt pointer
delete con; //deletes con pointer
