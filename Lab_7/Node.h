#pragma once
#include <string>

using std::string;

class Node {
    public:
    Node();
    Node(string);
    int height;
    string data;
    Node* left;
    Node* right;
    Node* parent;
};
