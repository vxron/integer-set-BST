#include "BSTSet.h"
#include <iostream>
#include <vector>
using namespace std;

// stack class uses vector (abusing vector properties<3)
using MyStack=std::vector<TNode*>;

// empty constructor (default), setting root to NULL
BSTSet::BSTSet():root(NULL){}

BSTSet::BSTSet(const std::vector<int>& input)
{
	// error handling
	if(input.empty()){
		return;
	}

	// Initialise root node
	root = new TNode(input[0],NULL,NULL);

	// loop through vector and add elements to tree
	for(unsigned i=1;i<input.size();i++){
		// temporary pointer to iterate through nodes
		// starts at root for each new element
		TNode* T = root;
		TNode* prev = NULL; // keep reference to previous node

		// keeps moving through nodes until we find empty node (leaf), then break but keep reference to last (deepest) node prev
		while(T!=NULL){
			if(input[i]>T->element){
				prev=T; // update previous reference
				// bigger means -> right
				T=T->right;
			}
			else if(input[i]<T->element){
				prev=T; // update previous reference
				// smaller means -> left
				T=T->left;
			}
			else{
				// duplicate - don't insert anything and start at next iteration
				// just update prev to be T (handles everything the same way as if we were inserting)
				prev=T;
				break;
			}
		}
		// when you break, T is NULL (jus. nothing) and prev contains reference to wherever you need to insert
		// need one more check
		if(input[i]>prev->element){
			prev->right=new TNode(input[i],NULL,NULL);
		}
		else if(input[i]<prev->element){
			prev->left=new TNode(input[i],NULL,NULL);
		}
	}

}

// recursion!! yay!! (see added function in TNode.h)
BSTSet::~BSTSet()
{
	delete root;
}

bool BSTSet::isIn(int v)
{
	// set temporary pointer to iterate through nodes
	TNode* T = root;
	while(true){
		if(T==NULL){
			return false;
		}
		else if(T->element==v){
			return true;
		}
		else if(v>T->element){
			// move right
			T=T->right;
		}
		else if(v<T->element){
			// move left
			T=T->left;
		}
	}
    return true;
}

void BSTSet::add(int v)
{
	// first handle adding to an empty set; check if root is NULL
	if(root==NULL){
		root = new TNode(v,NULL,NULL);
		return;
	}

	// keep going through tree until you find empty space to put it
	// temporary pointer to iterate through nodes
	// starts at root for each new element
	TNode* T = root;
	TNode* prev = NULL; // keep reference to previous node

	// keeps moving through nodes until we find empty node (leaf), then break but keep reference to last (deepest) node prev
	while(T!=NULL){
		if(v>T->element){
			prev=T; // update previous reference
			// bigger means -> right
			T=T->right;
		}
		else if(v<T->element){
			prev=T; // update previous reference
			// smaller means -> left
			T=T->left;
		}
		else{
			// duplicate - don't insert anything and start at next iteration
			// just update prev to be T (handles everything the same way as if we were inserting)
			prev=T;
			break;
		}
	}
	// when you break, T is NULL (jus. nothing) and prev contains reference to wherever you need to insert
	// need one more check
	if(v>prev->element){
		prev->right=new TNode(v,NULL,NULL);
	}
	else if(v<prev->element){
		prev->left=new TNode(v,NULL,NULL);
	}
}

// checks if it's there, then removes it
// use recursion hbb
bool BSTSet::remove(int v)
{

	// if it's not there
	if(isIn(v)==false){
		return false;
	}

	// first need to find location of node
	// set temporary pointer to iterate through nodes
	TNode* T = root;
	// also keep reference to previous node for removal purposes
	TNode* prev;
	while(T!=NULL){
		if(T->element==v){
			break;
		}
		else if(v>T->element){
			// move right
			prev=T;
			T=T->right;
		}
		else if(v<T->element){
			// move left
			prev=T;
			T=T->left;
		}
	}

	// when we break, T is the node which we are trying to remove
	// we also kept a reference to the previous node, prev

	/*
	while(true){
		// case I: leaf node
		if(T->left==NULL && T->right==NULL){
			// this is just a leaf node that we can remove
			delete T;
			break;
		}

		// case II: node w 1 child on RIGHT
		else if(T->left==NULL && T->right!=NULL){
			// connect child to "grandparent" --> new parent
			if(T->right->element>prev->element){
				// parent is smaller than child
				prev->left=T->right;
			}
			else{
				// parent is larger than child
				prev->right=T->right;
			}
			// then delete T
			delete T;
			break;
		}

		// 1 child on LEFT
		else if(T->left!=NULL && T->right==NULL){
			// connect child to "grandparent" --> new parent
			if(T->left->element>prev->element){
				// parent is smaller than child
				prev->left=T->left;
			}
			else{
				// parent is larger than child
				prev->right=T->left;
			}
			// then delete T
			delete T;
			break;
		}

		// case III: node w 2 children
	}
	*/

	return true;
}

// REPEATED ADD (+remove maybe)
void BSTSet::Union(const BSTSet& s)
{
	// insert everything from one into the other
	// could use recursion
	// maybe just use list -> use some type of traversal
}

// repeated add + remove
void BSTSet::intersection(const BSTSet& s)
{
	// convert tree into list and do intersection on lists
}

void BSTSet::difference(const BSTSet& s)
{
	// remove everything in A that's also in B
	// do lists again
}

// traverse in order (left -> middle -> right)
int BSTSet::size()
{
	int size=0;
	// size is number of nodes
	TNode* T = root;
	size++;

	if(T==NULL){
		// empty tree
		return 0;
	}

	// count elements on LEFT SUBTREE RECURSIVELY
	// if it's null, it skips over and we still have size=1 from root above
	while(T->left!=NULL){
		T=T->left;
		size++;
	}

	// reset T to root

	// count elements on RIGHT SUBTREE RECURSIVELY
	while(T!=NULL){

	}



    return size;
}

int BSTSet::height()
{
	// height is length of longest path (counting branches) from root to leaf
	// height starts at 0 (height at root is 0)
    return -2; //change this after completing this function
}

// create and use class MyStack
void BSTSet::printNonRec()
{
	// TODO
	cout << "-2"; //change this after completing this function
}

// Do not modify following provided methods

/*
	MyStack stack; // holds all the nodes that come before the node you're currently at

	// do a post order traversal using stack class (vector), then delete nodes sequentially
	// dont want to delete root --> need to keep that reference till the end!
	// push root first, so that we can pop it last
	stack.push_back(root);
	TNode* T = root;
	TNode* n = NULL;

	while(T!=NULL || !stack.empty()){
		if(T!=NULL){
			stack.push_back(T);
			T=T->left;
		}
		else{
			// assign top of stack to topmost
			TNode* topmost = stack.back();
			// check if topmost right is not null
			if(topmost->right!=NULL && n!=topmost->right){
				T=topmost->right;
			}
			else{
				delete topmost;
			}
		}

	}
	*/

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
