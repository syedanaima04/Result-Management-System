#ifndef STUDENTHEADER_H
#define STUDENTHEADER_H

#include "EnrollmentNode.h"

// Row header: points to all courses taken by one student.
class StudentHeader
{
public:
    int registrationID;
    EnrollmentNode* first;
    StudentHeader* next;

    StudentHeader(int id)
    {
        registrationID = id;
        first = NULL;
        next = NULL;
    }
};

#endif
