#include "BSTSet.h"
#include <iostream>
#include <vector>
using namespace std;

BSTSet::BSTSet()
{
	// TODO
}

BSTSet::BSTSet(const std::vector<int>& input)
{
	// TODO, change following code after completing this function
	root = new TNode(-1, NULL, NULL);
}

BSTSet::~BSTSet()
{
	// TODO
}

bool BSTSet::isIn(int v)
{
	// TODO
    return false; //change this after completing this function
}

void BSTSet::add(int v)
{
	// TODO
}

bool BSTSet::remove(int v)
{
	// TODO
    return true; //change this after completing this function
}

void BSTSet::Union(const BSTSet& s)
{
	// TODO
}

void BSTSet::intersection(const BSTSet& s)
{
	// TODO
}

void BSTSet::difference(const BSTSet& s)
{
	// TODO
}

int BSTSet::size()
{
	// TODO
    return -1; //change this after completing this function
}

int BSTSet::height()
{
	// TODO
    return -2; //change this after completing this function
}

// create and use class MyStack
void BSTSet::printNonRec()
{
	// TODO
	cout << "-2"; //change this after completing this function
}

// Do not modify following provided methods

void BSTSet::printBSTSet()
{
    if (root == NULL)
        std::cout << "";
    else {
        printBSTSet(root);
    }
}

void BSTSet::printBSTSet(TNode* t)
{
    if (t != NULL) {
        printBSTSet(t->left);
        std::cout << t->element << ",";
        printBSTSet(t->right);
    }
}
