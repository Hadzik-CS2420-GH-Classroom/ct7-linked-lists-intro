# CT7 -- Singly Linked List Introduction

## Overview

An in-class code-together activity introducing singly linked lists through a hands-on ice cream shop queue simulation. Students implement core linked list operations (insert, remove, traverse) by completing TODO items while the instructor walks through concepts using discussion comments and SVG diagrams.

## Files

| File | Focus | TODOs |
|---|---|---|
| `SinglyLinkedList.cpp` | Node-based list operations: destructor, push/pop front & back, print traversal | 23 |
| `main.cpp` | Farr's Ice Cream ticket queue scenario exercising all operations | 9 |

## Supporting Files

| File | Purpose |
|---|---|
| `Node.h` | Simple `Node` struct (`int data`, `Node* next`) with a two-parameter constructor |
| `SinglyLinkedList.h` | Class declaration with Rule of 5 (all deleted), public interface, `head_`/`size_` members |

## Teaching Order

Work through `SinglyLinkedList.cpp` in the order `main.cpp` calls the operations:

### 1. Destructor -- Why Manual Cleanup Matters

- Why `delete head_` alone leaks the rest of the chain
- The **temp pointer pattern**: save, advance, delete
- Traversal loop: `while (head_)`

### 2. `push_back` -- Customers Join the Line

- Creating a new node on the heap
- Empty list special case (new node becomes head)
- Traversal to the last node -- O(n) cost
- Comparison to arrays: appending is O(1) with capacity, but here it's O(n) without a tail pointer

### 3. `push_front` -- VIP Cuts to the Front

- One-liner: `head_ = new Node{value, head_}`
- Always O(1) -- no traversal needed
- Comparison to arrays: front insertion requires shifting everything -- O(n)

### 4. `pop_front` -- Serving the Next Customer

- Same temp pointer pattern as the destructor
- O(1) removal -- just move the head pointer
- Discussion: what happens to the deleted data? (STL convention: `pop` returns void)

### 5. `pop_back` -- Customer at the Back Gives Up

- Single-node special case (delete head, set to nullptr)
- The **trailing pointer pattern**: `previous` and `current` advance together
- Why one pointer isn't enough (singly linked = no backward references)
- O(n) cost vs O(1) for `pop_front` -- key weakness of singly linked lists
- Preview: doubly linked lists solve this with a `prev` pointer

### 6. `print` -- Traversing the List

- Fundamental traversal pattern: `current` starts at head, follows `next` until nullptr
- Same pattern reused in search, remove, and every other list operation

## Key Concepts

- **Singly linked list** vs array tradeoffs (O(1) front insert/remove vs O(1) random access)
- **Manual memory management**: `new`/`delete`, no smart pointers (teaching purposes)
- **Temp pointer pattern**: save before advancing to avoid losing the only reference to a node
- **Trailing pointer pattern**: two pointers for finding the second-to-last node
- **Rule of 5**: all special members explicitly deleted (copy/move constructors and assignments)
- **O(1) vs O(n)**: front operations are constant time; back operations require traversal

## Diagrams

SVG sources are in `images/svgs/`, PNG exports in `images/`.

| Diagram | Referenced In | Shows |
|---|---|---|
| `node_vs_array` | (supplemental) | Structural comparison of array contiguous memory vs linked node chain |
| `destructor_walk` | `SinglyLinkedList.cpp` | Traversing the chain with temp pointer, deleting each node |
| `push_front` | `SinglyLinkedList.cpp` | New node's next points to old head, then head moves to new node |
| `push_back` | `SinglyLinkedList.cpp` | Traversing to the last node, then linking the new node |
| `pop_front` | `SinglyLinkedList.cpp` | Save head into temp, advance head, delete temp |
| `pop_back` | `SinglyLinkedList.cpp` | Trailing pointer pattern: previous/current traversal, unlink and delete last node |

## Comment Conventions

Uses [Better Comments](https://marketplace.visualstudio.com/items?itemName=OmarRwemi.BetterComments) for VS 2022:

| Prefix | Color | Purpose |
|---|---|---|
| `// !` | Important (red) | `DISCUSSION:` teaching notes for instructor walkthrough |
| `// ?` | Question (blue) | `SEE DIAGRAM:` references to visual aids |
| `// TODO:` | Task (orange) | Student exercises (main branch) |
