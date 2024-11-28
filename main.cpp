#include <iostream>
#include <vector>
#include <algorithm>
#include "skiplist.h"

using namespace std;

int main() {
    SkipList skiplist;

    // generating 10 random numbers into an empty vector
    int numbers[10];
    for (int i = 0; i < 10; i++) 
    {
        numbers[i] = rand() % 100; // random numbers between 0 and 99
    }

    // sorting the integers, as the skip list is for sorted
    int arrLength = sizeof(numbers) / sizeof(numbers[0]);
    sort(numbers, numbers + arrLength);

    // inserting elements into the empty skip list from the sorted array of 10 random integers
    for (int i = 0; i < 10; i++)
    {
        skiplist.insert(numbers[i]);
    }

    // displaying the skip list after the initial insertions
    cout << "Skip List after insertion:" << endl;
    skiplist.display();

    // testing the search function of the skip list
    if (skiplist.search(6))
    {
        cout << "6 is in the list" << endl;
    }
    else
    {
        cout << "6 is not in the list" << endl;
    }

    if (skiplist.search(4))
    {
        cout << "4 is in the list" << endl;
    }
    else
    {
        cout << "4 is not in the list" << endl;
    }

    // remove an element
    cout << "Removing 6." << endl;
    skiplist.remove(6);

    //
    cout << "Skip List after removal: " << endl;
    skiplist.display();

    return 0;
}