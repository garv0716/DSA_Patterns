#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Definition for a Binary Tree Node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {

        vector<vector<int>> ans;

        if (root == NULL)
            return ans;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {

            int levelSize = q.size();
            vector<int> temp;

            for (int i = 0; i < levelSize; i++) {

                TreeNode* node = q.front();
                q.pop();

                temp.push_back(node->val);

                if (node->left)
                    q.push(node->left);

                if (node->right)
                    q.push(node->right);
            }

            ans.push_back(temp);
        }

        return ans;
    }
};

int main() {

    /*
            3
          /   \
        20     9
       /  \   /
      4    5 10
    */

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(20);
    root->right = new TreeNode(9);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(10);

    Solution obj;
    vector<vector<int>> result = obj.levelOrder(root);

    cout << "Level Order Traversal:\n";

    for (auto level : result) {
        for (int val : level) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}