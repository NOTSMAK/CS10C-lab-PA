#include "Tree.h"
#include <iostream>
#include <string>

using namespace std;

Tree::Tree() {
  root = NULL; // root starts as null
}

Tree::~Tree() {
  killAll(root); //desconstructor alternative to delete all nodes in the tree from top to bottom and left to right
}
bool Tree::noChildren( Node* node ) const { // used to check if a node has 0 children
  return node->left == nullptr && node->right == nullptr && node->middle == nullptr; // 
}

void Tree::insert( const string& word ) { //insert helper
  if ( root == nullptr ) { // if root is null then new node is just added to the root
    root = new Node( word );
  } 
  else {
    insert( root, word ); // calls the other insert fuction with using root and word 
  }
}

void Tree::insert(Node* curr, const string& word) { // insert with a given curr node parameter and string parameter
    if (word == curr->small || (!curr->large.empty() && word == curr->large)){ // if word is currs small or currs large then the code breaks
        return;
    }
    // Traverse to the correct position
    while (curr->left != nullptr) {  // if there is a curr left the code continues as there as if there is not left then theres no right or middle therefore curr is at the lowest height of the tree
      if (!curr->large.empty()) { // if currs large is not empty or curr atleast has 2 node 
        if (word < curr->small) { // if word is less than currs small
          curr = curr->left; // curr moves left
        }
        else if ( word > curr->large) { // if word is great than currs large
          curr = curr->right; // curr moves right
        } 
        else {
          curr = curr->middle; // other wise the only possible solution is curr to go middle 
        }
      } 
      else { // if currs large is empty therefore curr only has two children node left and middle
        if (word < curr->small) { // if word is less than currs small 
          curr = curr->left; // curr moves left 
        } 
        else {
          curr = curr->middle; // or else curr moves middle as theres no right because large doesn't exist 
        }
      }
    }
    if (!curr->large.empty()) {  // after the loop if currs large is not empty then 
        split(curr, word); // recursively call split fuction to make space 
    } 
    else { // after making space there curr should be the correct space to add word with large being empty
      if (word < curr->small) {  // if word is less then small 
        curr->large = curr->small; // large becomes the old small
        curr->small = word; // small because the new word
        curr->numData++; // numData increased
      } 
      else {
        curr->large = word; // only other possiblties is word being greater than small with large being empty therefore large becomes the new word;
        curr->numData++;
      }
    }
}


// This is handy since it puts a key into the right spot (small or
// large string)
void Tree::addData( Node* addHere, const string& word ) { // addData helper adds newData into a Node (NOT USED)
  if(addHere && addHere->numData != 2){
    if(addHere->small > word) {
      string hold = addHere->small;
      addHere->small = word;
      addHere->large = hold;
    }
    else{
      string hold = addHere->large;
      addHere->large = word;
      addHere->small = hold;
    }
  }
}

void
Tree::preOrder() const { // preOrderHelper
  preOrder( root ); // preorders using the root
  cout << endl; 
}

void Tree::preOrder( const Node* curr ) const { // outputs from root to left and then right subtrees
    if (curr != nullptr) {
        if (!curr->large.empty()) { // if a node has both large and small key
          cout << curr->small << ", ";  // outputs left from start to end
          preOrder(curr->left); // nodes left is now recursively called and then its small is outputed
          cout << curr->large << ", "; // after every lefts small is outputed then its large is outputed recursively
          preOrder(curr->middle); // middle is called and its small is outputted and then its large recursively
          preOrder(curr->right); // right is called and its small is ouputted and then its large
        }
        else { // if theres only one key in a node
          cout << curr->small << ", "; //currs small is outputed
          preOrder(curr->left); // goes left and recursively outputs every left small key
          preOrder(curr->middle); //goes middle
        }
      }
}

void Tree::inOrder() const {
  inOrder( root );
  cout << endl;
}

void Tree::inOrder(const Node* curr) const {  //ouputs from left end to root and then right end 
  if (curr != nullptr) { 
    inOrder(curr->left); 
    cout << curr->small << ", "; 
    inOrder(curr->middle); 
    if (!curr->large.empty()){
      cout << curr->large << ", ";
      inOrder(curr->right);
    }
  }
}

