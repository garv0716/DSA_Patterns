#include <iostream>
#include <queue>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (root == nullptr)
            return true;

        queue<TreeNode*> q;
        q.push(root);

        bool nullFound = false;

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            if (node == nullptr) {
                nullFound = true;
            } 
            else {
                if (nullFound)
                    return false;

                q.push(node->left);
                q.push(node->right);
            }
        }

        return true;
    }
};

int main() {
    /*
            1
          /   \
         2     3
        / \   /
       4   5 6

       Complete Binary Tree
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    root->right->left = new TreeNode(6);

    Solution obj;

    if (obj.isCompleteTree(root))
        cout << "Complete Binary Tree" << endl;
    else
        cout << "Not a Complete Binary Tree" << endl;

    return 0;
}