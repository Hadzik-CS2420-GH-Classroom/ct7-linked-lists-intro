# CT7 -- Header Diagrams

Conceptual diagrams referenced from `SinglyLinkedList.h`.

---

## 1. Node vs. Array
*`SinglyLinkedList.h` -- why linked lists exist and how nodes differ from contiguous arrays*

![Node vs Array](svgs/node_vs_array.svg)

---

## 2. push_front -- O(1)
*`SinglyLinkedList.h` -- create node, point to old head, update head*

![push_front](svgs/push_front.svg)

---

## 3. push_back -- O(n)
*`SinglyLinkedList.h` -- traverse to end, link new node*

![push_back](svgs/push_back.svg)

---

## 4. pop_front -- O(1)
*`SinglyLinkedList.h` -- save head, advance head, delete old*

![pop_front](svgs/pop_front.svg)

---

## 5. pop_back -- O(n)
*`SinglyLinkedList.h` -- traverse to second-to-last, delete last*

![pop_back](svgs/pop_back.svg)

---

## 6. Destructor Walk
*`SinglyLinkedList.h` -- walk from head to tail, deleting every node*

![Destructor Walk](svgs/destructor_walk.svg)
