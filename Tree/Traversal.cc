#include <iostream>
#include <string>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class BinaryTree;

class TreeNode{
    public:
        TreeNode* leftchild;
        TreeNode* rightchild;
        TreeNode* parent;
        string str;

        TreeNode():leftchild(0), rightchild(0), parent(0), str(" "){};
        TreeNode(string s):leftchild(0), rightchild(0), parent(0), str(s){};
};

class BinaryTree{
    public:
        TreeNode* root;
        BinaryTree():root(0){};
        BinaryTree(TreeNode* node):root(node){};

        void Preorder(TreeNode* current);
        void Inorder(TreeNode* current);
        void Postorder(TreeNode* current);
};

void BinaryTree::Preorder(TreeNode* current){
    if(current){
        cout << current->str << " ";
        Preorder(current->leftchild);
        Preorder(current->rightchild);
    }
}

void BinaryTree::Inorder(TreeNode* current){
    if(current){
        Inorder(current->leftchild);
        cout << current->str << " ";
        Inorder(current->rightchild);
    } 
}

void BinaryTree::Postorder(TreeNode *current){
    if (current) {                         // if current != NULL
        Postorder(current->leftchild);     // L
        Postorder(current->rightchild);    // R
        std::cout << current->str << " ";  // V
    }
}

int main(){
    TreeNode* nodeA = new TreeNode("A");
    TreeNode* nodeB = new TreeNode("B");
    TreeNode* nodeC = new TreeNode("C");
    TreeNode* nodeD = new TreeNode("D");
    TreeNode* nodeE = new TreeNode("E");
    TreeNode* nodeF = new TreeNode("F");

    nodeA->leftchild = nodeB;
    nodeA->rightchild = nodeC;
    nodeB->leftchild = nodeD;
    nodeB->rightchild = nodeE;
    nodeC->rightchild = nodeF;

    BinaryTree T(nodeA);
    system("chcp 65001");
    cout << "前序走訪:" << endl; 
    T.Preorder(nodeA);
    cout << endl;
    cout << endl;
    cout << "中序走訪:" << endl; 
    T.Inorder(nodeA);
    cout << endl;
    cout << endl;
    cout << "後序走訪:" << endl; 
    T.Postorder(nodeA);
    return 0;
}