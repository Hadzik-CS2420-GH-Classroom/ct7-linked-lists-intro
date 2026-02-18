#include "SinglyLinkedList.h"

#include <format>
#include <iostream>

int main() {
    std::cout << "=== Code-Together 7: Singly Linked List — Farr's Ice Cream ===\n\n";

    // ! DISCUSSION: Arrays vs linked lists — when to use which?
    //   Imagine Farr's Ice Cream on a busy Friday night. Customers grab
    //   a ticket number and wait in line. New customers join the back,
    //   and the person at the front gets served next.
    //
    //   An array would work, but every time we serve someone (remove from
    //   the front), we'd have to shift EVERY remaining ticket down one
    //   slot — O(n). A linked list just moves the head pointer — O(1).
    //
    //   Arrays:  Fast random access (who has ticket #5?), but expensive
    //            to insert/remove at the front (shift everything).
    //   Linked lists: Fast insert/remove at front (just move pointers),
    //            but no random access (must walk to find ticket #5).

    // =========================================================================
    // PART 1 — Basic Operations
    // =========================================================================

    SinglyLinkedList line;

    // --- 1. Customers arrive (push_back) ---
    std::cout << "--- 1. Customers arriving at Farr's ---\n";

    std::cout << "push_back(101) -- Ticket #101 arrives\n";
    line.push_back(101);

    std::cout << "push_back(102) -- Ticket #102 arrives\n";
    line.push_back(102);

    std::cout << "push_back(103) -- Ticket #103 arrives\n";
    line.push_back(103);

    std::cout << "Current line: ";
    line.print();
    std::cout << std::format("People waiting: {}\n\n", line.get_size());

    // ! DISCUSSION: push_back makes sense here — new customers join the
    //   END of the line, not the front. That's fair! First come, first served.

    // --- 2. A VIP cuts to the front (push_front) ---
    std::cout << "--- 2. VIP cuts to the front ---\n";

    std::cout << "push_front(200) -- VIP cuts to the front!\n";
    line.push_front(200); // Use push_front to add ticket 200 to the front of the line

    std::cout << "Current line: ";
    line.print();
    std::cout << std::format("People waiting: {}\n\n", line.get_size());

    // ! DISCUSSION: "Why is the order 200 -> 101 -> 102 -> 103?"
    //   push_front puts the new node BEFORE the current head.
    //   The VIP jumps ahead of everyone. In a real queue this is rude,
    //   but it shows how O(1) front insertion works — no shifting needed.

    // --- 3. Serving customers (pop_front) ---
    std::cout << "--- 3. Serving customers ---\n";

    std::cout << "pop_front() -- Serving ticket at the front\n";
    line.pop_front(); // Use pop_front to remove the first customer from the line

    std::cout << "Current line: ";
    line.print();
    std::cout << std::format("People waiting: {}\n\n", line.get_size());

    std::cout << "pop_front() -- Serving another ticket\n";
    line.pop_front(); // Use pop_front to remove the next customer from the line

    std::cout << "Current line: ";
    line.print();
    std::cout << std::format("People waiting: {}\n\n", line.get_size());

    // ! DISCUSSION: "Where did tickets #200 and #101 go?"
    //   pop_front removed them from memory entirely (delete).
    //   They've been served their ice cream and left.
    //   The head now points to ticket #102.

    // --- 4. More customers arrive while others are served ---
    std::cout << "--- 4. More customers arrive ---\n";

    std::cout << "push_back(104) -- Ticket #104 arrives\n";
    line.push_back(104);

    std::cout << "push_back(105) -- Ticket #105 arrives\n";
    line.push_back(105);

    std::cout << "Current line: ";
    line.print();
    std::cout << std::format("People waiting: {}\n\n", line.get_size());

    // ! DISCUSSION: This is a linked list's sweet spot — a queue where
    //   people constantly join and leave. No shifting, no resizing,
    //   just pointer updates. This is exactly how std::queue works
    //   under the hood.

    // --- 5. Customer at the back gives up and leaves (pop_back) ---
    std::cout << "--- 5. Customer at the back gives up ---\n";

    std::cout << "pop_back() -- Ticket at the back gives up waiting\n";
    line.pop_back(); // Use pop_back to remove the last customer from the line

    std::cout << "Current line: ";
    line.print();
    std::cout << std::format("People waiting: {}\n\n", line.get_size());

    // ! DISCUSSION: "Why is pop_back slower than pop_front?"
    //   To remove the last node, we have to traverse the ENTIRE list
    //   to find the second-to-last node (the trailing pointer pattern).
    //   pop_front just moves head — O(1). pop_back must traverse — O(n).
    //   This is a key tradeoff of singly linked lists. A doubly linked
    //   list solves this with a 'prev' pointer on each node.

    // =========================================================================
    // PART 2 — Search and Remove (Lost & Found scenario)
    // =========================================================================

    std::cout << "=== Part 2: Search and Remove — Campus Lost & Found ===\n\n";

    // ! DISCUSSION: The same list structure works for a Lost & Found inventory.
    //   Items are logged by ID. Staff need to search for items and remove
    //   them when claimed. These operations reuse the traversal pattern
    //   from print() and the trailing pointer pattern from pop_back().

    SinglyLinkedList lost_and_found;
    lost_and_found.push_back(1001); // laptop
    lost_and_found.push_back(1002); // backpack
    lost_and_found.push_back(1003); // water bottle
    lost_and_found.push_back(1004); // keys
    lost_and_found.push_back(1005); // umbrella

    std::cout << "Current inventory: ";
    lost_and_found.print();
    std::cout << std::format("Items on record: {}\n\n", lost_and_found.get_size());

    // --- 6. Searching for items (contains) ---
    std::cout << "--- 6. Checking if items are in the system ---\n";

    // Use contains() to check if item 1003 is in the list.
    std::cout << std::format("Item 1003 found: {}\n", lost_and_found.contains(1003) ? "true" : "false");

    // Use contains() to check if item 9999 is in the list.
    std::cout << std::format("Item 9999 found: {}\n", lost_and_found.contains(9999) ? "true" : "false");

    std::cout << "\n";

    // ! DISCUSSION: contains() traverses the entire list in the worst case.
    //   Item 1003 is near the middle — O(n/2) average.
    //   Item 9999 isn't there at all — O(n) because we walk the whole list.

    // --- 7. Removing claimed items ---
    std::cout << "--- 7. Removing claimed items ---\n";

    std::cout << "remove(1005) — tail:   ";
    lost_and_found.remove(1005); // Call remove(1005), then print the list
    lost_and_found.print();

    std::cout << "remove(1002) — middle: ";
    lost_and_found.remove(1002); // Call remove(1002), then print the list
    lost_and_found.print();

    std::cout << "remove(1001) — head:   ";
    lost_and_found.remove(1001); // Call remove(1001), then print the list
    lost_and_found.print();

    std::cout << std::format("Items remaining: {}\n", lost_and_found.get_size());

    return 0;
}
