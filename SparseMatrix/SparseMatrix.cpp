#include "SparseMatrix.h"
#include <iostream>
using namespace std;

SparseMatrix::SparseMatrix()
{
    studentHead = NULL;
    courseHead = NULL;
}

SparseMatrix::~SparseMatrix()
{
    // Delete every enrollment exactly once by traversing student rows.
    StudentHeader* student = studentHead;
    while (student != NULL)
    {
        EnrollmentNode* node = student->first;
        while (node != NULL)
        {
            EnrollmentNode* temp = node;
            node = node->right;
            delete temp;
        }

        StudentHeader* tempStudent = student;
        student = student->next;
        delete tempStudent;
    }

    CourseHeader* course = courseHead;
    while (course != NULL)
    {
        CourseHeader* tempCourse = course;
        course = course->next;
        delete tempCourse;
    }
}

StudentHeader* SparseMatrix::getStudentHeader(int id)
{
    StudentHeader* current = studentHead;
    while (current != NULL)
    {
        if (current->registrationID == id)
            return current;
        current = current->next;
    }
    return NULL;
}

CourseHeader* SparseMatrix::getCourseHeader(int id)
{
    CourseHeader* current = courseHead;
    while (current != NULL)
    {
        if (current->courseID == id)
            return current;
        current = current->next;
    }
    return NULL;
}

void SparseMatrix::createStudentHeader(int id)
{
    if (getStudentHeader(id) != NULL)
        return;

    StudentHeader* newHeader = new StudentHeader(id);
    newHeader->next = studentHead;
    studentHead = newHeader;
}

void SparseMatrix::createCourseHeader(int id)
{
    if (getCourseHeader(id) != NULL)
        return;

    CourseHeader* newHeader = new CourseHeader(id);
    newHeader->next = courseHead;
    courseHead = newHeader;
}

EnrollmentNode* SparseMatrix::findEnrollment(int studentID, int courseID)
{
    StudentHeader* row = getStudentHeader(studentID);
    if (row == NULL)
        return NULL;

    EnrollmentNode* current = row->first;
    while (current != NULL)
    {
        if (current->courseID == courseID)
            return current;
        current = current->right;
    }
    return NULL;
}

bool SparseMatrix::addEnrollment(int studentID, int courseID)
{
    if (findEnrollment(studentID, courseID) != NULL)
        return false;

    createStudentHeader(studentID);
    createCourseHeader(courseID);

    EnrollmentNode* newNode = new EnrollmentNode(studentID, courseID, 0);

    // Add this cell to the student's row.
    StudentHeader* row = getStudentHeader(studentID);
    newNode->right = row->first;
    row->first = newNode;

    // Add the same cell to the course's column.
    CourseHeader* column = getCourseHeader(courseID);
    newNode->down = column->first;
    column->first = newNode;

    return true;
}

bool SparseMatrix::updateMarks(int studentID, int courseID, float marks)
{
    if (marks < 0 || marks > 100)
        return false;

    EnrollmentNode* node = findEnrollment(studentID, courseID);
    if (node == NULL)
        return false;

    node->marks = marks;
    node->marksEntered = true;

    // Convert marks into a simple letter grade.
    if (marks >= 85) node->grade = "A";
    else if (marks >= 80) node->grade = "A-";
    else if (marks >= 75) node->grade = "B+";
    else if (marks >= 70) node->grade = "B";
    else if (marks >= 65) node->grade = "B-";
    else if (marks >= 60) node->grade = "C";
    else if (marks >= 50) node->grade = "D";
    else node->grade = "F";

    return true;
}



// Remove one student's row and unlink each shared cell from its course column.
bool SparseMatrix::removeStudentEnrollments(int studentID)
{
    StudentHeader* row = studentHead;
    StudentHeader* previousRow = NULL;

    while (row != NULL && row->registrationID != studentID)
    {
        previousRow = row;
        row = row->next;
    }

    if (row == NULL)
        return false;

    EnrollmentNode* current = row->first;

    while (current != NULL)
    {
        EnrollmentNode* nextInRow = current->right;
        CourseHeader* column = getCourseHeader(current->courseID);

        if (column != NULL)
        {
            EnrollmentNode* cell = column->first;
            EnrollmentNode* previousCell = NULL;

            while (cell != NULL && cell != current)
            {
                previousCell = cell;
                cell = cell->down;
            }

            if (cell != NULL)
            {
                if (previousCell == NULL)
                    column->first = cell->down;
                else
                    previousCell->down = cell->down;
            }
        }

        delete current;
        current = nextInRow;
    }

    if (previousRow == NULL)
        studentHead = row->next;
    else
        previousRow->next = row->next;

    delete row;
    return true;
}

// Remove one course column and unlink each shared cell from its student row.
bool SparseMatrix::removeCourseEnrollments(int courseID)
{
    CourseHeader* column = courseHead;
    CourseHeader* previousColumn = NULL;

    while (column != NULL && column->courseID != courseID)
    {
        previousColumn = column;
        column = column->next;
    }

    if (column == NULL)
        return false;

    EnrollmentNode* current = column->first;

    while (current != NULL)
    {
        EnrollmentNode* nextInColumn = current->down;
        StudentHeader* row = getStudentHeader(current->registrationID);

        if (row != NULL)
        {
            EnrollmentNode* cell = row->first;
            EnrollmentNode* previousCell = NULL;

            while (cell != NULL && cell != current)
            {
                previousCell = cell;
                cell = cell->right;
            }

            if (cell != NULL)
            {
                if (previousCell == NULL)
                    row->first = cell->right;
                else
                    previousCell->right = cell->right;
            }
        }

        delete current;
        current = nextInColumn;
    }

    if (previousColumn == NULL)
        courseHead = column->next;
    else
        previousColumn->next = column->next;

    delete column;
    return true;
}

EnrollmentNode* SparseMatrix::getStudentEnrollments(int studentID)
{
    StudentHeader* row = getStudentHeader(studentID);
    if (row == NULL)
        return NULL;
    return row->first;
}

EnrollmentNode* SparseMatrix::getCourseEnrollments(int courseID)
{
    CourseHeader* column = getCourseHeader(courseID);
    if (column == NULL)
        return NULL;
    return column->first;
}

void SparseMatrix::displayStudentEnrollments(int studentID)
{
    EnrollmentNode* current = getStudentEnrollments(studentID);

    if (current == NULL)
    {
        cout << "This student has no course enrollments.\n";
        return;
    }

    cout << "Course ID\tMarks\tGrade\n";
    while (current != NULL)
    {
        cout << current->courseID << "\t\t" << current->marks
             << "\t" << current->grade << endl;
        current = current->right;
    }
}

void SparseMatrix::displayCourseEnrollments(int courseID)
{
    EnrollmentNode* current = getCourseEnrollments(courseID);

    if (current == NULL)
    {
        cout << "No students are enrolled in this course.\n";
        return;
    }

    cout << "Registration ID\tMarks\tGrade\n";
    while (current != NULL)
    {
        cout << current->registrationID << "\t\t"
             << current->marks << "\t" << current->grade << endl;
        current = current->down;
    }
}
