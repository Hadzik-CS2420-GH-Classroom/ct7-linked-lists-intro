#include "SinglyLinkedList.h"

#include <format>
#include <iostream>

int main() {
    std::cout << "=== Code-Together 7: Farr's Ice Cream Ticket Queue ===\n\n";

    // ! DISCUSSION: Arrays vs linked lists — when to use which?
    //   Imagine Farr's Ice Cream on a busy Friday night. Customers grab
    //   a ticket number and wait in line.
    //   - An array would work, but serving someone (remove from the front)
    //     means shifting EVERY remaining ticket down one slot — O(n)
    //   - A linked list just moves the head pointer — O(1)
    //   - Arrays: fast random access (who has ticket #5?), but expensive
    //     insert/remove at front (shift everything)
    //   - Linked lists: fast insert/remove at front (just move pointers),
    //     but no random access (must walk to find ticket #5)

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

    // ! DISCUSSION: push_back makes sense here.
    //   - New customers join the END of the line, not the front
    //   - First come, first served

    // --- 2. A VIP cuts to the front (push_front) ---
    std::cout << "--- 2. VIP cuts to the front ---\n";

    std::cout << "push_front(200) -- VIP cuts to the front!\n";
    line.push_front(200);
    std::cout << "Current line: ";
    line.print();
    std::cout << std::format("People waiting: {}\n\n", line.get_size());

    // ! DISCUSSION: "Why is the order 200 -> 101 -> 102 -> 103?"
    //   - push_front puts the new node BEFORE the current head
    //   - The VIP jumps ahead of everyone — shows how O(1) front insertion
    //     works, no shifting needed

    // --- 3. Serving customers (pop_front) ---
    std::cout << "--- 3. Serving customers ---\n";

    std::cout << "pop_front() -- Serving ticket at the front\n";
    line.pop_front();
    std::cout << "Current line: ";
    line.print();
    std::cout << std::format("People waiting: {}\n\n", line.get_size());

    std::cout << "pop_front() -- Serving another ticket\n";
    line.pop_front();
    std::cout << "Current line: ";
    line.print();
    std::cout << std::format("People waiting: {}\n\n", line.get_size());

    // ! DISCUSSION: "Where did tickets #200 and #101 go?"
    //   - pop_front removed them from memory entirely (delete)
    //   - They've been served their ice cream and left
    //   - The head now points to ticket #102

    // --- 4. More customers arrive while others are served ---
    std::cout << "--- 4. More customers arrive ---\n";

    std::cout << "push_back(104) -- Ticket #104 arrives\n";
    line.push_back(104);
    std::cout << "push_back(105) -- Ticket #105 arrives\n";
    line.push_back(105);
    std::cout << "Current line: ";
    line.print();
    std::cout << std::format("People waiting: {}\n\n", line.get_size());

    // ! DISCUSSION: This is a linked list's sweet spot — a queue where people constantly join and leave.
    //   - No shifting, no resizing, just pointer updates
    //   - This is exactly how std::queue works under the hood

    // --- 5. Customer at the back gives up and leaves (pop_back) ---
    std::cout << "--- 5. Customer at the back gives up ---\n";

    std::cout << "pop_back() -- Ticket at the back gives up waiting\n";
    line.pop_back();
    std::cout << "Current line: ";
    line.print();
    std::cout << std::format("People waiting: {}\n\n", line.get_size());

    // ! DISCUSSION: "Why is pop_back slower than pop_front?"
    //   - To remove the last node, we traverse the ENTIRE list
    //     to find the second-to-last node (trailing pointer pattern)
    //   - pop_front just moves head — O(1); pop_back must traverse — O(n)
    //   - A doubly linked list solves this with a 'prev' pointer on each node

    return 0;
}
