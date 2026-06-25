# Complete Tree (DSA) Notes — Intuition-First

> Based on the full Tree series. Every intuition and analogy is preserved.

---

## 1. What is a Tree?

**Real-world analogy:** India's political hierarchy
- PM → Home Minister, Finance Minister → IAS Officers, Economists
- This branching, hierarchical structure **is** a tree

**Key terminology:**

| Term | Meaning |
|------|---------|
| Node | Every circle/box in the tree |
| Root Node | Topmost node — no parent (like the PM) |
| Leaf Node | Node with no children (left = null, right = null) |
| Parent | The node directly above |
| Child | Nodes directly below a parent |

**Binary Tree:** Every node has **at most 2 children** (left and right).

```
Node structure:
[ left | data | right ]
     ↓              ↓
 left child    right child
```

> Same as Linked List, but instead of one `next`, we have `left` and `right`.

---

## 2. Tree Traversals (Inorder, Preorder, Postorder)

**Family analogy:** Dada ji → Papa & Chacha → Pratyush, Pranjal, Sumit.
Chocolate is passed according to a fixed rule — who eats first depends on the traversal.

### Inorder (Left → Root → Right)
**Rule:** Give to left child first, eat yourself second, give to right child last.

```cpp
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data;
    inorder(root->right);
}
```

### Preorder (Root → Left → Right)
**Rule:** Eat yourself first, then left, then right.

```cpp
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data;
    preorder(root->left);
    preorder(root->right);
}
```

### Postorder (Left → Right → Root)
**Rule:** Left first, right second, eat yourself last.

```cpp
void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data;
}
```

**Trick to remember — where is Root?**
- **Pre**order  → Root is **first**
- **In**order   → Root is **middle**
- **Post**order → Root is **last**

**Complexity (all three):**
- Time:  `O(n)` — every node visited exactly once
- Space: `O(h)` — recursion stack depth = height of tree

---

## 3. Level Order Traversal (BFS using Queue)

**Why Queue?** We need First-In-First-Out to process nodes level by level.

**Queue basics:**
- `push`  → inserts from the back
- `front` → peek at the front element
- `pop`   → removes from the front

### Algorithm

1. Push root into queue
2. While queue is not empty:
   - Save `levelSize = queue.size()` (number of nodes on this level)
   - Loop `levelSize` times:
     - Pop front node `t`
     - Add `t->data` to temp array
     - Push `t->left` and `t->right` (if not null)
   - Push temp array into result

```cpp
vector<vector<int>> levelOrder(Node* root) {
    vector<vector<int>> res;
    if (!root) return res;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> tmp;
        while (levelSize--) {
            Node* t = q.front(); q.pop();
            tmp.push_back(t->data);
            if (t->left)  q.push(t->left);
            if (t->right) q.push(t->right);
        }
        res.push_back(tmp);
    }
    return res;
}
```

**Complexity:**
- Time:  `O(n)`
- Space: `O(n)` — queue holds up to one full level

### Zigzag Level Order (variation)

Use a boolean `leftToRight`. Fill temp array from front if true, from back if false. Toggle after each level.

```cpp
// Key change inside the inner loop:
if (leftToRight) tmp[first++] = t->data;
else             tmp[last--]  = t->data;

// After inner loop:
leftToRight = 1 - leftToRight;
```

---

## 4. Mirror / Symmetry Problems

### Same Tree (LeetCode 100)

**Intuition:** Two trees are the same if:
1. Both null → `true`
2. One null, other not → `false`
3. Values differ → `false`
4. Left subtrees same AND right subtrees same → `true`

```cpp
bool fun(Node* r1, Node* r2) {
    if (!r1 && !r2) return true;
    if (!r1 || !r2) return false;
    if (r1->data != r2->data) return false;
    bool R1 = fun(r1->left,  r2->left);
    bool R2 = fun(r1->right, r2->right);
    return R1 && R2;
}
```

**Complexity:** Time `O(n)`, Space `O(h)`

---

### Symmetric Tree (LeetCode 101)

**Intuition:** Split tree down the middle. In a mirror, left becomes right — so compare `r1->left` with `r2->right` and `r1->right` with `r2->left`.

```cpp
bool fun(Node* r1, Node* r2) {
    if (!r1 && !r2) return true;
    if (!r1 || !r2) return false;
    if (r1->data != r2->data) return false;
    bool R1 = fun(r1->left,  r2->right);  // mirror swap
    bool R2 = fun(r1->right, r2->left);   // mirror swap
    return R1 && R2;
}

bool isSymmetric(Node* root) {
    return fun(root->left, root->right);
}
```

**Complexity:** Time `O(n)`, Space `O(h)`

---

### Invert Tree (LeetCode 226)

**Intuition:** Every node swaps its left and right children. Tell children to do the same recursively (like a company where every manager swaps their two direct reports).

```cpp
void fun(Node* root) {
    if (!root) return;
    swap(root->left, root->right);
    fun(root->left);
    fun(root->right);
}
```

**Complexity:** Time `O(n)`, Space `O(h)`

