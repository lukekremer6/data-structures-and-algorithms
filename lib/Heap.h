/*
 * Implements a binary min-heap.
 *
 * It can insert elements in O(log n) time,
 * get the minimum element in O(1) time,
 * and remove the minimum element in O(log n) time.
 * It can be used to efficiently implement a priority queue.
*/

#ifndef HEAP_H
#define HEAP_H

#include "CDA.h"
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

template <typename keytype>
class Heap {
    private:
        CDA<keytype> keys;
        keytype junk;
        void percolateDown(int index);
        void percolateUp(int index);

    public:
        Heap();
        Heap(keytype k[], int s);
        keytype peekKey();
        keytype extractMin();
        void insert(keytype k);
        void printKey();
        std::string stringKey();
};

template <typename keytype>
void Heap<keytype>::percolateDown(int index) {
    // Check if there's a left child. Check if there's a right child. If so, compare them. smallestChildIndex = smallest one.
    // If you need to, swap index with smallestChild and call percolateDown() recursively.

    int smallestChildIndex = 0;

    if (keys.Length() > 2 * index) { // if keys[index] has a left child
        if (keys.Length() > 2 * index + 1) { // if keys[index] has a right child
            smallestChildIndex = (keys[2 * index] < keys[2 * index + 1]) ? (2 * index) : (2 * index + 1);
        }

        else {
            smallestChildIndex = 2 * index;
        }

        if (keys[index] > keys[smallestChildIndex]) {
            std::swap(keys[index], keys[smallestChildIndex]);
            percolateDown(smallestChildIndex);
        }
    }
}

template <typename keytype>
void Heap<keytype>::percolateUp(int index) {
    // Check if index has a parent.
    // If so, check if index is smaller than its parent.
    // If so, swap them and call percolateUp recursively.

    if (index > 1 && keys[index] < keys[index / 2]) {
        std::swap(keys[index], keys[index / 2]);
        percolateUp(index / 2);
    }
}

template <typename keytype>
Heap<keytype>::Heap() {
    // Add a single dummy element to the keys array so it starts at index 1
    keys.AddEnd(junk);
}

template <typename keytype>
Heap<keytype>::Heap(keytype k[], int s) {
    // Heapify

    // Add a single dummy element to the keys array so it starts at index 1
    keys.AddEnd(junk);

    for (int i = 0; i < s; ++i) {
        keys.AddEnd(k[i]);
    }

    for (int i = s; i > 0; --i) {
        percolateDown(i);
    }
}

template <typename keytype>
keytype Heap<keytype>::peekKey() {
    return keys[1];
}

template <typename keytype>
keytype Heap<keytype>::extractMin() {
    // Swap min with last element in heap and delete it.
    // Percolate the new root down.

    keytype min = keys[1];

    std::swap(keys[1], keys[keys.Length() - 1]);
    keys.DelEnd();
    percolateDown(1);

    return min;
}

template <typename keytype>
void Heap<keytype>::insert(keytype k) {
    keys.AddEnd(k);
    percolateUp(keys.Length() - 1);
}

template <typename keytype>
void Heap<keytype>::printKey() {
    std::cout << stringKey() << std::endl;
}

template <typename keytype>
std::string Heap<keytype>::stringKey() {
    // Insert each element in keys into a stringstream, then convert it into a string and return it
    std::ostringstream allKeys;

    for (int i = 1; i < keys.Length(); ++i) {
        allKeys << keys[i] << ' ';
    }

    std::string allKeysString = allKeys.str();
    allKeysString.pop_back();

    return allKeysString;
}

#endif
