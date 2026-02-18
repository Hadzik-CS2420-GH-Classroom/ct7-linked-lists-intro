#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "SinglyLinkedList.h"

static std::string capturePrint(const SinglyLinkedList& list) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    list.print();
    std::cout.rdbuf(oldCout);
    return buffer.str();
}

// ==================== Destructor (5 points) ====================

TEST(SinglyLinkedListTest, DestructorFreesMemory) {
    auto* list = new SinglyLinkedList();
    list->push_front(10);
    list->push_front(20);
    list->push_front(30);
    EXPECT_EQ(list->get_size(), 3);
    delete list; // should not crash or leak
}

// ==================== push_front Tests (8 points) ====================

TEST(SinglyLinkedListTest, PushFrontSingleElement) {
    SinglyLinkedList list;
    list.push_front(42);
    EXPECT_EQ(list.get_size(), 1)
        << "push_front on empty list should result in size 1";
    EXPECT_TRUE(capturePrint(list).find("42") != std::string::npos);
}

TEST(SinglyLinkedListTest, PushFrontMultipleElements) {
    SinglyLinkedList list;
    list.push_front(30);
    list.push_front(20);
    list.push_front(10);
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_TRUE(capturePrint(list).find("10 -> 20 -> 30 -> nullptr") != std::string::npos)
        << "Elements should be in reverse insertion order: 10 -> 20 -> 30";
}

// ==================== push_back Tests (8 points) ====================

TEST(SinglyLinkedListTest, PushBackSingleElement) {
    SinglyLinkedList list;
    list.push_back(42);
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_TRUE(capturePrint(list).find("42") != std::string::npos);
}

TEST(SinglyLinkedListTest, PushBackMultipleElements) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_TRUE(capturePrint(list).find("10 -> 20 -> 30 -> nullptr") != std::string::npos)
        << "Elements should appear in insertion order";
}

// ==================== pop_front Tests (8 points) ====================

TEST(SinglyLinkedListTest, PopFrontRemovesHead) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_front();
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(capturePrint(list).find("20 -> 30 -> nullptr") != std::string::npos);
}

TEST(SinglyLinkedListTest, PopFrontToEmpty) {
    SinglyLinkedList list;
    list.push_front(10);
    list.pop_front();
    EXPECT_TRUE(list.is_empty());
}

// ==================== pop_back Tests (10 points) ====================

TEST(SinglyLinkedListTest, PopBackRemovesTail) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_back();
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(capturePrint(list).find("10 -> 20 -> nullptr") != std::string::npos);
}

TEST(SinglyLinkedListTest, PopBackToEmpty) {
    SinglyLinkedList list;
    list.push_front(10);
    list.pop_back();
    EXPECT_TRUE(list.is_empty());
}

// ==================== contains() Tests (10 points) ====================

TEST(SinglyLinkedListTest, ContainsTrueForHeadMiddleTail) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(20));
    EXPECT_TRUE(list.contains(30));
}

TEST(SinglyLinkedListTest, ContainsFalseForMissingValue) {
    SinglyLinkedList list;
    list.push_back(10);
    EXPECT_FALSE(list.contains(99));
}

TEST(SinglyLinkedListTest, ContainsOnEmptyList) {
    SinglyLinkedList list;
    EXPECT_FALSE(list.contains(1));
}

// ==================== remove() Tests (14 points) ====================

TEST(SinglyLinkedListTest, RemoveTail) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.remove(30);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(capturePrint(list).find("10 -> 20 -> nullptr") != std::string::npos);
}

TEST(SinglyLinkedListTest, RemoveMiddle) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.remove(20);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(capturePrint(list).find("10 -> 30 -> nullptr") != std::string::npos);
}

TEST(SinglyLinkedListTest, RemoveHead) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.remove(10);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(capturePrint(list).find("20 -> 30 -> nullptr") != std::string::npos);
}

TEST(SinglyLinkedListTest, RemoveNotFound) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.remove(99);
    EXPECT_EQ(list.get_size(), 2);
}

TEST(SinglyLinkedListTest, RemoveOnEmptyList) {
    SinglyLinkedList list;
    EXPECT_NO_THROW(list.remove(5));
}

// ==================== Getters & Print (5 points) ====================

TEST(SinglyLinkedListTest, IsEmptyOnNewList) {
    SinglyLinkedList list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.get_size(), 0);
}

TEST(SinglyLinkedListTest, PrintEmptyList) {
    SinglyLinkedList list;
    EXPECT_TRUE(capturePrint(list).find("nullptr") != std::string::npos);
}
