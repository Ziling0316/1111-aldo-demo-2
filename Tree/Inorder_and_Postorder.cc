#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::vector;

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

class TreeNode{
public:
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    string str;

    TreeNode(string s): parent(0), left(0), right(0), str(s){};
};

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
      cout << root->str << endl;
      printTree(root->left, indent, false);
      printTree(root->right, indent, true);
    }
}

class Solution{
public:
    TreeNode* BuildTree(vector<string>& inorder, vector<string>& postorder){
        if(postorder.empty())  return NULL;
        TreeNode* root = new TreeNode(postorder[postorder.size()-1]);
        vector<string>::iterator it = find(postorder.begin(), postorder.end(), inorder[inorder.size()-1]);
        int num = distance(postorder.begin(), it);

        vector<string> leftIn(&inorder[0], &inorder[num]);
        vector<string> leftPost(&postorder[0], &postorder[leftIn.size()]);
        vector<string> rightIn(&inorder[num+1], &inorder[inorder.size()]);
        vector<string> rightPost(&postorder[leftIn.size()], &postorder[postorder.size()-1]);

        root->left = BuildTree(leftIn, leftPost);
        root->right = BuildTree(rightIn, rightPost);

        return root;
    }

};

int main(){
    string input_1, input_2, pattern = " ";
    vector<string> Inorder;
    vector<string> Postorder;
    system("chcp 65001");
    cout << "中序走訪:" ;
    getline(cin, input_1);
    cout << "後序走訪:" ;
    getline(cin, input_2);
    Inorder = Split(input_1, pattern);
    Postorder = Split(input_2, pattern);
    Solution T;
    auto root = T.BuildTree(Inorder, Postorder);
    printTree(root, "", true);
    return 0;
}