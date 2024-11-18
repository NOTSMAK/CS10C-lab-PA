#include "AVLTree.h"

#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;



void AVLTree::insert(const string &key) {    
    Node* newNode = new Node(key); // newNode points to new Node created
    if (root == nullptr) { // if root is nullptr
        root = newNode; // root is the newNode
        root->parent = nullptr; // newNodes parents are nullptr as newNode is root
        return;
    }
    insert(root,newNode); // insert helper with root and newNode
}
   
void AVLTree::insert(Node *curr, Node*newNode){ 
    while (curr != nullptr) { // loops until curr is null
        if (newNode->data < curr->data) {  // if newNode data is less than currs data
            if (newNode->data == curr->data) { //case 1 if newNodes data matches with currs data then nothing can be inserted
                return;
            }
            if (curr->left == nullptr) { // if currs left is nullptr then
                curr->left = newNode; // currs left becomes newNode
                newNode->parent = curr; // newNodes parents become curr
                break; // break out of the loop
            }
            else { // other case go left
                curr = curr->left; 
            }   
        }
        else { // other case if newNodes data is greater than currs data
            if (newNode->data == curr->data) { // if newNodes data is equal to currs data then returns as newNode can't be added twice
                return;
            }
            if (curr->right == nullptr) { // if currs right is nullptr
                curr->right = newNode; // currs right is newNode
                newNode->parent = curr; // newNodes parents are curr
                break; // break out of the loop
            }
            else { //other case curr just moves right as newNOde data is greater than curr
                curr = curr -> right; 
            }     
        }    
    }
    newNode = newNode->parent; // newNode points to newNodes parents
while (newNode != nullptr) { // loops until newNode is nullptr
    fixBalance(newNode); // call fix balance to rebalance every node after insert 
    newNode = newNode -> parent; // newNode points to the next parent
}
    return;
}

Node* AVLTree::fixBalance(Node *newNode) {
    Height(newNode); // height is called on newNode to update the height
    if (balanceFactor(newNode) == -2) { // if balance factor is -2
        if(balanceFactor(newNode->right) ==1) { //if balance factor of rightNode is 1
            rotateRight(newNode->right); //rotate right right
        }
        rotateLeft(newNode);// rotate left
    }
    else if (balanceFactor(newNode) == 2) { // if balance factor of newNode is 2 
        if(balanceFactor(newNode->left) == -1) { // if balance factor of newNodes left node is -1 
            rotateLeft(newNode->left);// then rotate left first 
        }
        rotateRight(newNode); //  rotate right 
    }
    return newNode; 
}
void AVLTree::rotateRight(Node* curr) { //rotate right
    Node* leftRightChild = curr -> left -> right; // leftRightChild points to curr's left child's right child
    if (curr->parent != nullptr) { // if curr's parent isn't nullptr
        updateChild(curr -> parent, curr, curr->left); // update curr's parent's child from curr to curr's left child
    }
    else { // if curr has no parent, it's the root
        root = curr -> left; // update the root to curr's left child
        root -> parent = nullptr; // set the new root's parent to nullptr
    }
    setChild(curr->left, "right", curr); // set curr's left child's right child to curr
    setChild(curr, "left", leftRightChild); // set curr's left child to leftRightChild (curr's left child's right child)
}

void AVLTree::rotateLeft(Node* curr) { //rotate left
    Node* rightLeftChild = curr->right->left; // rightLeftChild points to curr's right child's left child
    if (curr->parent != nullptr) { // if curr's parent isn't nullptr
        updateChild(curr -> parent, curr, curr->right); // update curr's parent's child from curr to curr's right child
    }
    else { // if curr has no parent, it's the root
        root = curr -> right; // update the root to curr's right child
        root -> parent = nullptr; // set the new root's parent to nullptr
    }
    setChild(curr->right, "left", curr); // set curr's right child's left child to curr
    setChild(curr, "right", rightLeftChild); // set curr's right child to rightLeftChild (curr's right child's left child)
}

bool AVLTree::updateChild(Node* parent, Node* curr, Node* newChildNode) { 
   if (parent->left == curr) { // if curr is the left child of parent
        return setChild(parent, "left", newChildNode); // set parent's left child to newChildNode
   }
   else if (parent->right == curr) { // if curr is the right child of parent
      return setChild(parent, "right", newChildNode); // set parent's right child to newChildNode
   }
   return false; // curr is not a child of parent (should not happen in a valid AVL tree)
}

bool AVLTree::setChild(Node* parent, string childSide, Node* child) {
   if (childSide != "left" && childSide != "right") { // check if childSide is either "left" or "right"
      return false; // if not, return false
   }
   if (childSide == "left") { // if childSide is "left"
      parent->left = child; // set the parent's left child to the given child
   }
   else { // if childSide is "right"
      parent->right = child; // set the parent's right child to the given child
   }
   if (child != nullptr) { // if the child is not nullptr
      child->parent = parent; // set the child's parent to the given parent
   }
   Height(parent); // update the height of the parent node
   return true; // return true indicating the child was successfully set
}


int AVLTree::Height(Node* newNode) { // return the height of the node and update is as well
      int leftHeight = -1; // left height default is -1
    int rightHeight = -1; // right height default is -1
    if (newNode->left != nullptr) { //if newNodes left isn't nullptr
        leftHeight = newNode->left->height; // leftHeight is newNodes left height
    }

   if (newNode->right != nullptr) { // if newNodes right isn't nullptr 
       rightHeight = newNode->right->height; // rightHeight is newNOdes rights height
   }
   if (leftHeight > rightHeight) { // if leftHeight is greater than right height 
        newNode->height = leftHeight + 1; // newNodes height is leftHeight+1 to also count for the newNodes height itself
    } 
    else {
        newNode->height = rightHeight + 1; // newNodes height is rightHeight+1 to also count for the newNodes height itself
    
    }
    return newNode->height; // return newNodes height
}


int AVLTree::balanceFactor(Node* curr) {
    int leftHeight = -1; // left height default is -1
    int rightHeight = -1; // right height default is -1
    if (curr->left != nullptr ) { // if currs left isn't nullptr
        leftHeight = curr->left->height; // curr 
    }
    if (curr->right != nullptr) { // if currs right isn't nullptr
       rightHeight = curr->right->height; //rightHeight is currs right height
   }
   return leftHeight - rightHeight; //the balance factor is now the difference of leftHeight and right Height
}

void AVLTree::printBalanceFactors() {
    printBalanceFactors(root); // printNode helper
    cout << endl;
}

void AVLTree::printBalanceFactors(Node* printNode) { // prints as inOrder
    if (printNode == nullptr) { // base case
        return;
    }
    else {
        printBalanceFactors(printNode -> left); // go all the way left
         cout << printNode->data << "(" << balanceFactor(printNode) << "), " ; // output all left from bottom
        printBalanceFactors(printNode -> right); // then go right
    }
}
