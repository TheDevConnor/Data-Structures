# Data Structures

A collection of C++ data structure implementations and practice exercises.

## Project Structure

```
├── Project_1/          Stack-based calculator (infix → postfix → evaluation)
├── week_1/             Linked lists (singly & doubly linked)
├── week_2/             Stacks & Queues (array & linked-list based)
├── week_3/             Recursion & balanced parentheses
├── week_4-6/           (future topics)
├── trees/              Tree data structures (binary tree, BST)
└── docs/               Notes and resources
```

## Topics Covered

| Topic | Folder | Files |
|---|---|---|
| Singly Linked List | `week_1/` | `linked_list.cpp`, `SLL_draft/` |
| Doubly Linked List | `week_1/` | `double_linked_list.cpp` |
| Stack (Array) | `week_2/Stacks/` | `stack_array.cpp` |
| Stack (Linked List) | `week_2/Stacks/` | `stack_ll.cpp` |
| Queue (Array) | `week_2/Queue_array/` | `Queue.h`, `Queue.cpp`, `testQueue.cpp` |
| Queue (Linked List) | `week_2/Queue_LL/` | `Queues_LL_Implementation.cpp` |
| Train Station Queue | `week_2/Train_Station_Queue_Exercise/` | `main.cpp` |
| Balanced Parentheses | `week_3/` | `balanced_stack.cpp` |
| Recursion | `week_3/` | `recursion.cpp` |
| Stack Calculator | `Project_1/` | `calculator.cpp` |
| Binary Tree | `trees/` | `binary_tree.cpp`, `bst.cpp` |

## Building & Running

Compile any file with g++:

```bash
g++ -o output_file source_file.cpp
./output_file
```

## Build Notes

- `.gitignore` ignores `*.exe` and any binary named `main`
- Compiled binaries in source directories are tracked — run `git clean` or add to `.gitignore` to remove
