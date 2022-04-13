#include "BSTSet.h"
#include <iostream>
#include <vector>
#include <math.h>
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

bool BSTSet::isIn(int v)const
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

TNode* BSTSet::find_min(TNode* T){
	// min is leftmost element
	int min;
	//TNode* T = root;
	TNode* prev;
	while(T!=NULL){
		// save ref to prev node before loop hits NULL
		prev=T;
		T=T->left;
	}

	return prev;
}

int BSTSet::find_max(TNode* T){
	// max is rightmost element
	int max;
	//TNode* T = root;

	while(T!=NULL){
		max=T->element;
		T=T->right;
	}

	return max;
}

// checks if it's there, then removes it
// use recursion hbb
bool BSTSet::remove(int v)
{

	/*
	// if it's not there
	if(isIn(v)==false){
		return false;
	}
	*/

	//printBSTSet();
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

	if(T==NULL){
		return false; //element isnt there when you break out
	}
	// when we break, T is the node which we are trying to remove
	// we also kept a reference to the previous node, prev



	// case I: leaf node
	if(T->left==NULL && T->right==NULL){

		//printBSTSet();

		// special case where we only have 1 node, root
		if(T==root){
			root=NULL;
			return true;
		}

		// fix link from prev
		if(prev->left==T){
			prev->left=NULL;
		}
		else{
			prev->right=NULL;
		}

		T->left=NULL;
		T->right=NULL;
		// this is just a leaf node that we can remove
		delete T;
	}

	// case II: node w 2 children
	else if(T->left!=NULL && T->right!=NULL){

		// get minimum on right node, tmp
		TNode* tmp=T->right;
		TNode* parent=T;
		while(tmp->left!=NULL){
			// get parent node
			parent=tmp;
			tmp=tmp->left;
		}
		// set T element to minimum on right
		T->element=tmp->element;

		/*
		if(T==parent){
			parent->right=tmp->right;
		}
		*/
		/*
		else{
			parent->left=tmp->right;
		}
		*/

		tmp->left=NULL;
		tmp->right=NULL;
		delete tmp;

		/*
		// give node w min on right (that we want to delete) a new value of -1
		find_min(T->right)->element=500;

		// remove this node
		remove(500);
		*/
	}

	// case III: node w 1 child on RIGHT
	else{

		if(T==root){
			if(T->left!=NULL){
				// there's a left element
				root=T->left;
			}
			else{
				// there's a right element
				root=T->right;
			}
		}

		else if(T->left!=NULL){
			// there's a left element (child)
			if(prev->right==T){
				// T is to the right of previous, so child must be to the right of previous
				prev->right=T->left;
			}
			else{
				prev->left=T->left;
			}
		}

		else{
			// there's a right element (child)
			if(prev->right==T){
				// T is to the right of previous, so child must be to the right of prev
				prev->right=T->right;
			}
			else{
				prev->left=T->right;
			}
		}

		// always set T left and right to NULL (so it doesn't have refs to anything)
		T->left=NULL;
		T->right=NULL;
		delete T;
	}

		/*
		// connect child to "grandparent" --> new parent
		if(T->right->element>prev->element){
			// parent is smaller than child
			prev->right=T->right;
		}
		else{
			// parent is larger than child
			prev->left=T->right;
		}
		// then delete T
		delete T;
	}
	*/

	/*
	// 1 child on LEFT
	else if(T->left!=NULL && T->right==NULL){
		// connect child to "grandparent" --> new parent
		if(T->left->element>prev->element){
			// parent is smaller than child (child is to right of parent)
			prev->right=T->left;
		}
		else{
			// parent is larger than child (child is to left of parent)
			prev->left=T->left;
		}
		// then delete T
		delete T;
	}
	*/

	return true;
}

// REPEATED ADD
void BSTSet::Union(const BSTSet& s)
{
	// add to yourself
	MyStack stack; // holds all the nodes that come before the node you're currently at

	TNode* T = s.root;
	// push root into stack
	//stack.push_back(T);

	// if T is NULL, we've reached the end of a subtree, but if there's something in the stack, we still have anotha one to traverse
	// if stack is empty but T is not NULL, we still have things to traverse in the given subtree
	// (why we use an OR statement)
	while(T!=NULL || !stack.empty()){
		while(T!=NULL){
			stack.push_back(T);
			T=T->left;
		}

		// T must be null at this point, meaning we take from stack
		T = stack.back();
		stack.pop_back();
		add(T->element);

		// traverse right tree
		T=T->right;

	}

	// insert everything from one into the other


	// could use recursion
	// maybe just use list -> use some type of traversal
}

