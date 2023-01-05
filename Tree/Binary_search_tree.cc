// Binary Search Tree operations in C++
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stringstream;
using std::vector;

struct node {
    int key;
    struct node *left, *right;
};

// Create a node
struct node *newNode(int item) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert a node
struct node *insert(struct node *node, int key) {
    // Return a new node if the tree is empty
    if (node == NULL) return newNode(key);
    // Traverse to the right place and insert the node
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    return node;
}

// Print the tree
void printTree(node *root, string indent, bool last) {
    if (root != nullptr) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }
      cout << root->key << endl;
      printTree(root->left, indent, false);
      printTree(root->right, indent, true);
    }
}

const vector<string> Split(string s, string pattern){
    string::size_type begin, end;
    vector<string> result;
    end = s.find(pattern);
    begin = 0;

    while(end!=string::npos){
        if(end!=begin){
            result.push_back(s.substr(begin, end-begin));
        }
        begin = end+pattern.size();
        end = s.find(pattern, begin);
    }
    if (begin != s.length()) {
        result.push_back(s.substr(begin));
    }
    return result;
}
// Driver code
int main() {
    struct node *root = NULL;
    string input, pattern = ",";
    int num;
    vector<string> bst;
    vector<int> BST;
    system("chcp 65001");
    cout << "輸入:";
    getline(cin, input);
    bst = Split(input, pattern);
    for(auto i : bst){
      stringstream ss(i);
      ss >> num;
      BST.push_back(num);
    }
    for(auto i : BST){
      root = insert(root, i);
    }
    cout << endl;
    printTree(root, "", true);
    return 0;
}