#include "SinglyLinkedList.h"

#include <format>
#include <iostream>
#include <stdexcept>

// --- Destructor ---

// ! DISCUSSION: Why do we need a destructor at all?
//   Each node was created with 'new', which allocates memory on the
//   heap. If we don't 'delete' every node, that memory leaks — it's
//   reserved but never freed, even after our list object is gone.
//   The destructor traverses the chain and deletes each node one by one.
//
// ! DISCUSSION: "Why not just delete head_ and be done?"
//   'delete head_' only frees the FIRST node. The rest of the chain
//   is still out there, unreachable and leaked. We must follow the
//   next pointers and delete each node individually.
//
// ? SEE DIAGRAM: images/svgs/destructor_walk.svg — traversing the chain, deleting each node

SinglyLinkedList::~SinglyLinkedList() {
    while (head_) {
        // ! DISCUSSION: "Why do we need a temp pointer?"
        //   We need to save head_ BEFORE we move it forward.
        //   If we do head_ = head_->next first, we lose the only
        //   pointer to the current node and can never delete it.
        //   Order matters: save → advance → delete.
        auto* temp = head_;
        head_ = head_->next;
        delete temp;
    }
}

// --- Insertion ---

// ? SEE DIAGRAM: images/svgs/push_front.svg — shows new node's next pointing to old head, then head moving

void SinglyLinkedList::push_front(int value) {
    // ! DISCUSSION: This is the beauty of push_front — it's always O(1).
    //   No matter how long the list is, we just:
    //     1. Create a new node whose 'next' points to the current head
    //     2. Update head to point to the new node
    //   Compare this to an array: inserting at the front means shifting
    //   EVERY element one slot to the right — O(n).
    head_ = new Node{value, head_};
    ++size_;
}

// ? SEE DIAGRAM: images/svgs/push_back.svg — shows traversing to the last node, then linking the new node

void SinglyLinkedList::push_back(int value) {
    auto* newNode = new Node{value};

    if (!head_) {
        // ! DISCUSSION: Empty list is a special case.
        //   There's no existing node to attach to, so the new node
        //   simply becomes the head.
        head_ = newNode;
    } else {
        // ! DISCUSSION: We must traverse to the END of the list to find the
        //   last node. This makes push_back O(n) — the longer the list,
        //   the longer the traversal. This is a key tradeoff vs arrays, where
        //   appending to the end is O(1) (if there's capacity).
        //   We could fix this by keeping a 'tail' pointer, but that adds
        //   complexity we'll explore later.
        auto* current = head_;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    ++size_;
}

// --- Removal ---

// ? SEE DIAGRAM: images/svgs/pop_front.svg — shows saving head, advancing head, deleting old head

void SinglyLinkedList::pop_front() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    // ! DISCUSSION: Same temp-pointer pattern as the destructor.
    //   Save the current head, advance head to the next node, then
    //   delete the old head. This is O(1) — no matter the list size,
    //   we only touch one node.
    //
    // ! DISCUSSION: "What happens to the data in the deleted node?"
    //   It's gone. If the caller needed that value, they should have
    //   read it before calling pop_front(). Some implementations
    //   return the value, but the STL convention (std::stack::pop,
    //   std::queue::pop) is to return void and provide a separate
    //   top()/front() method to peek first.
    auto* temp = head_;
    head_ = head_->next;
    delete temp;
    --size_;
}

// --- Getters ---

int SinglyLinkedList::get_size() const noexcept { return size_; }
bool SinglyLinkedList::is_empty() const noexcept { return size_ == 0; }

// --- Utility ---

void SinglyLinkedList::print() const {
    // ! DISCUSSION: Printing by traversing the list.
    //   We use a 'current' pointer that starts at head and follows
    //   the next pointers until it hits nullptr (end of list).
    //   This is the fundamental traversal pattern for linked lists —
    //   you'll see it in search, remove, and every other operation.
    auto* current = head_;
    while (current) {
        std::cout << std::format("{} -> ", current->data);
        current = current->next;
    }
    std::cout << "nullptr\n";
}
