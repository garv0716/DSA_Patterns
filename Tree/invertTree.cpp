#include <iostream>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }

        swap(root->left, root->right);

        invertTree(root->left);
        invertTree(root->right);

        return root;
    }
};

// Function to print tree in preorder traversal
void preorder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    /*
            4
           / \
          2   7
         / \ / \
        1  3 6  9
    */

    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);

    cout << "Original tree (Preorder): ";
    preorder(root);
    cout << endl;

    Solution obj;
    root = obj.invertTree(root);

    cout << "Inverted tree (Preorder): ";
    preorder(root);
    cout << endl;

    return 0;
}