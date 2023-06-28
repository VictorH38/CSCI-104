#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int getHeight(Node* root) {
    int counter;
    if (root == nullptr) {
        return 0;
    }
    else {
        counter = 1;
    }

    Node* leftNode = root->left;
    Node* rightNode = root->right;

    int leftHeight = getHeight(leftNode);
    int rightHeight = getHeight(rightNode);

    if (leftHeight >= rightHeight) {
        counter += leftHeight;
    }
    else {
        counter += rightHeight;
    }

    return counter;
}

bool equalPaths(Node * root)
{
    // Add your code below
    if (root == nullptr) {
        return true;
    }

    Node* leftNode = root->left;
	Node* rightNode = root->right;

    if (leftNode && rightNode) {
        return getHeight(leftNode) == getHeight(rightNode);
    }
    else if (leftNode) {
        return equalPaths(leftNode);
    }
    else if (rightNode) {
        return equalPaths(rightNode);
    }
    else {
        return true;
    }
}
