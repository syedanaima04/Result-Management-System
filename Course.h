#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

// Stores information about one course.
class Course
{
private:
    int courseID;
    string courseName;
    int creditHours;

public:
    Course();
    Course(int id, string name, int credits);

    int getCourseID() const;
    string getCourseName() const;
    int getCreditHours() const;

    void displayDetails() const;
};

#endif
