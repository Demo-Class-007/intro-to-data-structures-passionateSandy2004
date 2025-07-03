// src/hello.cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <limits>
#include <vector>

// ------------------
// Your ER‐Triage API
// ------------------
struct Patient {
    std::string name;
    int priority;
    long   timestamp;
    Patient* next;
};

class TriageQueue {
public:
    TriageQueue() : head(nullptr), counter(0) {}
    ~TriageQueue() {
        while (head) {
            auto tmp = head->next;
            delete head;
            head = tmp;
        }
    }
    void enqueue(const std::string &name, int priority) {
        // TODO: implement insertion by priority then FIFO
        // increment counter for timestamp
        (void)name; (void)priority;
    }
    std::string dequeue() {
        // TODO: remove & return head->name
        return "";
    }
    std::pair<std::string,int> peek() const {
        if (!head) return {"", -1};
        return { head->name, head->priority };
    }
    bool isEmpty() const { return head == nullptr; }
    std::vector<std::pair<std::string,int>> display() const {
        std::vector<std::pair<std::string,int>> out;
        for (auto cur = head; cur; cur = cur->next)
            out.emplace_back(cur->name, cur->priority);
        return out;
    }
private:
    Patient* head;
    long     counter;  // simple timestamp generator
};

// --------------
// Test cases
// --------------
TEST_CASE("Empty queue starts empty") {
    TriageQueue q;
    REQUIRE(q.isEmpty());
    REQUIRE(q.peek().second == -1);
}

TEST_CASE("Enqueue & Dequeue by priority") {
    TriageQueue q;
    q.enqueue("Alice", 3);
    q.enqueue("Bob",   1);
    REQUIRE(!q.isEmpty());
    REQUIRE(q.dequeue() == "Bob");
    REQUIRE(q.dequeue() == "Alice");
    REQUIRE(q.isEmpty());
}

TEST_CASE("FIFO on equal priority") {
    TriageQueue q;
    q.enqueue("X", 2);
    q.enqueue("Y", 2);
    REQUIRE(q.dequeue() == "X");
    REQUIRE(q.dequeue() == "Y");
}

TEST_CASE("Peek does not remove") {
    TriageQueue q;
    q.enqueue("P1", 4);
    auto p = q.peek();
    REQUIRE(p.first == "P1");
    REQUIRE(p.second == 4);
    REQUIRE(!q.isEmpty());
}

TEST_CASE("Display order") {
    TriageQueue q;
    q.enqueue("A", 5);
    q.enqueue("B", 1);
    q.enqueue("C", 3);
    auto lst = q.display();
    REQUIRE(lst.size() == 3);
    // highest‑priority first
    REQUIRE(lst[0].first == "B");
    REQUIRE(lst[1].first == "C");
    REQUIRE(lst[2].first == "A");
}