void Tree::postOrder() const { 
  postOrder( root );
  cout << endl;
}

void Tree::postOrder(const Node* curr) const { // outputs left end then right end and continuues till reaches root
  if (curr != nullptr) {
    if (!curr->large.empty()) { 
      postOrder(curr->left); 
      postOrder(curr->middle);
      cout << curr->small << ", ";
      postOrder(curr->right);
      cout << curr->large << ", ";
      }
    else { // if there's only one key in node
      postOrder(curr->left);
      postOrder(curr->middle);
      cout << curr->small << ", ";
    }
  }
}

void Tree::remove(const string& word) {
{
  Node* deleteNode = root; // deleteNode points to the root
  while (deleteNode != nullptr) { // loops untill deleteNode is null
    if(deleteNode->small == word || (!deleteNode->large.empty() && deleteNode->large == word)) { // if deleteNode matches with any of the possible keys in a node then the loop breaks
      break;
    }
    else { // case where the node doesn't have a key that matches with word parameter
      if (deleteNode->small > word) { // if delete Node's small is greater than word
        deleteNode = deleteNode->left; // then deleteNode goes left 
      }
      else {
        if (!deleteNode->large.empty()  && deleteNode->large < word) {
          deleteNode = deleteNode->right; // other case where deleteNode goes right 
        }
        else {
          deleteNode = deleteNode->middle; // if any of the other case doesn't work then deleteNode goes middle to look for the key
        }
      }
    }
  }
  if (deleteNode != nullptr){ // if deleteNode finds the correct Node then it wouldn't be nullptr
    if (!deleteNode->large.empty()) { // if deleteNodes large is empty 
      if (word == deleteNode->small) { // and word is deleteNodes small
        deleteNode->small = deleteNode->large; // deleteNode's small is changed to large 
        deleteNode->large = ""; // large is changed to empty
      }
      else {
        deleteNode->large = ""; ;// if word isn't deleteNodes small then it is definitly deleteNodes large therefore it is emptied 
      }
    }
    else { // if deleteNodes large is empty then rearangement within the tree is needed
    Node* parent = deleteNode->parent;  // parent pointer points to deleteNodes parent
    if (parent != nullptr) { // if parent isn't null
      if (word < parent->small) { // and if word is less than parents small 
        parent->left = nullptr; // parents small becomes null 
        parent->large = parent->middle->small; // parents large becomes parents middles small
        parent->middle = nullptr; // parents middle becomes nullptr
        } 
      else {
        parent->middle = nullptr; // parents middle is null
        parent->large = parent->small; //parents large is parents small 
        parent->small = parent->left->small; // parent small is parents lefts small
        parent->left = nullptr; // parents left becomes nullptr
      }
    }
    else { // if parent Node is null and curr is the root node
    Node* holdNode = new Node(); // holdNode is created for the tree to increase in height as root doesn't have a parent
      if (root->left != nullptr) { // if root has atleast one child
        holdNode->small = root->left->small; // holdNodes small is roots lefts small
        holdNode->large = root->middle->small; //holdNodes large is roots middles small
        root = holdNode; // holdNode becomes root
      } 
      else { // if roots left is nullptr 
        root = nullptr;  // root can be deleted without trouble
      }
    }
  }
}
}
}
bool Tree::hasTwoChildSibling(Node* sibling) const { //NOT USED but checks if a node has two siblings
    if (!sibling || !sibling->parent) 
        return false;

    Node* parent = sibling->parent;
    return (parent->left && parent->middle && parent->right);
}

Node* Tree::search(const string& word) { // Search Helper
  return search(root, word); // search using root
}

