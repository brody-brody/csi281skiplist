#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

class Node 
{
public:
    // each node holds a key and a pointer to the next, meaning our skip list is singly linked
    int key;
    std::vector<Node*> forward;

    Node(int key, int level);
};

class SkipList 
{
private:
    int maxLevel;
    float probability;
    Node* head;

    int randomLevel();
public:
    // limiting max level ensures performance balances with memory usage
    // probability stays at a basic coin flip
    SkipList(int maxLevel = 4, float probability = 0.5);
    ~SkipList();

    void insert(int key);
    bool search(int key);
    void remove(int key);
    void display();
};