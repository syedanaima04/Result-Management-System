#ifndef ENROLLMENTNODE_H
#define ENROLLMENTNODE_H

#include <string>
using namespace std;

// One non-empty cell in the student-course sparse matrix.
class EnrollmentNode
{
public:
    int registrationID;
    int courseID;
    float marks;
    string grade;
    bool marksEntered;
    EnrollmentNode* right; // Next course for the same student.
    EnrollmentNode* down;  // Next student for the same course.

    EnrollmentNode(int studentID, int cID, float studentMarks)
    {
        registrationID = studentID;
        courseID = cID;
        marks = studentMarks;
        grade = "Not graded";
        marksEntered = false;
        right = NULL;
        down = NULL;
    }
};

#endif
