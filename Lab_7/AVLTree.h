
#pragma once
#include "Node.h"
class AVLTree
{
    public: 
        AVLTree() {
            root = nullptr;
        };
         ~AVLTree(){
            Killall(root);
         }
         AVLTree(const AVLTree &) = delete;
         AVLTree& operator=(const AVLTree &) = delete;
        void insert(const string &);
        int balanceFactor(Node*);
        void printBalanceFactors();
        void Killall(Node *curr){ // deconstructor helper
            if(curr == nullptr){
                return;
            }
             Killall (curr->left);
             Killall(curr->right);
            delete curr;
        }
        
    private:
        Node* root;
        void printBalanceFactors(Node *printNode);
        int Height(Node*curr);
        Node* rotate(Node*);
        void rotateLeft(Node*);
        void rotateRight(Node*);
        bool updateChild(Node*,Node*,Node*);
        Node* fixBalance(Node*);
        bool setChild(Node*, string, Node*);
        void insert(Node *, Node*);
        
};