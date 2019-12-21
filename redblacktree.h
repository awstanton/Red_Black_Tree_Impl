#ifndef __REDBLACKTREE__
#define __REDBLACKTREE__

#include <memory>
#include <iostream>

enum Color {RED, BLACK};

struct Node {
	Node* parent;
	Node* left;
	Node* right;
	int data;
	Color color;
};

class redBlackTree {
public:
    friend void rbswap(redBlackTree& rb1, redBlackTree& rb2);

    redBlackTree();

    redBlackTree(const redBlackTree&);

    redBlackTree& operator=(redBlackTree);

    ~redBlackTree();

    void rbPrint();

    Node* rbFind(int);

    void rbInsert(int);

    void rbDelete(int);

    void preorderPrint(Node*);

    void inorderPrint(Node*);

    void postorderPrint(Node*);

    Node* getRoot();
    Node* getNil();
    std::allocator<Node>& getAlloc();

private:
    Node* root; // with a synthesized constructor, these variables would get undefined value
	Node* nil;
	std::allocator<Node> alloc;

    void leftRotate(Node*);

    void rightRotate(Node*);

    void rbInsertFix(Node*);

    void transplant(Node*, Node*);

    Node* rightMinimum(Node*);

    void rbDeleteFix(Node*);
};

#endif // __REDBLACKTREE


// https://www.learncpp.com/cpp-tutorial/89-class-code-and-header-files/
// https://www.learncpp.com/cpp-tutorial/1-10a-header-guards/
// https://is.muni.cz/www/408176/38744863/The_C__Programming_Language__Stroustrup_.pdf
// https://docs.microsoft.com/en-us/cpp/cpp/scope-visual-cpp?view=vs-2017
// https://docs.microsoft.com/en-us/cpp/cpp/program-and-linkage-cpp?view=vs-2017

// make tests more organized and less code
// improve existing code
// function to test whether each of the red-black properties is satisfied
// maybe print the level of each of the nodes in the print function
// method to print in tree format with branches and spaces and everything
// perhaps try to incorporate the SOLID principles
// also think about const versions of functions
// also consider whether to make a constructor or anything else explicit
// maybe make nil a static member of the class

// some sample uses of sets
//Set x();
//x.insert(5);
//x.delete(4);
//x.search(6);
// Set y(x);
// Set z;
// z = y;
// z = x;
// union
// intersection
// cartesian product
// set difference
// powerset
// operator==
// operator<<
// operator>>
