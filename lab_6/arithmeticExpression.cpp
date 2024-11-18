#include "arithmeticExpression.h"
#include <iostream>
#include <cstdlib>
#include <stack>
#include <fstream>
#include <sstream>

using namespace std;
void arithmeticExpression::buildTree(){  
    infixExpression = infix_to_postfix();  // converts data from infix to postfix
	stack <TreeNode*> StackOfNodes; // stack of TreeNode pointers

	for (unsigned i = 0; i < infixExpression.size(); ++i) {  // checks the priority of infix Expression and pushes it to stack accordingly 
		TreeNode *newNode = new TreeNode(infixExpression.at(i), 'a' + i); // newNode is created for every character of infixExpression
		if (priority(infixExpression.at(i)) == 0) { // if priority is 0 then newNode is pushed into stack
			StackOfNodes.push(newNode);
		}
		else if (priority(infixExpression.at(i)) > 0) { // other case if priority is greater than 0 
			newNode->right = StackOfNodes.top(); // newNodes right is Stacks top
			StackOfNodes.pop(); // stacks top is deleted 
			newNode->left = StackOfNodes.top(); //stacks new top is newNodes left
			StackOfNodes.pop(); //stacks top is deleted again 
			StackOfNodes.push(newNode); //stacks top is now newNode with its right being the higher priority and left being lower
			root = newNode; // root is newNode as the last node on the right has the highest priority 
		}
	}
}

arithmeticExpression::arithmeticExpression(const string &Input){
    infixExpression = Input; // infixExpression is set to the parameter input;
    root = 0; // root is 0
}
 void arithmeticExpression::infix() { // infix helper 
    infix(root);
 }

void arithmeticExpression::prefix() { //prefix helper 
    prefix(root);
}

void arithmeticExpression::postfix() { // postFix helper 
    postfix(root);
}

 void arithmeticExpression::infix(TreeNode *Node){ 
if (Node == 0) { // if node is 0 then there is no node to put into the infix order
		return; 
	}
	if (priority(Node->data)!= 0) { // if priority isn't 0
		cout << "("; // output left parenthasis 
		infix(Node->left); // nodes go left 
		cout << Node->data; // output that data 
		infix(Node->right); // node right 
		cout << ")"; // end parenthesis 
	}
	else {
		infix(Node->left); // if priority is 0 then go left and out put all of that data and then go right 
		cout << Node->data; //output Node data
		infix(Node->right); //go right
	}
}
 

void arithmeticExpression::prefix(TreeNode *Node){  // prefix order

    	if (Node == nullptr) { // if node is nullptr then return
		return;
	} // output all left data and then right data in prefix order
    cout << Node->data; // output node data 
	prefix(Node->left); // go left 
	prefix(Node->right); // then go right
}

    /* Helper function that outputs the postfix notation of the arithmetic expression tree
       by performing the postorder traversal of the tree. */
    void arithmeticExpression::postfix(TreeNode *Node){
    if (Node == nullptr) { // if node is nullptr then return
		return; 
	} // outputting in prefix order 
	postfix(Node->left); // go left 
	postfix(Node->right); // then go right 
	cout << Node->data; // then start output from the bottom of the tree
}
int arithmeticExpression::priority(char op){ // returns 
    int priority = 0;
    if(op == '('){  // if op is a first parenthesis then priority is 3
        priority =  3;
    }
    else if(op == '*' || op == '/'){ // if its a m or d then priority is 2nd highest
        priority = 2;
    }
    else if(op == '+' || op == '-'){ // if addition and subtraction the priority is higher 
        priority = 1;
    }
    return priority; // if its last parenthasis then priority is last
}

string arithmeticExpression::infix_to_postfix(){ //given code to get arithmetic Expression from file 
    stack<char> s; 
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}


 