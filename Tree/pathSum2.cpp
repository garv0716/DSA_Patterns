#include <iostream>
#include <vector>
using namespace std;

// Definition of Binary Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

vector<vector<int>> result;

// DFS function
void fun(Node* root, int sum, int target, vector<int>& diary) {
    if (!root)
        return;

    sum += root->data;
    diary.push_back(root->data);

    // Leaf node
    if (!root->left && !root->right) {
        if (sum == target)
            result.push_back(diary);

        diary.pop_back();
        return;
    }

    fun(root->left, sum, target, diary);
    fun(root->right, sum, target, diary);

    // Backtracking
    diary.pop_back();
}

// Wrapper function
vector<vector<int>> pathSum(Node* root, int target) {
    result.clear();
    vector<int> diary;
    fun(root, 0, target, diary);
    return result;
}

// Driver code
int main() {
    /*
            5
          /   \
         4     8
        /     / \
       11    13  4
      /  \      / \
     7    2    5   1

    Target = 22
    Output:
    5 4 11 2
    5 8 4 5
    */

    Node* root = new Node(5);
    root->left = new Node(4);
    root->right = new Node(8);

    root->left->left = new Node(11);
    root->left->left->left = new Node(7);
    root->left->left->right = new Node(2);

    root->right->left = new Node(13);
    root->right->right = new Node(4);
    root->right->right->left = new Node(5);
    root->right->right->right = new Node(1);

    int target = 22;

    vector<vector<int>> ans = pathSum(root, target);

    cout << "Paths with sum " << target << ":\n";
    for (auto& path : ans) {
        for (int x : path)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}