---

## 5. LCA — Binary Tree (LeetCode 236)

**Intuition (boss analogy):**
Ask every node: *"How many of P and Q do you manage?"* (answer: 0, 1, or 2).
The **first node** that answers 2 is the LCA (Lowest Common Ancestor).

- Each node asks its left child, then its right child
- Adds 1 to itself if it equals P or Q (every node is its own boss)
- `total = left + self + right`
- First time `total == 2` → that node is the LCA

```cpp
Node* answer = NULL;

int fun(Node* node, Node* p, Node* q) {
    if (!node) return 0;
    int left  = fun(node->left,  p, q);
    int right = fun(node->right, p, q);
    int self  = (node == p || node == q) ? 1 : 0;
    int total = left + right + self;
    if (total == 2 && answer == NULL)
        answer = node;
    return total;
}
```

**Complexity:** Time `O(n)`, Space `O(h)`

---

## 6. Binary Search Tree (BST)

**Concept:** Like a sorted array but in tree form.
- Left child `<` parent `<` right child *(for every node, not just direct children)*

**Key property:** Inorder traversal of any BST gives a **sorted array**.

### BST Search (LeetCode 700)

**Intuition:** Exactly like binary search on a sorted array — at each node, go left if target is smaller, right if larger. Never explore both sides.

```cpp
Node* answer = NULL;

void fun(Node* root, int k) {
    if (!root) return;
    if (root->data == k) { answer = root; return; }
    if (root->data > k)  fun(root->left,  k);
    else                 fun(root->right, k);
}
```

**Complexity:**
- Time:  `O(log n)` average, `O(n)` worst (skewed tree)
- Space: `O(h)`

---

## 7. LCA — BST (LeetCode 235)

**Intuition:** The LCA is the **split point** — the node where P goes left and Q goes right (or the node equals P or Q itself).

- root == P or Q → root is LCA
- Both P and Q are greater than root → go right
- Both P and Q are smaller than root → go left
- P ≤ root ≤ Q → root is the split point → **LCA found**

```cpp
Node* answer = NULL;

void fun(Node* root, Node* p, Node* q) {
    if (!root) return;
    if (root == p || root == q) { answer = root; return; }
    if      (root->data < p->data) fun(root->right, p, q);
    else if (root->data > q->data) fun(root->left,  p, q);
    else { answer = root; return; }  // split point
}

Node* lcaBST(Node* root, Node* p, Node* q) {
    if (p->data > q->data) swap(p, q);  // ensure p < q
    fun(root, p, q);
    return answer;
}
```

**Complexity:** Time `O(log n)` average, Space `O(h)`

---

## 8. Path Sum Problems

### Path Sum I (LeetCode 112)

**Intuition:** Carry a running `sum` from root down to every leaf. At a leaf node, check if `sum == target`.

```cpp
bool result = false;

void fun(Node* root, int sum, int target) {
    if (!root) return;
    sum += root->data;
    if (!root->left && !root->right) {   // leaf node
        if (sum == target) result = true;
        return;
    }
    fun(root->left,  sum, target);
    fun(root->right, sum, target);
}
```

**Complexity:** Time `O(n)`, Space `O(h)`

---

### Path Sum II (LeetCode 113)

**Intuition:** Same as Path Sum I, but carry a `diary` (vector) recording the current path. At each leaf, if sum matches, save the diary to results. **Before returning, pop the last entry** (backtracking — undo your choice).

```cpp
vector<vector<int>> result;

void fun(Node* root, int sum, int target, vector<int>& diary) {
    if (!root) return;
    sum += root->data;
    diary.push_back(root->data);          // write in diary
    if (!root->left && !root->right) {
        if (sum == target) result.push_back(diary);
        diary.pop_back();                 // erase before returning
        return;
    }
    fun(root->left,  sum, target, diary);
    fun(root->right, sum, target, diary);
    diary.pop_back();                     // erase before returning
}
```

**Complexity:** Time `O(n²)` worst case (copying paths), Space `O(n · h)`

---

### Sum of Root-to-Leaf Numbers (LeetCode 129)

**Intuition:** Build a number digit by digit as you go down: `sum = sum * 10 + node->data`. At each leaf, add the formed number to the result total.

```cpp
int result = 0;

void fun(Node* root, int sum) {
    if (!root) return;
    sum = sum * 10 + root->data;
    if (!root->left && !root->right) { result += sum; return; }
    fun(root->left,  sum);
    fun(root->right, sum);
}
```

**Complexity:** Time `O(n)`, Space `O(h)`

---

## 9. Diameter of Binary Tree (LeetCode 543)

**Intuition:** Any path in a tree has a **turning point** (like a mountain peak). The diameter through any node = `height(left subtree) + height(right subtree)`. Track the maximum across all nodes while computing heights.

```cpp
int result = 0;

int fun(Node* root) {
    if (!root) return 0;
    int left  = fun(root->left);
    int right = fun(root->right);
    int sum   = left + right;          // diameter through this node
    result    = max(result, sum);
    return 1 + max(left, right);       // height returned upward
}
```

