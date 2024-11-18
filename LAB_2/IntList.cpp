#include "IntList.h"

#include <iostream>
#include <exception>

using namespace std;

#define STRINGIZE(x) #x
#define STR(x) STRINGIZE(x)
#define HERE ("Broken at\n" __FILE__ ":" STR(__LINE__) ": broken")

#include <iostream>

ostream & operator<<(ostream &out, const IntList &rhs) {
  if(rhs.dummyHead.next == &rhs.dummyTail){ // checks if the list is empty
    return;
  }
  IntNode*OutPutNode = rhs.dummyHead.next; 
  while(OutPutNode != &rhs.dummyTail) { // adds all the values of each node to out 
    out << OutPutNode->data;
    if (OutPutNode->next != &rhs.dummyTail) { // used to add proper spacing 
      out << " ";
    }
    OutPutNode = OutPutNode->next; // traversing proccess 
  }
  return out;
}
//Deconstructor to delete all node at the end of runtime
IntList::~IntList() {
  while(!empty()){ // checks if not empty then deletes 
    pop_front();
  }
}
// adds a new node to the front of the list after dummyhead
void IntList::push_front(int value) {
  IntNode* newFrontNode = new IntNode(value); // create new node with value
  newFrontNode->next = dummyHead.next; //  new front node next points to dummy heads next
  newFrontNode->prev = &dummyHead; // its prev points to dummy head making it the new front node 
  dummyHead.next->prev = newFrontNode; // dummyHeads next previous pointer becomes frontNode
  dummyHead.next = newFrontNode; // dummyHeads next points to the newfront Node
}

void IntList::pop_front() { // 
  if(empty()){
  return;
  }
  IntNode* deleteNode = dummyHead.next; // delete node is pointing to the first node
  dummyHead.next = deleteNode->next; // dummyheads next changes to the node after the first Node
  deleteNode->next->prev = &dummyHead; // front Nodes next Nodes previous changes to dummyhead
  delete deleteNode; 
}

void IntList::push_back(int value) {
   if(empty()){
     IntNode* newLastNode = new IntNode(value);
  }
   IntNode* newLastNode = new IntNode(value); // creates a newNode and pointer pointing to newNode
    newLastNode->next = &dummyTail; // newLastNodes next points to dummyTail
    newLastNode->prev = dummyTail.prev; // dummyTails previous points to newlastNOde
    dummyTail.prev->next = newLastNode; // Node before dummyTail points to newLastNode
    dummyTail.prev = newLastNode;
}

void IntList::pop_back() {
  if(empty()){
    return;
  }
  if (!empty()){
    IntNode* deleteNode = dummyTail.prev; // deleteNode holds the last Node
    dummyTail.prev = deleteNode->prev; // adjusts the prev pointers of dummy Tail to point to the Node before delete Node
    deleteNode->prev->next = &dummyTail; // deleteNodes previous node now points to dummy tail
    delete deleteNode;
  }
}

bool IntList::empty() const {
  return dummyHead.next == &dummyTail; // returns if the list is empty by checking dummyheads next ptr 
}
void IntList::printReverse() const {
  if(empty()){
    return;
  }
  IntNode *curr = dummyTail.prev; // curr ptr pointing to the last node
  if(dummyHead.next == &dummyTail){ // special case if theres no nodes other than dummyhead and dummytail
    cout << dummyTail.data << " "; 
    cout << dummyHead.data;
  }
  else{
    while(curr != &dummyHead){// checks if curr is dummyHead and traverses backwards using prev
      cout << curr->data ; // outputs currs data
      if (curr->next != nullptr) { // checks to see if it reaches the end to stop spacing
        cout  << " ";
      }
    curr = curr->prev; // traversing proccess
    }
  }
}