// repeated add + remove
void BSTSet::intersection(const BSTSet& s)
{
	MyStack stack;

	BSTSet tmp;
	// iterate through YOUR stuff and for each thing, see if it exists in s
	// add to temporary tree

	TNode* T = root;

	while(T!=NULL || !stack.empty()){
		while(T!=NULL){
			stack.push_back(T);
			T=T->left;
		}

		// T must be null at this point, meaning we take from stack
		T = stack.back();
		stack.pop_back();
		if(s.isIn(T->element)==true){
			tmp.add(T->element);
		}

		// traverse right tree
		T=T->right;

	}

	// remove all elements that dont have a counterpart in the other and vice versa
	// then union the remaining

	//*this=tmp;
	delete root;
	root=tmp.root;
	tmp.root=NULL;

}

void BSTSet::difference(const BSTSet& s)
{
	// remove everything in A that's also in B
	// do lists again
	MyStack stack;

	BSTSet tmp;
		// iterate through YOUR stuff and for each thing, see if it exists in s
		// add to temporary tree

	TNode* T = root;

	/*
	while(T!=NULL || !stack.empty()){
		while(T!=NULL){
			stack.push_back(T);
			T=T->left;
		}

		// T must be null at this point, meaning we take from stack
		T = stack.back();
		stack.pop_back();
		if(s.isIn(T->element)==true){
			// REMOVE
			tmp.remove(T->element);
		}

		// traverse right tree
		T=T->right;

	}

	// remove all elements that dont have a counterpart in the other and vice versa
	// then union the remaining

	//*this=tmp;
	delete root;
	root=tmp.root;
	tmp.root=NULL;
	*/

}

// traverse in order (left -> middle -> right)
int BSTSet::size()
{
	int size=0;
	// size is number of nodes

	TNode* T = root;
	//size++;

	if(T==NULL){
		// empty tree
		return 0;
	}


	MyStack stack; // holds all the nodes that come before the node you're currently at

	// push root into stack
	//stack.push_back(T);

	// if T is NULL, we've reached the end of a subtree, but if there's something in the stack, we still have anotha one to traverse
	// if stack is empty but T is not NULL, we still have things to traverse in the given subtree
	// (why we use an OR statement)
	while(T!=NULL || !stack.empty()){
		while(T!=NULL){
			stack.push_back(T);
			T=T->left;
		}

		// T must be null at this point, meaning we take from stack
		T = stack.back();
		stack.pop_back();
		size++;

		// traverse right tree
		T=T->right;

	}
	// count elements on LEFT SUBTREE RECURSIVELY
	// if it's null, it skips over and we still have size=1 from root above

	// reset T to root

	// count elements on RIGHT SUBTREE RECURSIVELY

    return size;
}

int getHeight(TNode* T){
	if(T==NULL){
		return 0;
	}
	else{
		return 1+max(getHeight(T->left),getHeight(T->right));
	}
}

int BSTSet::height()
{
	// height is length of longest path (counting branches) from root to leaf
	// height starts at 0 (height at root is 0)

	return getHeight(root)-1;

}



// create and use class MyStack, in order traversal
void BSTSet::printNonRec()
{
	MyStack stack; // holds all the nodes that come before the node you're currently at

	// do nothing if root is NULL
	if(root==NULL){return;};

	// start with root, bas this will increment
	TNode* T = root;

	// push root into stack
	//stack.push_back(T);

	// if T is NULL, we've reached the end of a subtree, but if there's something in the stack, we still have anotha one to traverse
	// if stack is empty but T is not NULL, we still have things to traverse in the given subtree
	// (why we use an OR statement)
	while(T!=NULL || !stack.empty()){
		while(T!=NULL){
			stack.push_back(T);
			T=T->left;
		}

		// T must be null at this point, meaning we take from stack
		T = stack.back();
		stack.pop_back();
		cout << T->element << ",";

		// traverse right tree
		T=T->right;

	}

	// if (root->left) is there (i.e. any node has a left element), push root onto stack and move to root->left

	// if root->left is NULL, print root->element and pop from stack, move towards right root->right

	// stop if stack is empty (no more root to look at)
}

// Do not modify following provided methods

/*


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
