#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include "StudentHeader.h"
#include "CourseHeader.h"
class SparseMatrix {
private:
    StudentHeader* studentHead; CourseHeader* courseHead;
    StudentHeader* getStudentHeader(int studentID); CourseHeader* getCourseHeader(int courseID);
    void createStudentHeader(int studentID); void createCourseHeader(int courseID);
public:
    SparseMatrix(); ~SparseMatrix();
    bool addEnrollment(int studentID,int courseID); bool updateMarks(int studentID,int courseID,float marks);
    bool removeStudentEnrollments(int studentID); bool removeCourseEnrollments(int courseID);
    EnrollmentNode* findEnrollment(int studentID,int courseID);
    EnrollmentNode* getStudentEnrollments(int studentID); EnrollmentNode* getCourseEnrollments(int courseID);
    void displayStudentEnrollments(int studentID); void displayCourseEnrollments(int courseID);
};
#endif
