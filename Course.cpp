#include "Course.h"
#include <iostream>
using namespace std;

Course::Course()
{
    courseID = 0;
    courseName = "";
    creditHours = 3;
}

Course::Course(int id, string name, int credits)
{
    courseID = id;
    courseName = name;
    creditHours = credits;
}

int Course::getCourseID() const { return courseID; }
string Course::getCourseName() const { return courseName; }
int Course::getCreditHours() const { return creditHours; }

void Course::displayDetails() const
{
    cout << "Course ID: " << courseID << endl;
    cout << "Course Name: " << courseName << endl;
    cout << "Credit Hours: " << creditHours << endl;
}
