#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stringstream;
using std::vector;
using std::find;
using std::distance;

class TreeNode {
public:
    string data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(string s) : data(s), left(NULL), right(NULL) {};
    
    friend class Solution;
    
};

// Print the tree
void printTree(TreeNode *root, string indent, bool last) {
    if (root != nullptr) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }
      cout << root->data << endl;
      printTree(root->left, indent, false);
      printTree(root->right, indent, true);
    }
}

class Solution {
public:
    TreeNode* BuildTree(vector<string>& preorder, vector<string>& inorder) {
        if(preorder.empty()) return NULL;

        // decide root
        TreeNode* root = new TreeNode(preorder[0]);

        // build left & right subtree
        vector<string>::iterator it = find(inorder.begin(), inorder.end(), preorder[0]);
        int num = distance(inorder.begin(), it);
        vector<string> leftPre(&preorder[1], &preorder[num+1]);
        vector<string> leftIn(&inorder[0], &inorder[num]);
        vector<string> rightPre(&preorder[1+num], &preorder[preorder.size()]);
        vector<string> rightIn(&inorder[num+1], &inorder[inorder.size()]);
        root->left = BuildTree(leftPre, leftIn);
        root->right = BuildTree(rightPre, rightIn);
        return root;
    }
};

const vector<string> split(const string& str, const string& pattern) {
    vector<string> result;
    string::size_type begin, end;//保證足夠長的string可被儲存

    end = str.find(pattern);
    begin = 0;

    while (end != string::npos) {//npos表示size_type的最大值，用来表示不存在的位置
        if (end - begin != 0) {
            result.push_back(str.substr(begin, end-begin)); //substr印出begin~end之間的string
        }    
        begin = end + pattern.size();
        end = str.find(pattern, begin);
    }

    if (begin != str.length()) {
        result.push_back(str.substr(begin));
    }
    return result;        
}

int main(){
    string input_1, input_2;
    vector<string> preorder;
    vector<string> inorder;
    string pattern = ",";
    system("chcp 65001");
    cout << "前序走訪:" ;
    getline(cin, input_1);
    cout << "中序走訪:" ;
    getline(cin, input_2);
    preorder = split(input_1, pattern);
    inorder = split(input_2, pattern);
    Solution T;
    auto root = T.BuildTree(preorder, inorder);
    printTree(root, "", true);
    return 0;
}