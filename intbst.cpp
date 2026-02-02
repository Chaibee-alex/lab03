// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n == nullptr)
        return;
    clear (n -> left);
    clear (n -> right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root)
    {
        Node* temp = new Node(value);
        root = temp;
        return true;
    }

    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (n == nullptr) {
        root = new Node(value);
        return true;
    }

    if (value == n->info) return false;

    if (value < n->info) {
        if (n->left == nullptr) {
            n->left = new Node(value);
            return true;
        }
        return insert(value, n->left);
    } else {
        if (n->right == nullptr) {
            n->right = new Node(value);
            return true;
        }
        return insert(value, n->right);
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n == nullptr)
        return;
    cout << n -> info << " "; 
    printPreOrder (n -> left);
    printPreOrder (n -> right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (n == nullptr) return;
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n == nullptr) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (!n)
        return 0;
    
    return sum (n -> left) + n -> info + sum (n -> right); 
}

// return count of values
int IntBST::count() const {
    return count (root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (n == nullptr) return 0;
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (n == nullptr)
        return nullptr;
    if (value == n -> info)
        return n;
    
    if (value < n -> info) 
        return getNodeFor(value, n -> left);
    else
        return getNodeFor(value, n -> right);
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != nullptr;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* target = getNodeFor(value, root);
    if (target == nullptr) return nullptr;

    if (target->left != nullptr) {
        Node* temp = target->left;
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        return temp;
    }

    Node* temp = root;
    Node* store = nullptr;
    while (temp != nullptr) {
        if (value > temp->info) {
            store = temp;
            temp = temp->right;
        } else if (value < temp->info) {
            temp = temp->left;
        } else {
            break;
        }
    }
    return store;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* temp = getPredecessorNode(value);
    if (!temp)
        return 0;
    return temp -> info;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* target = getNodeFor(value, root);
    if (target == nullptr) return nullptr;

    if (target->right != nullptr) {
        Node* temp = target->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    }
    Node* store = nullptr;
    Node* temp = root;
    while (temp != nullptr) {
        if (value < temp->info) {
            store = temp;
            temp = temp->left;
        } else if (value > temp->info) {
            temp = temp->right;
        } else {
            break;
        }
    }
    return store;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* temp = getSuccessorNode(value);
    if (temp == nullptr) return 0;
    return temp->info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value) {
    Node* parent = nullptr;
    Node* cur = root;

    while (cur != nullptr && cur->info != value) {
        parent = cur;
        if (value < cur->info) cur = cur->left;
        else cur = cur->right;
    }
    if (cur == nullptr) return false;

    if (cur->left != nullptr && cur->right != nullptr) {
        Node* predParent = cur;
        Node* pred = cur->left;
        while (pred->right != nullptr) {
            predParent = pred;
            pred = pred->right;
        }
        cur->info = pred->info;

        parent = predParent;
        cur = pred;
    }

    Node* child = (cur->left != nullptr) ? cur->left : cur->right;

    if (parent == nullptr) {
        root = child;
    } else if (parent->left == cur) {
        parent->left = child;
    } else {
        parent->right = child;
    }

    delete cur;
    return true;
}

