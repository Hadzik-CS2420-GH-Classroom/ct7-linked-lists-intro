#include "SinglyLinkedList.h"

#include <format>
#include <iostream>
#include <stdexcept>

// --- Destructor ---

// ! DISCUSSION: Why do we need a destructor at all?
//   - Each node was created with 'new', which allocates memory on the heap
//   - If we don't 'delete' every node, that memory leaks — reserved but never freed
//   - The destructor traverses the chain and deletes each node one by one
//
// ! DISCUSSION: "Why not just delete head_ and be done?"
//   - 'delete head_' only frees the FIRST node
//   - The rest of the chain is still out there, unreachable and leaked
//   - We must follow the next pointers and delete each node individually
//
// ? SEE DIAGRAM: images/destructor_walk.png — traversing the chain, deleting each node

SinglyLinkedList::~SinglyLinkedList() {
    while (head_) {
        // ! DISCUSSION: "Why do we need a temp pointer?"
        //   - We need to save head_ BEFORE we move it forward
        //   - If we do head_ = head_->next first, we lose the only
        //     pointer to the current node and can never delete it
        //   - Order matters: save → advance → delete

        // TODO: Save the current head_ into a temp pointer

        // TODO: Advance head_ to the next node

        // TODO: Delete the temp pointer (frees the old head node)

    }
}

// --- Insertion ---

// ? SEE DIAGRAM: images/push_front.png — shows new node's next pointing to old head, then head moving

void SinglyLinkedList::push_front(int value) {
    // ! DISCUSSION: This is the beauty of push_front — it's always O(1).
    //   No matter how long the list is, we just:
    //   - Create a new node whose 'next' points to the current head
    //   - Update head to point to the new node
    //   - Compare to an array: inserting at the front means shifting
    //     EVERY element one slot to the right — O(n)

    // TODO: Create a new Node with 'value' and whose next points to head_,
    //       then update head_ to point to the new node.

    // TODO: Increment size_

}

// ? SEE DIAGRAM: images/push_back.png — shows traversing to the last node, then linking the new node

void SinglyLinkedList::push_back(int value) {
    // TODO: Create a new Node with 'value' (next defaults to nullptr)


    if (!head_) {
        // ! DISCUSSION: Empty list is a special case.
        //   - There's no existing node to attach to
        //   - The new node simply becomes the head

        // TODO: Set head_ to the new node

    } else {
        // ! DISCUSSION: We must traverse to the END of the list to find the last node.
        //   - This makes push_back O(n) — the longer the list, the longer the traversal
        //   - Key tradeoff vs arrays, where appending to the end is O(1) (if there's capacity)
        //   - We could fix this by keeping a 'tail' pointer, but that adds
        //     complexity we'll explore later

        // TODO: Create a 'current' pointer starting at head_

        // TODO: Traverse to the last node (while current->next is not nullptr)

        // TODO: Link the new node to the end of the list

    }

    // TODO: Increment size_

}

// --- Removal ---

// ? SEE DIAGRAM: images/pop_front.png — shows saving head, advancing head, deleting old head

void SinglyLinkedList::pop_front() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    // ! DISCUSSION: Same temp-pointer pattern as the destructor.
    //   - Save the current head, advance head to the next node, then delete the old head
    //   - This is O(1) — no matter the list size, we only touch one node
    //
    // ! DISCUSSION: "What happens to the data in the deleted node?"
    //   - It's gone — if the caller needed that value, they should have
    //     read it before calling pop_front()
    //   - Some implementations return the value, but the STL convention
    //     (std::stack::pop, std::queue::pop) is to return void
    //   - Provide a separate top()/front() method to peek first

    // TODO: Save head_ into a temp pointer

    // TODO: Advance head_ to the next node

    // TODO: Delete the temp pointer

    // TODO: Decrement size_

}

// ? SEE DIAGRAM: images/pop_back.png — shows trailing pointer pattern to find and remove the last node

void SinglyLinkedList::pop_back() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    // ! DISCUSSION: Special case — only one node in the list.
    //   - If head_->next is nullptr, the head IS the tail
    //   - Just delete it and set head_ to nullptr — no traversal needed
    if (!head_->next) {
        // TODO: Delete head_ and set it to nullptr, then decrement size_

        return;
    }

    // ! DISCUSSION: The "trailing pointer" pattern.
    //   - We need TWO pointers: 'current' advances through the list,
    //     'previous' trails one node behind
    //   - When current reaches the last node, previous points to the second-to-last —
    //     exactly the node whose 'next' we need to set to nullptr
    //   - Why one pointer isn't enough: singly linked nodes don't know who points TO them —
    //     no way to go BACKWARDS, so the trailing pointer tracks where we came from
    //
    // ! DISCUSSION: This makes pop_back O(n).
    //   - We must traverse the entire list to find the second-to-last node
    //   - Compare to pop_front which is O(1)
    //   - A doubly linked list fixes this by giving each node a 'prev' pointer

    // TODO: Create 'previous' pointing to head_, and 'current' pointing to head_->next

    // TODO: While current->next is not nullptr:
    //         Advance previous to current
    //         Advance current to current->next

    // ! DISCUSSION: Now 'current' is the last node, 'previous' is the second-to-last.
    //   Unlink and delete:
    //   - Set previous->next to nullptr (it's now the new tail)
    //   - Delete current (free the old tail's memory)

    // TODO: Set previous->next to nullptr

    // TODO: Delete current

    // TODO: Decrement size_

}

// --- Getters ---

int SinglyLinkedList::get_size() const noexcept { return size_; }
bool SinglyLinkedList::is_empty() const noexcept { return size_ == 0; }

// --- Utility ---

void SinglyLinkedList::print() const {
    // ! DISCUSSION: Printing by traversing the list.
    //   - Use a 'current' pointer that starts at head and follows
    //     next pointers until it hits nullptr (end of list)
    //   - This is the fundamental traversal pattern for linked lists —
    //     you'll see it again in search and remove operations (CT8)

    Node* current = head_;

    while (current) {
        std::cout << std::format("{} -> ", current->data);
        current = current->next;
    }

    std::cout << "nullptr\n";
}
