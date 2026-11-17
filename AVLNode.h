#pragma once
#ifndef AVLNODE_H
#define AVLNODE_H

#include "../Student/Student.h"

// Each AVL node stores one Student and links to its left and right children.
class AVLNode
{
public:
    Student data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Student student)
    {
        data = student;
        left = NULL;
        right = NULL;
        height = 1; // A newly created leaf aways has height 1.
    }
};

#endif