**Complexity:** Time `O(n)`, Space `O(h)`

---

## 10. Complete Binary Tree Check (LeetCode 958)

**Definition:**
- Every level except possibly the last is completely filled
- The last level is filled **left to right** (no gaps between filled nodes)

**Intuition:** Do a level-order traversal **including nulls**. Once you see a null node, set `nullFound = true`. If you later see a non-null node, the tree is **NOT** complete.

```cpp
bool isComplete(Node* root) {
    if (!root) return true;
    queue<Node*> q;
    q.push(root);
    bool nullFound = false;
    while (!q.empty()) {
        Node* t = q.front(); q.pop();
        if (!t) {
            nullFound = true;
        } else {
            if (nullFound) return false;  // non-null after a null → invalid
            q.push(t->left);             // push even if null
            q.push(t->right);
        }
    }
    return true;
}
```

**Complexity:** Time `O(n)`, Space `O(n)`

---

## 11. Validate BST (LeetCode 98)

**Intuition:** Inorder of a valid BST is a sorted array. Use a `prev` pointer — during inorder traversal, each node must be strictly greater than the previous node visited.

```cpp
Node* prev = NULL;
bool answer = true;

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    if (prev && root->data <= prev->data)
        answer = false;
    prev = root;
    inorder(root->right);
}
```

**Complexity:** Time `O(n)`, Space `O(h)`

---

## 12. Recover BST (LeetCode 99)

**Intuition:** In a valid BST's inorder, exactly two elements are swapped. In the resulting broken sequence there are either **1 or 2 violation points** (places where an element is greater than the next).

- **2 violations:** Swap `wrong1_first` with `wrong2_second`
- **1 violation (adjacent swap):** Swap `wrong1_first` with `wrong1_second`

Apply during inorder using a `prev` pointer (no extra array needed):

```cpp
Node* prev = NULL;
int wrong = 0;
Node *g1f, *g1s, *g2f, *g2s;

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    if (prev && root->data <= prev->data) {
        if (wrong == 0) { g1f = prev; g1s = root; }
        else            { g2f = prev; g2s = root; }
        wrong++;
    }
    prev = root;
    inorder(root->right);
}

void recoverTree(Node* root) {
    inorder(root);
    if (wrong == 1) swap(g1f->data, g1s->data);
    else            swap(g1f->data, g2s->data);
}
```

**Complexity:** Time `O(n)`, Space `O(h)`

---

## 13. Construct Tree from Preorder + Inorder (LeetCode 105)

**Why two arrays?** Preorder alone has many possible trees. Preorder + Inorder together give a **unique** tree.

**Intuition:**
- Preorder's first element is always the **root**
- Find that root in inorder — everything to its left is the **left subtree**, everything to its right is the **right subtree**
- Recurse for each subtree

**Trick:** Build a hashmap of `value → index` for inorder so lookup is `O(1)`.

```cpp
unordered_map<int,int> inMap;
int idx = 0;

Node* fun(vector<int>& pre, int lo, int hi) {
    if (lo > hi) return NULL;                    // base case: empty range

    Node* node = new Node(pre[idx++]);           // build root from preorder
    int id = inMap[node->data];                  // find root's position in inorder

    node->left  = fun(pre, lo,    id - 1);      // left subtree
    node->right = fun(pre, id + 1, hi);          // right subtree
    return node;
}

Node* buildTree(vector<int>& pre, vector<int>& in) {
    for (int i = 0; i < (int)in.size(); i++)
        inMap[in[i]] = i;
    return fun(pre, 0, (int)in.size() - 1);
}
```

**Complexity:** Time `O(n)`, Space `O(n)` for hashmap + `O(h)` recursion stack

---

## Quick Reference: All Complexities

| Topic | LeetCode | Time | Space |
|-------|----------|------|-------|
| Inorder / Preorder / Postorder | 94, 144, 145 | O(n) | O(h) |
| Level Order Traversal | 102 | O(n) | O(n) |
| Zigzag Level Order | 103 | O(n) | O(n) |
| Same Tree | 100 | O(n) | O(h) |
| Symmetric Tree | 101 | O(n) | O(h) |
| Invert Tree | 226 | O(n) | O(h) |
| LCA — Binary Tree | 236 | O(n) | O(h) |
| BST Search | 700 | O(log n) avg | O(h) |
| LCA — BST | 235 | O(log n) avg | O(h) |
| Path Sum I | 112 | O(n) | O(h) |
| Path Sum II | 113 | O(n²) worst | O(n·h) |
| Sum Root-to-Leaf Numbers | 129 | O(n) | O(h) |
| Diameter | 543 | O(n) | O(h) |
| Complete Binary Tree Check | 958 | O(n) | O(n) |
| Validate BST | 98 | O(n) | O(h) |
| Recover BST | 99 | O(n) | O(h) |
| Build Tree (Preorder + Inorder) | 105 | O(n) | O(n) |

> **Note:** `h` = height of tree. Balanced tree → `h = log n`. Skewed tree → `h = n`.