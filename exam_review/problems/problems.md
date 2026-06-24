# COP3415 — Final Exam Practice Problems
**Exam:** Wednesday, June 24, 2026 at 9 AM — IST 1065 | 90 min | 100 pts

---

## Problem 1 — BSTs & Traversals

**Insert the following values into an empty BST in order:**
`15, 10, 20, 8, 12, 17, 25`

Then write a **recursive function** that returns the **sum of all leaf nodes**.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = val; n->left = n->right = NULL;
    return n;
}

Node* insert(Node* root, int key) {
    // YOUR CODE HERE
}

int sumLeaves(Node* root) {
    // YOUR CODE HERE
}

int main() {
    Node* root = NULL;
    int vals[] = {15, 10, 20, 8, 12, 17, 25};
    for (int i = 0; i < 7; i++) root = insert(root, vals[i]);
    printf("Sum of leaves: %d\n", sumLeaves(root)); // What should this print?
    return 0;
}
```

**Your Answer (sum of leaves):** 62

---

## Problem 2 — AVL Trees & Rotations

**Trace through inserting these values one by one into an empty AVL tree:**
`30, 20, 10`

For each insertion: draw the tree, compute balance factors, identify which rotation case fires, and draw the result after rotation.

```c
typedef struct AVLNode {
    int data, height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

int height(AVLNode* n) { return n ? n->height : 0; }
int max(int a, int b)  { return a > b ? a : b; }
int getBalance(AVLNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

AVLNode* rightRotate(AVLNode* z) {
    // YOUR CODE HERE
}

AVLNode* leftRotate(AVLNode* z) {
    // YOUR CODE HERE
}

AVLNode* insert(AVLNode* root, int key) {
    // YOUR CODE HERE — handle all 4 rotation cases
}
```

**Written question:** After inserting `30 → 20 → 10`, what is the root of the final AVL tree and why?

**Your Answer:** ___

---

## Problem 3 — Heaps & Heap Sort

**Given the array:** `[4, 10, 3, 5, 1]`

- Step 1 — Manually build a **Max-Heap** (show each heapify step)
- Step 2 — Run **Heap Sort** and show the array after each extraction
- Step 3 — Implement `heapSort` below

```c
#include <stdio.h>

void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }

void maxHeapify(int arr[], int n, int i) {
    // YOUR CODE HERE
}

void heapSort(int arr[], int n) {
    // Step 1: Build max heap
    // YOUR CODE HERE

    // Step 2: Extract elements one by one
    // YOUR CODE HERE
}

int main() {
    int arr[] = {4, 10, 3, 5, 1};
    int n = 5;
    heapSort(arr, n);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    return 0;
}
```

**Bonus:** What is the time complexity of build-heap alone, and why is it O(n) and not O(n log n)?
Because we have to iterate through each index of the array so it is O(n) where n is the length of the array.

**Your Answer:** 1 3 4 5 10

---

## Problem 4 — Graph BFS / DFS

**Given this adjacency list (undirected graph):**
```
0 → [1, 2]
1 → [0, 3, 4]
2 → [0, 4]
3 → [1]
4 → [1, 2]
```

Manually write the **BFS** and **DFS** traversal orders starting from vertex `0`, then implement both.

```c
#include <stdio.h>
#include <stdbool.h>
#define V 5

int graph[V][V] = {
    {0,1,1,0,0},
    {1,0,0,1,1},
    {1,0,0,0,1},
    {0,1,0,0,0},
    {0,1,1,0,0}
};

// --- BFS ---
void BFS(int start) {
    bool visited[V] = {false};
    int queue[V], front = 0, rear = 0;
    // YOUR CODE HERE
}

// --- DFS ---
void DFS(int v, bool visited[]) {
    // YOUR CODE HERE
}

int main() {
    printf("BFS: "); BFS(0);
    bool visited[V] = {false};
    printf("\nDFS: "); DFS(0, visited);
    return 0;
}
```

**Written question:** What is one scenario where you'd choose BFS over DFS and why?

**Your BFS order:** 
``BFS: 0 1 2 3 4`` 
**Your DFS order:**
``DFS: 0 1 3 4 2``
**Your Answer (written):** I am not sure. Maybe depth would be better if you needed someting quick while breath 
is more reliable but takes longer

---

## Problem 5 — Hash Tables

**Insert the following keys into a hash table of size 7 using:**
`h(k) = k mod 7` and **linear probing** for collisions.

Keys to insert in order: `10, 20, 35, 14, 21`

Manually draw the table after each insertion, marking which slots are probed.

```c
#include <stdio.h>
#define SIZE 7
#define EMPTY -1
#define DELETED -2

int table[SIZE];

void initTable() {
    for (int i = 0; i < SIZE; i++) table[i] = EMPTY;
}

int hash(int key) { return key % SIZE; }

void insert(int key) {
    // YOUR CODE HERE — linear probing
}

int search(int key) {
    // YOUR CODE HERE — return index or -1 if not found
}

void printTable() {
    for (int i = 0; i < SIZE; i++)
        printf("[%d]: %d\n", i, table[i]);
}

int main() {
    initTable();
    int keys[] = {10, 20, 35, 14, 21};
    for (int i = 0; i < 5; i++) insert(keys[i]);
    printTable();
    printf("Search 14: index %d\n", search(14));
    return 0;
}
```

**Written question:** What happens to `search` performance as the load factor approaches 1.0 with linear probing, and why?

**Your table (draw it):**
```
[0]: 
[1]: 
[2]: 
[3]: 
[4]: 
[5]: 
[6]: 
```
**Your Answer (written):**
```
[0]: 35
[1]: 14
[2]: 21
[3]: 10
[4]: -1
[5]: -1
[6]: 20
Search 14: index 1
```
---

## Problem 6 — Tries

**Insert these words into a Trie:** `"can", "cat", "car", "card"`

Manually draw the trie after all insertions — mark which nodes are end-of-word.

Then implement a function that **counts how many words in the trie start with a given prefix:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ALPHA 26

typedef struct TrieNode {
    struct TrieNode* children[ALPHA];
    bool isEnd;
} TrieNode;

TrieNode* newNode() {
    TrieNode* n = (TrieNode*)calloc(1, sizeof(TrieNode));
    n->isEnd = false;
    return n;
}

void insert(TrieNode* root, char* word) {
    // YOUR CODE HERE
}

// Returns the node at end of prefix, or NULL if prefix doesn't exist
TrieNode* findPrefix(TrieNode* root, char* prefix) {
    // YOUR CODE HERE
}

// Count all words in subtree rooted at node
int countWords(TrieNode* node) {
    // YOUR CODE HERE
}

int countWithPrefix(TrieNode* root, char* prefix) {
    TrieNode* node = findPrefix(root, prefix);
    return node ? countWords(node) : 0;
}

int main() {
    TrieNode* root = newNode();
    char* words[] = {"can", "cat", "car", "card"};
    for (int i = 0; i < 4; i++) insert(root, words[i]);

    printf("Words with prefix 'ca':  %d\n", countWithPrefix(root, "ca"));   // expected: 4
    printf("Words with prefix 'car': %d\n", countWithPrefix(root, "car"));  // expected: 2
    printf("Words with prefix 'dog': %d\n", countWithPrefix(root, "dog"));  // expected: 0
    return 0;
}
```

**Your Answer (expected outputs):** ___

---

## Problem 7 — AVL Rotations: LL Case (Single Right Rotation)

**Insert in order:** `50, 30, 10`

Manually trace:
- Draw the tree after each insertion
- Compute the balance factor at each node after inserting `10`
- Identify which node is **unbalanced**, which case it is, and perform the rotation

```c
AVLNode* rightRotate(AVLNode* z) {
    AVLNode* y  = z->left;
    AVLNode* T3 = y->right;

    // Perform rotation
    y->right = z;
    z->left  = T3;

    // Update heights — ALWAYS update z first, then y
    z->height = max(height(z->left), height(z->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // new root
}

AVLNode* insert(AVLNode* root, int key) {
    // Step 1: Normal BST insert
    if (!root) return newAVLNode(key);
    if (key < root->data)      root->left  = insert(root->left,  key);
    else if (key > root->data) root->right = insert(root->right, key);
    else return root;

    // Step 2: Update height
    root->height = max(height(root->left), height(root->right)) + 1;

    // Step 3: Get balance factor
    int balance = getBalance(root);

    // YOUR CODE HERE — detect LL case and return rightRotate
}
```

**Written:** After the rotation, what are the balance factors of all nodes in the final tree?

**Your Answer:**
```
Before rotation (draw tree):


After rotation (draw tree):


Balance factors: root=___ left=___ right=___
```

---

## Problem 8 — AVL Rotations: LR Case (Double Rotation)

**Insert in order:** `50, 30, 40`

Manually trace:
- Draw tree after inserting `40`
- Show balance factors — which node is unbalanced?
- Draw the tree **after the left rotation on node 30**
- Draw the tree **after the right rotation on node 50**

```c
AVLNode* insert(AVLNode* root, int key) {
    if (!root) return newAVLNode(key);
    if (key < root->data)      root->left  = insert(root->left,  key);
    else if (key > root->data) root->right = insert(root->right, key);
    else return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance  = getBalance(root);

    // LL Case
    if (balance > 1 && key < root->left->data)
        return rightRotate(root);

    // RR Case
    if (balance < -1 && key > root->right->data)
        return leftRotate(root);

    // LR Case — YOUR CODE HERE
    // Hint: left rotate the left child FIRST, then right rotate root

    // RL Case — YOUR CODE HERE
    // Hint: right rotate the right child FIRST, then left rotate root

    return root;
}
```

**Written:** Why does the LR case require TWO rotations instead of one?

**Your Answer:**
```
After insert 40 (draw tree):


After left rotate on 30 (draw tree):


After right rotate on 50 (draw tree):


Written answer: 
```

---

## Problem 9 — AVL Rotations: Mixed (Exam-Style)

**Insert ALL of the following into an empty AVL tree in order:**
`10, 20, 30, 40, 50, 25`

For each insertion that triggers a rotation:
- State which node became unbalanced
- State which case it is (LL / RR / LR / RL)
- Draw the tree before and after the rotation

Then implement the **full** insert with all 4 cases handled:

```c
AVLNode* insert(AVLNode* root, int key) {
    // Step 1: BST insert
    if (!root) return newAVLNode(key);
    if (key < root->data)      root->left  = insert(root->left,  key);
    else if (key > root->data) root->right = insert(root->right, key);
    else return root;

    // Step 2: Update height
    root->height = max(height(root->left), height(root->right)) + 1;

    // Step 3: Balance factor
    int balance = getBalance(root);

    // YOUR CODE HERE — all 4 cases:
    // LL:  balance > 1  && key < root->left->data
    // RR:  balance < -1 && key > root->right->data
    // LR:  balance > 1  && key > root->left->data
    // RL:  balance < -1 && key < root->right->data

    return root;
}

int main() {
    AVLNode* root = NULL;
    int vals[] = {10, 20, 30, 40, 50, 25};
    for (int i = 0; i < 6; i++) root = insert(root, vals[i]);
    printf("Root: %d\n", root->data);
    return 0;
}
```

**Written questions:**
1. How many rotations total happen during these 6 insertions?
2. What is the final root of the AVL tree?
3. What is the height of the final tree?

**Your Answer:**
```
Rotation log:
  Insert 10: no rotation
  Insert 20: no rotation
  Insert 30: unbalanced node=___ case=___ 
  Insert 40: unbalanced node=___ case=___
  Insert 50: unbalanced node=___ case=___
  Insert 25: unbalanced node=___ case=___

Total rotations: ___
Final root:      ___
Final height:    ___

Final tree (draw it):
```

---

## Answer Key Hints (check AFTER solving)

| Problem | Key Value to Verify |
|---------|---------------------|
| 1 | Sum of leaves = 8 + 12 + 17 + 25 = ? |
| 2 | Root after LL rotation on `30,20,10` = 20 |
| 3 | Sorted output = `1 3 4 5 10` |
| 4 | BFS: 0,1,2,3,4 — DFS: 0,1,3,4,2 |
| 5 | Key 35 → slot 0; collision for 14 at slot 0 → probes to slot 1 |
| 6 | 'ca'=4, 'car'=2, 'dog'=0 |
| 7 | New root=30, BF: root=0, left=0, right=0 |
| 8 | New root=40 after double rotation |
| 9 | 3 rotations total; final root=30; height=3 |
