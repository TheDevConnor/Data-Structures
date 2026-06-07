# Data Structures Notes

## Linked Lists

### Singly Linked List
- Each node contains data and a pointer to the next node.
- Operations: `push_front`, `push_back`, `pop_front`, `pop_back`, `print`.
- Traversal is O(n); insertion at head is O(1).

### Doubly Linked List
- Each node has `next` and `prev` pointers.
- Allows O(1) deletion from both ends and reverse traversal.
- More memory overhead per node (extra pointer).

## Stacks (LIFO)

### Array-based
- Fixed capacity, O(1) push/pop, simple implementation.
- Risk of stack overflow if capacity is exceeded.

### Linked-list based
- Dynamic size, no overflow (until heap exhaustion).
- Slightly more overhead per element.

## Queues (FIFO)

### Circular Array Queue
- Reuses array slots via modulo arithmetic (`frnt = (frnt + 1) % capacity`).
- O(1) enqueue/dequeue, fixed capacity.

### Linked List Queue
- `front` pointer for dequeue, `rear` pointer for enqueue.
- Dynamic size, O(1) operations.

## Expression Evaluation

### Infix → Postfix (Shunting Yard)
1. Operands go directly to output.
2. Operators pushed to stack after popping higher/equal precedence operators.
3. Left-associative: pop equal precedence. Right-associative (`^`): don't pop equal.
4. Parentheses: `(` pushed, `)` pops until `(`.

### Postfix Evaluation
- Push operands; on operator, pop two operands, apply, push result.

## Recursion

- Base case + recursive step.
- Stack memory: each call adds a frame; deep recursion risks stack overflow.
- Examples: string reversal, exponentiation, summation.

## Trees

### Binary Tree
- Each node has at most two children: `left` and `right`.
- Traversals: preorder (root→left→right), inorder (left→root→right), postorder (left→right→root).

### Binary Search Tree (BST)
- BST property: left subtree < node ≤ right subtree.
- Search, insert: O(h) where h = height (worst O(n), best O(log n)).
- Inorder traversal yields sorted order.
