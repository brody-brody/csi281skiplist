#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "skiplist.h"

using namespace std;

int main() {
    SkipList skiplist;

    // generating 10 random numbers into an empty vector
    // using the Mersenne Twister generator with uniform distribution
    // https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/
    static random_device rd;
    static mt19937 gen(rd());
    // random numbers generated will be in the range of 0 to 20 inclusive
    uniform_int_distribution<int> dis(0, 20);
    int numbers[10];
    for (int i = 0; i < 10; i++) 
    {
        numbers[i] = dis(gen);
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
    cout << "------Skip List after initial insertion:------" << endl;
    skiplist.display();

    // keep testing the search function until we find three elements in the list
    cout << "\n---------Testing the search function----------" << endl;
    int i = 0, count = 0, second;
    while (count < 3)
    {
        if (skiplist.search(i))
        {
            cout << i << " is in the list!\n" << endl;
            count++;
            // storing second element for removal test
            if (count == 2)
                second = i;
        }
        else
        {
            cout << i << " is not in the list.\n" << endl;
        }
        i++;
    }

    // remove an element
    cout << "-----------Skip List after removal:-----------" << endl;
    cout << "Removing the second unique element found, " << second << ", from the list." << endl;
    skiplist.remove(second);

    // displaying the skip list after the removal
    skiplist.display();

    return 0;
}