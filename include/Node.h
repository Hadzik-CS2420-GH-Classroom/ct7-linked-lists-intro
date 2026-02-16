#pragma once

// ! DISCUSSION: What is a node?
//   A node is the building block of a linked list. Unlike an array,
//   where elements sit side-by-side in memory, each node lives
//   wherever the OS finds space. The 'next' pointer is what chains
//   them together — it stores the ADDRESS of the next node.
//
// ? SEE DIAGRAM: images/svgs/node_vs_array.svg — array (contiguous) vs nodes (scattered, pointer-linked)
//
// ! DISCUSSION: "Why a struct and not a class?"
//   A struct is just a class where everything is public by default.
//   Nodes are simple data holders — there's no behavior to hide.
//   Using struct signals "this is just plain data" to anyone reading
//   the code. The linked list class will manage the nodes; the node
//   itself doesn't need to protect anything.

struct Node {
    int data;
    Node* next;

    // ! DISCUSSION: "What does 'Node* next = nullptr' mean?"
    //   The '= nullptr' is a default argument. If we create a node
    //   without specifying a next pointer, it defaults to nullptr
    //   (points to nothing). This is handy for creating the last
    //   node in a list, or a brand-new standalone node.
    Node(int value, Node* next = nullptr)
        : data{value}, next{next} {}
};
