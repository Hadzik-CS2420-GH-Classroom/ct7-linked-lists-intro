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

        // TODO: Save the current head_ into a temp pointer

        // TODO: Advance head_ to the next node

        // TODO: Delete the temp pointer (frees the old head node)

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

    // TODO: Create a new Node with 'value' and whose next points to head_,
    //       then update head_ to point to the new node.

    // TODO: Increment size_

}

// ? SEE DIAGRAM: images/svgs/push_back.svg — shows traversing to the last node, then linking the new node

void SinglyLinkedList::push_back(int value) {
    // TODO: Create a new Node with 'value' (next defaults to nullptr)


    if (!head_) {
        // ! DISCUSSION: Empty list is a special case.
        //   There's no existing node to attach to, so the new node
        //   simply becomes the head.

        // TODO: Set head_ to the new node

    } else {
        // ! DISCUSSION: We must traverse to the END of the list to find the
        //   last node. This makes push_back O(n) — the longer the list,
        //   the longer the traversal. This is a key tradeoff vs arrays, where
        //   appending to the end is O(1) (if there's capacity).
        //   We could fix this by keeping a 'tail' pointer, but that adds
        //   complexity we'll explore later.

        // TODO: Create a 'current' pointer starting at head_

        // TODO: Traverse to the last node (while current->next is not nullptr)

        // TODO: Link the new node to the end of the list

    }

    // TODO: Increment size_

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

    // TODO: Save head_ into a temp pointer

    // TODO: Advance head_ to the next node

    // TODO: Delete the temp pointer

    // TODO: Decrement size_

}

// ? SEE DIAGRAM: images/svgs/pop_back.svg — shows trailing pointer pattern to find and remove the last node

void SinglyLinkedList::pop_back() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    // ! DISCUSSION: Special case — only one node in the list.
    //   If head_->next is nullptr, the head IS the tail. Just delete
    //   it and set head_ to nullptr. No traversal needed.
    if (!head_->next) {
        // TODO: Delete head_ and set it to nullptr, then decrement size_

        return;
    }

    // ! DISCUSSION: The "trailing pointer" pattern.
    //   We need TWO pointers: 'current' advances through the list,
    //   and 'previous' trails one node behind. When current reaches
    //   the last node, previous is pointing to the second-to-last —
    //   which is exactly the node whose 'next' we need to set to nullptr.
    //
    //   Why can't we just use one pointer?
    //   Because singly linked list nodes don't know who points TO them.
    //   Once we find the last node, there's no way to go BACKWARDS to
    //   update the previous node's next pointer. The trailing pointer
    //   solves this by keeping track of where we came from.
    //
    // ! DISCUSSION: This makes pop_back O(n) — we must traverse the
    //   entire list to find the second-to-last node. Compare this to
    //   pop_front which is O(1). This is a key weakness of singly
    //   linked lists. A doubly linked list fixes this by giving each
    //   node a 'prev' pointer — we'll see that later.

    // TODO: Create two pointers: 'current' and 'previous', both starting at head_

    // TODO: Traverse the list until current reaches the last node.
    //       In each iteration, advance previous to current, then advance current to current->next.

    // ! DISCUSSION: Now 'current' is the last node and 'previous' is
    //   the second-to-last. We unlink and delete:
    //     1. Set previous->next to nullptr (it's now the new tail)
    //     2. Delete current (free the old tail's memory)

    // TODO: Set previous->next to nullptr

    // TODO: Delete current

    // TODO: Decrement size_

}

// --- Search ---

// ! DISCUSSION: contains() is a read-only search — it just answers
//   "is this value in the list?" without modifying anything.
//   We use the same traversal pattern from print():
//     current starts at head, follows next until nullptr.
//   If we find a node whose data matches, return true immediately.
//   If we reach nullptr without finding it, return false.
//
// ! DISCUSSION: This is O(n) in the worst case — we may have to look
//   at every node. There's no shortcut for an unsorted list.
//   Compare this to an array with binary search: O(log n), but only
//   if the array is sorted. Linked lists can't do binary search at all
//   because they have no random access.

bool SinglyLinkedList::contains(int value) const {
    // ! DISCUSSION: Start at the head and walk the chain.
    //   We don't need a trailing pointer here because we're just
    //   reading — no pointer surgery needed.

    // TODO: Create a 'current' pointer starting at head_

    // TODO: While current is not nullptr:
    //         If current->data equals value, return true.
    //         Advance current to current->next.

    // TODO: If the loop finishes without finding value, return false

    return false; // placeholder — remove this line when done
}

// --- Remove by value ---

// ! DISCUSSION: remove() deletes the FIRST node whose data matches value.
//   If the value isn't in the list, do nothing.
//   This combines the traversal pattern (find the node) with the
//   trailing pointer pattern (unlink it safely).
//
// ! DISCUSSION: Why do we need special cases again?
//   Just like pop_back, the logic differs depending on:
//     1. The list is empty — nothing to remove
//     2. The match is the HEAD node — no previous node to update
//     3. The match is in the middle or tail — trailing pointer needed

void SinglyLinkedList::remove(int value) {
    if (!head_) return;

    // ! DISCUSSION: Special case — the value is at the head.
    //   If head_->data matches, we just pop_front and we're done.
    //   We CANNOT use the trailing pointer pattern here because there
    //   is no node before head_.
    if (head_->data == value) {
        // TODO: Call pop_front() to remove the head node

        return;
    }

    // ! DISCUSSION: The trailing pointer pattern for middle/tail removal.
    //   We need TWO pointers:
    //     'previous' — the node we came from
    //     'current'  — the node we're inspecting
    //
    //   When current->data == value:
    //     - previous->next = current->next  (skip over current)
    //     - delete current                  (free the memory)
    //     - --size_
    //     - return
    //
    //   If we reach nullptr without a match, the value isn't in the list.

    // TODO: Create 'previous' pointing to head_, and 'current' pointing to head_->next

    // TODO: While current is not nullptr:
    //         If current->data == value:
    //           Set previous->next to current->next  (unlink current)
    //           Delete current
    //           Decrement size_
    //           Return
    //         Otherwise:
    //           Advance previous to current
    //           Advance current to current->next

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

    // TODO: Create a 'current' pointer starting at head_

    // TODO: While current is not nullptr, print current->data followed by " -> ",
    //       then advance current to current->next.

    std::cout << "nullptr\n";
}