Node* Tree::search( Node* curr, const string& word ) {
    if (curr == nullptr) { // curr is nullptr then return nullptr
        return nullptr;
    }
    if (curr->small == word || (!curr->large.empty() && curr->large == word)) { // if curr's small is word or currs large is small then curr is returned as it holds value that is being searhed for
        return curr; 
    }
    if (word < curr->small) { // if word is smaller than curr then curr is moved left and using recursion the curr->left is check and so on
        return search(curr->left, word);
    } else if ( word > curr->large) { // if word is greater than curr large then curr moves right and recursively check if it holds word
        return search(curr->right, word);
    } else {
        return search(curr->middle, word); // other case where middle is checked recursively
    }
 
}
void Tree::split (Node* curr, const string &key){
    string small; // small to keep track of small key
    string middle; // middle to keep track of the key that gets added to the parent 
    string large; //  large to keep track of the large key 
    if(key < curr->small){ // if new key is less than currs small then currs
        small  = key; // small becomes new key 
        middle = curr->small;  // middle becomes currs small 
        large = curr->large; //  large becomes currs large
    }
    else if(key > curr->large && !(curr->large.empty())){ // if key is greater than large and currs large is not empty(it shouldn't be empty)
        small = curr->small; // small becomes currs small
        middle = curr->large; // middle becomes currs large
        large = key; // large becomes new key
    }
    else{// other situation where key is greater than small but less than middle
        small = curr->small; // small is currs small
        middle = key; // middle is key
        large = curr->large; // large is currs large
    }
     // two new Nodes are created to keep track of the two different keys small and large and after middle is moved up to the parent
    Node* newSmallNode = new Node(); // newSmallNode points to the small of the curr
    newSmallNode -> small = small;
    Node * newLargeNode = new Node();
    newLargeNode-> small  = large; // newLargeNode small points to the large of curr

    if(curr->parent == nullptr){ // if currs parent is null
        curr->small = middle; // currs small becomes middle 
        curr->large = ""; // currs large deleted
        curr->left = newSmallNode; // currs left points to newSmallNode with newSmallNode holding currs small key
        curr->middle = newLargeNode; // currs middle points the newLargeNode which holds currs large 
        curr->right = nullptr; // currs right is null
        newSmallNode->parent = curr; // newSmallNodes are now curr which holds the middle as its only key
        newLargeNode->parent = curr; // same with newLargeNode
        root = curr; // root is curr because this case was spliting when root had full cpacity therefore after spliting curr holding the middle value is now root
     } // with two newNode holding small and large values of curr therefore making more space for newNodes to be added
    else{// other case where parent is not nullptr/ curr isn't root
        Node *parent = curr->parent; // new Node pointer parent points to currs parent 
        newSmallNode->parent = parent; // newSmallNodes parent points to currs parent
        newLargeNode->parent = parent; // same with newLarge
        if(parent->left == curr){ //if parents left is curr then 
            parent->left = nullptr; // parents left gets deleted
        }
        else if(parent->middle == curr){ // parents middle is curr then middle gets deleted
            parent->middle = nullptr;
        }
        else{
            parent->right = nullptr; // if parents right is curr then middle gets deleted 
        }
        // after properly storing currs properties, curr is deleted to rearange the nodes
      split(parent, middle, newSmallNode, newLargeNode);  // split takes in all the values of curr to connect everything together
    }
}
void Tree::split(Node * parent, const string &middle, Node* newSmallNode, Node*newLargeNode){
    if(!parent->large.empty()){ // if currs large is not empty then curr is split again recursively
        split(parent,middle);
    }
    else{ // otherwise rearanging is possible as curr has space to add a new value from below
        if(middle < parent->small){ // if middle is less then parents small
        parent->large = parent->small; // parent large becomes parents small
        parent->small = middle; //parents small becomes middle
        parent->right = parent->middle; // parents right is parents middle as newSmallNode and newLargeNode are from below therefore less than parents middle
        parent->left = newSmallNode; // parents left points to newSmall Node
        parent->middle = newLargeNode; // parents middle becomes the newLargeNode
        }
        else{ // other case where middle is greater than parents small 
            parent->large = middle; // parents large becomes the middle
            parent->middle = newSmallNode; // parents middls becomes newSmallNode
            parent->right = newLargeNode; //parents middls becomes newLargeNOde
        }
        newSmallNode->parent = parent; // newSmallNodes parent points to parent 
        newLargeNode->parent = parent; // newLargeNodes parent points to parent
    }
}