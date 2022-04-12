#ifndef TNODE_H_
#define TNODE_H_

class TNode
{
public:
    int element;
    TNode* left;
    TNode* right;

    TNode(int i, TNode* l, TNode* r)
    {
        element = i; left = l; right = r;
    }

    // add a destructor
    // deletes all nodes when we call delete on root
    ~TNode(){
    	delete left; // delete does an implicit call to destructor (recursion; deleting all leaves)
    	delete right;
    }

};

#endif /* TNODE_H_ */
