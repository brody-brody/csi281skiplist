#include "skiplist.h"

using namespace std;

Node::Node(int key, int level) : key(key), forward(level + 1, nullptr) {}

SkipList::SkipList(int maxLevel, float probability) : maxLevel(maxLevel), probability(probability) 
{
    // -1 is the sentinel key, meaning its not actually in the data, rather its just a starting point
    head = new Node(-1, maxLevel);
}

SkipList::~SkipList() 
{
    Node* current = head;

    // traverse the list and delete all nodes
    while (current) 
    {
        Node* next = current->forward[0];
        delete current;
        current = next;
    }
}

int SkipList::randomLevel() 
{
    // using the Mersenne Twister generator with uniform distribution
    // this is for the probabilistic nature of the skip list
    // https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0f, 1.0f);

    int level = 0;

    // if our coin flip is successful, and we are not yet at the max level, increment it
    while (dis(gen) < probability && level < maxLevel) 
    {
        level++;
    }

    return level;
}

void SkipList::insert(int key) 
{
    // temporary vector tracks nodes that need pointer updates
    vector<Node*> update(maxLevel + 1, nullptr);
    Node* current = head;


    // traversing from top level down to find where to insert
    for (int i = maxLevel; i >= 0; i--) 
    {
        // moving along current level until node has a greater or equal key
        while (current->forward[i] && current->forward[i]->key <= key) 
        {
            current = current->forward[i];
        }

        // updating node
        update[i] = current;
    }

    current = current->forward[0];

    // inserting new node if it doesnt exist
    if (!current || current->key != key) 
    {
        // random level for the new node
        int newLevel = randomLevel();
        Node* newNode = new Node(key, newLevel);

        // updating forward pointers at each level
        for (int i = 0; i <= newLevel; i++) 
        {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

bool SkipList::search(int key) 
{
    Node* current = head;

    // traverse from the top level down to find the given key
    for (int i = maxLevel; i >= 0; i--) 
    {
        // moving along current level until there is a node with a greater or equal key
        while (current->forward[i] && current->forward[i]->key < key) 
        {
            current = current->forward[i];
        }
    }

    current = current->forward[0];

    // checking if node exists and matches key
    return current && current->key == key;
}

void SkipList::remove(int key) 
{
    // temporary vector tracks nodes that need pointer updates
    vector<Node*> update(maxLevel + 1, nullptr);
    
    Node* current = head;

    // traversing from top level down to find where to remove
    for (int i = maxLevel; i >= 0; i--) 
    {
        // moving along current level until node has a greater key
        while (current->forward[i] && current->forward[i]->key < key) 
        {
            current = current->forward[i];
        }

        update[i] = current;
    }

    current = current->forward[0];

    // removing the node if it exists
    if (current && current->key == key) 
    {
        // updating forward pointers at each level
        for (int i = 0; i <= maxLevel; i++) 
        {
            // if pointer has changed, stop
            if (update[i]->forward[i] != current) 
                break;
            update[i]->forward[i] = current->forward[i];
        }

        delete current;
    }
}

void SkipList::display() 
{
    // traversing through list and printing out each level, with respective keys
    for (int i = 0; i <= maxLevel; i++) 
    {
        Node* current = head->forward[i];

        cout << "Level " << i << ": ";

        // going through all elements and printing keys
        while (current) 
        {
            cout << current->key << " ";
            current = current->forward[i];
        }

        cout << endl;
    }
}