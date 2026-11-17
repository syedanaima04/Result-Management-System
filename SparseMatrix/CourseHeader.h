#ifndef COURSEHEADER_H
#define COURSEHEADER_H

#include "EnrollmentNode.h"

// Column header: points to all students enrolled in one course.
class CourseHeader
{
public:
    int courseID;
    EnrollmentNode* first;
    CourseHeader* next;

    CourseHeader(int id)
    {
        courseID = id;
        first = NULL;
        next = NULL;
    }
};

#endif
