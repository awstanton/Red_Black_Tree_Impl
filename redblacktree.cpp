#include <memory>
#include <cstddef>
#include <iostream>
#include <memory>
#include "redblacktree.h"

void rbswap(redBlackTree& rb1, redBlackTree& rb2) {
    std::swap(rb1.root, rb2.root);
    std::swap(rb1.nil, rb2.nil);
    std::swap(rb1.alloc, rb2.alloc);
}

// tree traversal used in different places
// maybe make nil static
// maybe make rbDeleteFix more understandable
// maybe take out transplant
// ensure that time complexity is respected by analyzing my supporting functions

// default constructor
redBlackTree::redBlackTree() {
    nil = alloc.allocate(1);
    nil->parent = NULL;
    nil->left = NULL;
    nil->right = NULL;
    nil->data = 0;
    nil->color = BLACK;
    root = nil;
}

// copy constructor
redBlackTree::redBlackTree(const redBlackTree& rb) {
    if (rb.root == rb.nil) {
        nil = alloc.allocate(1);
        nil->parent = NULL;
        nil->left = NULL;
        nil->right = NULL;
        nil->data = 0;
        nil->color = BLACK;
        root = nil;
    }
    else {
        Node* ptr = rb.root;
        Node* prev = rb.root;
        Node* z1 = NULL;
        Node* z2 = NULL;
        bool done = false;

        nil = alloc.allocate(1);
        nil->parent = NULL;
        nil->left = NULL;
        nil->right = NULL;
        nil->data = 0;
        nil->color = BLACK;

        z1 = alloc.allocate(1);
        z1->data = ptr->data;
        z1->color = rb.root->color;
        z1->parent = nil;
        z1->left = nil;
        z1->right = nil;

        root = z1;

        while (!done) {
            ptr = ptr->left;
            // traverse downwards by left children
            while (ptr != rb.nil) {
                z2 = alloc.allocate(1);
                z2->data = ptr->data;
                z2->color = ptr->color;
                z2->left = nil;
                z2->right = nil;
                z2->parent = z1;

                z1->left = z2;
                z1 = z2;

                prev = prev->left;
                ptr = ptr->left;
            }
            ptr = prev;
            // traverse upwards
            while (ptr != rb.nil && (ptr->right == rb.nil || ptr->right == prev))  {
                prev = ptr;
                ptr = ptr->parent;
                z1 = z1->parent;
            }

            if (ptr == rb.nil) {
                done = true;
            }
            // traverse downwards by right child
            else {
                ptr = ptr->right;
                prev = ptr;

                z2 = alloc.allocate(1);
                z2->data = ptr->data;
                z2->color = ptr->color;
                z2->left = nil;
                z2->right = nil;
                z2->parent = z1;

                z1->right = z2;
                z1 = z2;
            }
        }
    }
}

// trying to use the copy-swap idiom by passing by value in parameter and swapping member variable values, letting destructor destroy the one swapped out - this works because pass by value copies into the function, so a copy is destroyed
redBlackTree& redBlackTree::operator=(redBlackTree rb) {
    rbswap(*this, rb);
    return *this;
}

// destructor
redBlackTree::~redBlackTree() {
    if (root == nil) {
        alloc.deallocate(nil, 1);
    }
    else {
        Node* ptr = root;
        Node* prev = root;
        bool done = false;

        while (!done) {
            ptr = ptr->left;
            while (ptr != nil) {
                prev = prev->left;
                ptr = ptr->left;
            }
            ptr = prev;

            while (ptr != nil && (ptr->right == nil || ptr->right == prev))  {
                prev = ptr;
                ptr = ptr->parent;
                if (ptr->right == prev)
                    ptr->right = nil;
                else
                    ptr->left = nil;
                alloc.deallocate(prev, 1);
            }

            if (ptr == nil) {
                done = true;
            }
            else {
                ptr = ptr->right;
                prev = ptr;
            }
        }
        alloc.deallocate(nil, 1);
    }
    root = NULL;
    nil = NULL;
}

// prints the nodes in order, followed by 0, to represent the nil node
void redBlackTree::rbPrint() {
    Node* ptr = root;
    Node* prev = root;
    bool done = false;

    if (root == nil || root == NULL)
        return;

    while (!done) {
        ptr = ptr->left;
        while (ptr != nil) {
            prev = prev->left;
            ptr = ptr->left;
        }
        ptr = prev;
        std::cout << ptr->data << " " << ptr->color << std::endl;

        while (ptr != nil && (ptr->right == nil || ptr->right == prev))  {
            prev = ptr;
            ptr = ptr->parent;
            if (ptr->right != prev)
                std::cout << ptr->data << " " << ptr->color << std::endl;
        }

        if (ptr == nil) {
            done = true;
        }
        else {
            ptr = ptr->right;
            prev = ptr;
        }
    }
    std::cout << std::endl;
}

