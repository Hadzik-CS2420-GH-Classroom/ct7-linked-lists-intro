#pragma once

#include "Node.h"


// ! DISCUSSION: Why wrap nodes in a class?
//   We could just use Node* directly in main, but then the caller
//   has to manually manage every pointer, track the size, and
//   remember to delete everything. The class handles all of that —
//   the user just calls push_front(), pop_front(), etc.
//   This is the same idea behind std::vector, std::list, and
//   every other STL container.

class SinglyLinkedList {
public:
    
    SinglyLinkedList() = default;
    ~SinglyLinkedList();

    // ! DISCUSSION: Rule of 3 (and Rule of 5)
    //   If you define ANY of destructor / copy constructor / copy assignment,
    //   you should define ALL three. We defined a destructor above, so we
    //   must handle the copy operations too. Here we 'delete' them —
    //   that counts as handling them. This prevents the compiler from
    //   auto-generating a shallow copy, which would give two lists
    //   pointing to the SAME nodes. When one list's destructor deletes
    //   them, the other list has dangling pointers — instant crash.
    //
    // ! DISCUSSION: "Do we have to delete move too?"
    //   Technically no — the compiler won't auto-generate move operations
    //   when you've declared copy operations. But explicitly deleting all
    //   four makes the intent crystal clear to anyone reading the code.
    //   This is the "Rule of 5": destructor + copy pair + move pair.
    SinglyLinkedList(const SinglyLinkedList&) = delete;            // copy constructor  (required by Rule of 3)
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete; // copy assignment   (required by Rule of 3)
    SinglyLinkedList(SinglyLinkedList&&) = delete;                 // move constructor  (explicit for clarity)
    SinglyLinkedList& operator=(SinglyLinkedList&&) = delete;      // move assignment   (explicit for clarity)

    void push_front(int value); // insert a new node at the head — O(1)
    void push_back(int value);  // insert a new node at the tail — O(n)
    void pop_front();           // remove the head node — O(1)
    void pop_back();            // remove the tail node — O(n)

    int get_size() const noexcept;
    bool is_empty() const noexcept;

    void print() const;

private:
    // ! DISCUSSION: "Why initialize to nullptr and 0 here?"
    //   These are default member initializers (C++11). They
    //   guarantee head_ and size_ start with sane values even
    //   if we forget to set them in a constructor. Without this,
    //   head_ would contain garbage — a pointer to random memory.
    Node* head_ = nullptr;
    int size_ = 0;
};
