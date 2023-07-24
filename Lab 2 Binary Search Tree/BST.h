// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.
// 05/13/2022 pragma once modification by Prof Sipantzi
// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"

#pragma once

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
private:
    BSTNode<Key, E>* root;   // Root of the BST

    int nodecount;         // Number of nodes in the BST

    // Private "helper" functions
    void clearhelp(BSTNode<Key, E>*);
    BSTNode<Key, E>* inserthelp(const Key&, const E&);
    BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
    BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
    BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
    E* findhelp(BSTNode<Key, E>*, const Key&) const;
    void printhelp(BSTNode<Key, E>*, int) const;
    void vist(BSTNode<Key, E>*) const;

public:
    BST() { root = NULL; nodecount = 0; }  // Constructor

    //Note from Prof Sipantzi -- I've commented out the destructor
    //since you would have to change clearhelp() to make it work with
    //doubly-threaded trees and that is not part of the assignment.
    //~BST() { clearhelp(root); }            // Destructor

    void clear()   // Reinitialize tree
    {
        clearhelp(root); root = NULL; nodecount = 0;
    }

    // Insert a record into the tree.
    // k Key value of the record.
    // e The record to insert.
    void insert(const Key& k, const E& e) {
        inserthelp(k, e);
        nodecount++;
    }

    // Remove a record from the tree.
    // k Key value of record to remove.
    // Return: The record removed, or NULL if there is none.
    E* remove(const Key& k) {
        E* temp = findhelp(root, k);   // First find it
        if (temp != NULL) {
            root = removehelp(root, k);
            nodecount--;
        }
        return temp;
    }

    // Remove and return the root node from the dictionary.
    // Return: The record removed, null if tree is empty.
    E* removeAny() {  // Delete min value
        if (root != NULL) {
            E* temp = new E;
            *temp = root->element();
            root = removehelp(root, root->key());
            nodecount--;
            return temp;
        }
        else return NULL;
    }

    // Return Record with key value k, NULL if none exist.
    // k: The key value to find. */
    // Return some record matching "k".
    // Return true if such exists, false otherwise. If
    // multiple records match "k", return an arbitrary one.
    E* find(const Key& k) const { return findhelp(root, k); }

    // Return the number of records in the dictionary.
    int size() { return nodecount; }

    void print() const { // Print the contents of the BST
        if (root == NULL) cout << "The BST is empty.\n";
        else printhelp(root, 0);
    }

    void printInorder() {
        BSTNode<Key, E>* ptr = root->left();

        while (ptr->getLBit() == true) {
            ptr = ptr->left();
        }

        while (ptr != root) {
            cout << ptr->element() << endl;

            if (ptr->getRBit() == false) { ptr= ptr->right(); }
            else {
                ptr = ptr->right();

                while (ptr->getLBit() != false) {
                    ptr = ptr->left();
                }
            }

        }

    }

    void printReverse() {
        int tracker{ 0 };

        BSTNode<Key, E>* ptr = root->left();
        ptr = ptr->right();

        while (ptr->getRBit() == true) {
            ptr = ptr->right();
        }

        while (tracker < nodecount) {

            cout << ptr->element() << endl;
            tracker++;

            if (ptr->getLBit() == false) { ptr = ptr->left(); }
            else {
                ptr = ptr->left();

                while (ptr->getRBit() != false) {
                    ptr = ptr->right();
                }
            }

        }

    }

};

// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key,E>* r) const {
    cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* root) {
  if (root == NULL) return;
  clearhelp(root->left());
  clearhelp(root->right());
  delete root;
}

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp( const Key& k, const E& it) {
        
    BSTNode<Key, E>* node = new BSTNode<Key, E>(k, it, NULL, NULL);
    bool addLeft = true;

    //if the tree is empty, create node
    if (nodecount == 0) {
        root = new BSTNode<Key, E>;
        root->setLBit(false);
        root->setRBit(false);
        root->setRight(root->right());

        node->setLBit(root->getLBit());
        node->setRBit(root->getRBit());

        root->setLeft(node);
        node->setLeft(root->left());
        root->setLBit(true);
        node->setRight(root);
        
        return node;
    }
    else {
        BSTNode<Key, E>* current = root->left();

        while (true) {
            //if the new node is less than the current node
            if (k < current->key()) {
                //if the node has an open left thread
                if (current->getLBit() == false) {
                    addLeft = true;
                    break;
                }
                else { current = current->left(); }
            }
            else {//Otherwise new node > current node
                //if the node has an open right thread
                if (current->getRBit() == false) {
                    addLeft = false;
                    break;
                }
                else { current = current->right(); }
            }
        }
        if (addLeft) {
            //add node as left child and update bit values
            node->setLeft(current->left());
            current->setLeft(node);
            node->setLBit(current->getLBit());
            node->setRBit(false);
            current->setLBit(true);
            node->setRight(current);
            
        }
        else if (!addLeft) {
            //add node as right child and update bit values
            node->setRight(current->right());
            current->setRight(node);
            node->setRBit(current->getRBit());
            current->setRBit(true);
            node->setLeft(current);

        }

        return node;
    }

}


// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
  if (rt->left() == NULL)
    return rt;
  else return getmin(rt->left());
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
  if (rt->left() == NULL) // Found min
    return rt->right();
  else {                      // Continue left
    rt->setLeft(deletemin(rt->left()));
    return rt;
  }
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* rt, const Key& k) {
  if (rt == NULL) return NULL;    // k is not in tree
  else if (k < rt->key())
    rt->setLeft(removehelp(rt->left(), k));
  else if (k > rt->key())
    rt->setRight(removehelp(rt->right(), k));
  else {                            // Found: remove it
    BSTNode<Key, E>* temp = rt;
    if (rt->left() == NULL) {     // Only a right child
      rt = rt->right();         //  so point to right
      delete temp;
    }
    else if (rt->right() == NULL) { // Only a left child
      rt = rt->left();          //  so point to left
      delete temp;
    }
    else {                    // Both children are non-empty
      BSTNode<Key, E>* temp = getmin(rt->right());
      rt->setElement(temp->element());
      rt->setKey(temp->key());
      rt->setRight(deletemin(rt->right()));
      delete temp;
    }
  }
  return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root,
                              const Key& k) const {
  if (root == NULL) return NULL;          // Empty tree
  if (k < root->key())
    return findhelp(root->left(), k);   // Check left
  else if (k > root->key())
    return findhelp(root->right(), k);  // Check right
  else {
      E* temp = new E;
      *temp = root->element();
      return temp;  // Found it
  }
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::
printhelp(BSTNode<Key, E>* root, int level) const {

    if (root == NULL) return;

    if (root->getLBit() == true) {
        printhelp(root->left(), level + 1);
    }

    for (int i = 0; i < level; i++)         // Indent to level
    {  cout << "  ";  }
    if (root->key() != 0)
    {
        cout << root->key() << endl;
    }

    if (root->getRBit() == true) {
        printhelp(root->right(), level + 1);
    }

}