// returns pointer to node if found, otherwise returns pointer to nil
Node* redBlackTree::rbFind(int value) {
    Node* ptr = root;
    while (ptr != nil) {
        if (value == ptr->data)
            return ptr;
        else if (value < ptr->data)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    return ptr;
}

void redBlackTree::rbInsert(int number) {
    Node* z = alloc.allocate(1);
    Node* y = nil;
    Node* x = root;

    z->data = number;

    // find position for new node
    while (x != nil) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    //  set pointers to and from new node's new parent
    z->parent = y;
    if (y == nil)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;
    // set pointers and color for new node
    z->left = nil;
    z->right = nil;
    z->color = RED;
    // maintain red-black tree property
    rbInsertFix(z);
}

// seems like this could be more easily/efficiently implemented by not using transplant (instead, use delete method and just change data values)
void redBlackTree::rbDelete(int number) {
    Node* z = rbFind(number);
    if (z != nil) {
        Node* y = z;
        Node* x;
        Color c = y->color;
        if (z->left == nil) {
            x = z->right;
            transplant(z, x);
        }
        else if (z->right == nil) {
            x = z->left;
            transplant(z, x);
        }
        else {
            y = rightMinimum(z);
            c = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                y->right = z->right;
                y->right->parent = y;
                y->parent->left = x;
                x->parent = y->parent;
            }
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
            transplant(z, y);
        }
        if (c == BLACK) {
            rbDeleteFix(x);
        }
    }
    nil->parent = NULL;
}

void redBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    // assign y's parent and assign child pointer of y's parent if needed
    if (root == x) {
        root = y;
        y->parent = nil;
    }
    else {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->parent = x->parent;

    }
    // assign x's parent
    x->parent = y;
    // assign x's right child
    if (y->left != nil) {
        x->right = y->left;
        x->right->parent = x;
    }
    else {
        x->right = nil;
    }
    // assign y's left child
    y->left = x;
}

void redBlackTree::rightRotate(Node* x) {
    Node* y = x->left;
    // assign y's parent and assign child pointer of y's parent if needed
    if (root == x) {
        root = y;
        y->parent = nil;
    }
    else {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->parent = x->parent;
    }
    // assign x's parent
    x->parent = y;
    // assign x's left child
    if (y->right != nil) {
        x->left = y->right;
        x->left->parent = x;
    }
    else {
        x->left = nil;
    }
    // assign y's right child
    y->right = x;
}

void redBlackTree::rbInsertFix(Node* z) {
    // ensure that proper checks on accessing members of nil are made
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) { // z's parent is a left child
            Node* y = z->parent->parent->right;
            if (y->color == RED) {                  // z's uncle is RED
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {                                  // z's uncle is BLACK
                if (z == z->parent->right) {        // z is a right child
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else {                                      // z's parent is a right child
            Node* y = z->parent->parent->left;
            if (y->color == RED) {                  // z's uncle is RED
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {                                  // z's uncle is BLACK
                if (z == z->parent->left) {         // z is a left child
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void redBlackTree::transplant(Node* x, Node* y) {
    if (x->parent == nil) {
        root = y;
        y->parent = nil;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
        y->parent = x->parent;
    }
    else {
        x->parent->right = y;
        y->parent = x->parent;
    }
    alloc.deallocate(x, 1);
}

Node* redBlackTree::rightMinimum(Node* x) {
    if (x->right == nil)
        return nil;
    else {
        Node* y = x->right;
        while (y->left != nil)
            y = y->left;
        return y;
    }
}

// HOW TO MAKE THIS FUNCTION MORE UNDERSTANDABLE
void redBlackTree::rbDeleteFix(Node* x) {
    Node* w;
    while (x != root && x->color != RED) {
        if (x == x->parent->left) {
            w = x->parent->right;
            // case 1
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            // case 2
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                // case 3
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                // case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

Node* redBlackTree::getRoot() {
    return root;
}

Node* redBlackTree::getNil() {
    return nil;
}

std::allocator<Node>& redBlackTree::getAlloc() {
    return alloc;
}
