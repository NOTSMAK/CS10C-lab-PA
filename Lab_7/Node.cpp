#include "Node.h"

Node::Node(string key) {
    height = 0;
    data =key;
    left =nullptr;
    right = nullptr;
    parent =nullptr;  
}