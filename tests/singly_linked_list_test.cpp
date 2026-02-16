#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "SinglyLinkedList.h"

// Helper: capture stdout from a list's print() method
static std::string capturePrint(const SinglyLinkedList& list) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    list.print();
    std::cout.rdbuf(oldCout);
    return buffer.str();
}

// ==================== Destructor (6 points) ====================

TEST(SinglyLinkedListTest, DestructorFreesMemory) {
    // If the destructor is broken, this will leak or crash.
    // We just verify it runs without error on a populated list.
    auto* list = new SinglyLinkedList();
    list->push_front(10);
    list->push_front(20);
    list->push_front(30);
    EXPECT_EQ(list->get_size(), 3);
    delete list;  // should not crash or leak
}

// ==================== push_front Tests (8 points) ====================

TEST(SinglyLinkedListTest, PushFrontSingleElement) {
    SinglyLinkedList list;
    list.push_front(42);
    EXPECT_EQ(list.get_size(), 1)
        << "push_front on empty list should result in size 1";
    std::string output = capturePrint(list);
    EXPECT_TRUE(output.find("42") != std::string::npos)
        << "List should contain 42 after push_front(42)";
}

TEST(SinglyLinkedListTest, PushFrontMultipleElements) {
    SinglyLinkedList list;
    list.push_front(30);
    list.push_front(20);
    list.push_front(10);
    EXPECT_EQ(list.get_size(), 3)
        << "push_front three times should result in size 3";
    std::string output = capturePrint(list);
    EXPECT_TRUE(output.find("10 -> 20 -> 30 -> nullptr") != std::string::npos)
        << "Elements should be in reverse insertion order: 10 -> 20 -> 30";
}

// ==================== push_back Tests (8 points) ====================

TEST(SinglyLinkedListTest, PushBackSingleElement) {
    SinglyLinkedList list;
    list.push_back(42);
    EXPECT_EQ(list.get_size(), 1)
        << "push_back on empty list should result in size 1";
    std::string output = capturePrint(list);
    EXPECT_TRUE(output.find("42") != std::string::npos)
        << "List should contain 42 after push_back(42)";
}

TEST(SinglyLinkedListTest, PushBackMultipleElements) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    EXPECT_EQ(list.get_size(), 3)
        << "push_back three times should result in size 3";
    std::string output = capturePrint(list);
    EXPECT_TRUE(output.find("10 -> 20 -> 30 -> nullptr") != std::string::npos)
        << "Elements should be in insertion order: 10 -> 20 -> 30";
}

// ==================== pop_front Tests (8 points) ====================

TEST(SinglyLinkedListTest, PopFrontRemovesHead) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_front();
    EXPECT_EQ(list.get_size(), 2)
        << "pop_front should decrease size from 3 to 2";
    std::string output = capturePrint(list);
    EXPECT_TRUE(output.find("20 -> 30 -> nullptr") != std::string::npos)
        << "After pop_front, list should be: 20 -> 30 -> nullptr";
}

TEST(SinglyLinkedListTest, PopFrontToEmpty) {
    SinglyLinkedList list;
    list.push_front(10);
    list.pop_front();
    EXPECT_EQ(list.get_size(), 0)
        << "pop_front on single-element list should result in size 0";
    EXPECT_TRUE(list.is_empty())
        << "List should be empty after removing the only element";
}

// ==================== pop_back Tests (10 points) ====================

TEST(SinglyLinkedListTest, PopBackRemovesTail) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_back();
    EXPECT_EQ(list.get_size(), 2)
        << "pop_back should decrease size from 3 to 2";
    std::string output = capturePrint(list);
    EXPECT_TRUE(output.find("10 -> 20 -> nullptr") != std::string::npos)
        << "After pop_back, list should be: 10 -> 20 -> nullptr";
}

TEST(SinglyLinkedListTest, PopBackToEmpty) {
    SinglyLinkedList list;
    list.push_front(10);
    list.pop_back();
    EXPECT_EQ(list.get_size(), 0)
        << "pop_back on single-element list should result in size 0";
    EXPECT_TRUE(list.is_empty())
        << "List should be empty after removing the only element";
}

// ==================== Getters & Print (10 points) ====================

TEST(SinglyLinkedListTest, IsEmptyOnNewList) {
    SinglyLinkedList list;
    EXPECT_TRUE(list.is_empty())
        << "A newly created list should be empty";
    EXPECT_EQ(list.get_size(), 0)
        << "A newly created list should have size 0";
}

TEST(SinglyLinkedListTest, PrintEmptyList) {
    SinglyLinkedList list;
    std::string output = capturePrint(list);
    EXPECT_TRUE(output.find("nullptr") != std::string::npos)
        << "Printing an empty list should show 'nullptr'";
}

TEST(SinglyLinkedListTest, PrintPopulatedList) {
    SinglyLinkedList list;
    list.push_back(101);
    list.push_back(102);
    list.push_back(103);
    std::string output = capturePrint(list);
    EXPECT_TRUE(output.find("101 -> 102 -> 103 -> nullptr") != std::string::npos)
        << "print() should show all elements with ' -> ' separators ending in 'nullptr'";
}
