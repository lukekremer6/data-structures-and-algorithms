/*
 * Implements a circular dynamic array.
 *
 * The main advantage of a circular array over a regular array
 * is that it supports O(1) insertion and deletion at both
 * the front and back of the array, unlike a regular array,
 * which only supports O(1) insertion and deletion at the back
 * of the array. A circular array can be used to implement an
 * efficient queue.
*/

#ifndef CDA_H
#define CDA_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>

template <typename elmtype>
class CDA {
    private:
        int capacity;
        int size;
        int ordered;
        int front;
        elmtype* array;
        elmtype error;

        void DoubleCapacity();
        void HalveCapacity();
        elmtype Quickselect(int k);
        void Merge(CDA & array1, CDA & array2);
        int BinarySearch(elmtype e);
        int LinearSearch(elmtype e);
        elmtype & GetElement(int i);

    public:
        friend void swap(CDA & c1, CDA & c2) {
            using std::swap;
            swap(c1.capacity, c2.capacity);
            swap(c1.size, c2.size);
            swap(c1.ordered, c2.ordered);
            swap(c1.front, c2.front);
            swap(c1.array, c2.array);
            swap(c1.error, c2.error);
        }

        CDA();
        CDA(int s);
        CDA(const CDA & source);
        CDA & operator =(CDA source);
        ~CDA();
        elmtype & operator[](int i);
        void AddEnd(elmtype v);
        void AddFront(elmtype v);
        void DelEnd();
        void DelFront();
        int Length();
        int EmptySlots();
        void Clear();
        int Ordered();
        int SetOrdered();
        elmtype Select(int k);
        void InsertionSort();
        void MergeSort();
        void CountingSort(int m);
        int Search(elmtype e);
};

template <typename elmtype>
CDA<elmtype>::CDA() : capacity(1), size(0), ordered(0), front(0), array(new elmtype[capacity]) {}

template <typename elmtype>
CDA<elmtype>::CDA(int s) : capacity(s), size(s), ordered(0), front(0), array(new elmtype[capacity]) {}

template <typename elmtype>
CDA<elmtype>::CDA(const CDA & source) : capacity(source.capacity), size(source.size), ordered(source.ordered), front(source.front), array(new elmtype[capacity]) {
    for (int i = 0; i < size; ++i) {
        array[i] = source.array[i];
    }
}

template <typename elmtype>
CDA<elmtype> & CDA<elmtype>::operator =(CDA<elmtype> source) {
    swap(*this, source);
    return *this;
}

template <typename elmtype>
CDA<elmtype>::~CDA() {
    delete[] array;
}

template <typename elmtype>
elmtype & CDA<elmtype>::operator[](int i) {
    ordered = 0;
    if (i < 0 || i >= size) {
        std::cout << "ERROR: out of bounds" << std::endl;
        return error;
    }

    else {
        return GetElement(i);
    }
}

template <typename elmtype>
void CDA<elmtype>::AddEnd(elmtype v) {
    if (size == capacity) {
        DoubleCapacity();
    }

    GetElement(size) = v;
    ++size;

    // Check if array is still ordered
    if (ordered == 1 && GetElement(size - 2) > GetElement(size - 1)) {
        if (size == 2) {
            ordered = -1;
        }

        else {
            ordered = 0;
        }
    }

    else if (ordered == -1 && GetElement(size - 2) < GetElement(size - 1)) {
        if (size == 2) {
            ordered = 1;
        }

        else {
            ordered = 0;
        }
    }
}

template <typename elmtype>
void CDA<elmtype>::AddFront(elmtype v) {
    if (size == capacity) {
        DoubleCapacity();
    }

    front = (front - 1 + capacity) % capacity;
    GetElement(0) = v;

    ++size;

    // Check if array is still ordered
    if (ordered == 1 && GetElement(0) > GetElement(1)) {
        if (size == 2) {
            ordered = -1;
        }

        else {
            ordered = 0;
        }
    }

    else if (ordered == -1 && GetElement(0) < GetElement(1)) {
        if (size == 2) {
            ordered = 1;
        }

        else {
            ordered = 0;
        }
    }
}

template <typename elmtype>
void CDA<elmtype>::DelEnd() {
    --size;

    if (size <= capacity / 4.0) {
        HalveCapacity();
    }
}

template <typename elmtype>
void CDA<elmtype>::DelFront() {
    front = (front + 1) % capacity;
    --size;

    if (size <= capacity / 4.0) {
        HalveCapacity();
    }
}

template <typename elmtype>
int CDA<elmtype>::Length() {
    return size;
}

template <typename elmtype>
int CDA<elmtype>::EmptySlots() {
    return capacity - size;
}

template <typename elmtype>
void CDA<elmtype>::Clear() {
    delete[] array;
    capacity = 1;
    size = 0;
    ordered = 0;
    front = 0;
    array = new elmtype[capacity];
}

template <typename elmtype>
int CDA<elmtype>::Ordered() {
    return ordered;
}

template <typename elmtype>
int CDA<elmtype>::SetOrdered() {
    if (size <= 1) {
        ordered = 0;
    }

    else {
        // Assume array is in increasing order
        ordered = 1;

        // If array is not in increasing order, assume it is unordered
        for (int i = 0; i < size - 1; ++i) {
            if (GetElement(i) > GetElement(i + 1)) {
                ordered = 0;
                break;
            }
        }

        if (ordered == 0) {
            // Assume array is in decreasing order
            ordered = -1;

            // If array is not in decreasing order, it is unordered
            for (int i = 0; i < size - 1; ++i) {
                if (GetElement(i) < GetElement(i + 1)) {
                    ordered = 0;
                    break;
                }
            }
        }
    }

    return ordered;
}

// Find the k-th smallest element in the array without sorting.
// If the array is already sorted, this takes O(1) time.
// If the array is unsorted, this takes O(n) time on average.
template <typename elmtype>
elmtype CDA<elmtype>::Select(int k) {
    if (ordered == 1) {
        return GetElement(k - 1);
    }

    else if (ordered == -1) {
        return GetElement(size - k);
    }

    else {
        return Quickselect(k);
    }
}

template <typename elmtype>
void CDA<elmtype>::InsertionSort() {
    for (int i = 1; i < size; ++i) {
        elmtype key = GetElement(i);
        int j;

        for (j = i - 1; j >= 0 && key > GetElement(j); --j) {
            GetElement(j + 1) = GetElement(j);
        }

        GetElement(j + 1) = key;
    }

    ordered = -1;
}

template <typename elmtype>
void CDA<elmtype>::MergeSort() {
    if (size > 1) {
        int size1 = size / 2;
        int size2 = size / 2.0 + 0.5;
        
        CDA array1(size1);
        CDA array2(size2);

        for (int i = 0; i < size1; ++i) {
            array1[i] = GetElement(i);
        }

        for (int i = 0; i < size2; ++i) {
            array2[i] = GetElement(i + array1.Length());
        }

        array1.MergeSort();
        array2.MergeSort();

        Merge(array1, array2);
    }

    front = 0;
    ordered = -1;
}

template <typename elmtype>
void CDA<elmtype>::CountingSort(int m) {
    int count[m + 1];

    for (int i = 0; i < m + 1; ++i) {
        count[i] = 0;
    }

    for (int i = 0; i < size; ++i) {
        ++count[m - GetElement(i)];
    }
    
    int total = 0;
    for (int i = 0; i <= m; ++i) {
        int temp = count[i];
        count[i] = total;
        total += temp;
    }

    elmtype* sortedArray = new elmtype[capacity];
    for (int i = 0; i < size; ++i) {
        sortedArray[count[m - GetElement(i)]] = GetElement(i);
        ++count[m - GetElement(i)];
    }

    delete[] array;
    array = sortedArray;

    front = 0;
    ordered = -1;
}

template <typename elmtype>
int CDA<elmtype>::Search(elmtype e) {
    if (ordered == 1 || ordered == -1) {
        return BinarySearch(e);
    }

    else {
        return LinearSearch(e);
    }
}

template <typename elmtype>
void CDA<elmtype>::DoubleCapacity() {
    int newCapacity = capacity * 2;
    elmtype* newArray = new elmtype[newCapacity];

    for (int i = 0; i < size; ++i) {
        newArray[i] = GetElement(i);
    }

    delete[] array;

    capacity = newCapacity;
    front = 0;
    array = newArray;
}

template <typename elmtype>
void CDA<elmtype>::HalveCapacity() {
    int newCapacity = capacity / 2.0 + 0.5;

    if (newCapacity < 4) {
        newCapacity = 4;
    }

    elmtype* newArray = new elmtype[newCapacity];

    for (int i = 0; i < size; ++i) {
        newArray[i] = GetElement(i);
    }

    delete[] array;

    capacity = newCapacity;
    front = 0;
    array = newArray;
}

template <typename elmtype>
elmtype CDA<elmtype>::Quickselect(int k) {
    srand(time(NULL));
    elmtype pivot = GetElement(rand() % size);

    CDA less;
    CDA greater;
    CDA equal;

    for (int i = 0; i < size; ++i) {
        if (GetElement(i) < pivot) {
            less.AddEnd(GetElement(i));
        }

        else if (GetElement(i) == pivot) {
            equal.AddEnd(GetElement(i));
        }

        else {
            greater.AddEnd(GetElement(i));
        }
    }

    if (k - 1 < less.Length()) {
        return less.Quickselect(k);
    }

    else if (k - 1 < less.Length() + equal.Length()) {
        return pivot;
    }

    else {
        return greater.Quickselect(k - less.Length() - equal.Length());
    }
}

template <typename elmtype>
void CDA<elmtype>::Merge(CDA & array1, CDA & array2) {
    int i = 0;
    int j = 0;

    for (int k = 0; k < size; ++k) {
        if (i == array1.Length()) {
            array[k] = array2[j];
            ++j;
        }

        else if (j == array2.Length()) {
            array[k] = array1[i];
            ++i;
        }

        else if (array1[i] > array2[j]) {
            array[k] = array1[i];
            ++i;
        }

        else {
            array[k] = array2[j];
            ++j;
        }
    }
}

template <typename elmtype>
int CDA<elmtype>::BinarySearch(elmtype e) {
    int lowerBound = 0;
    int upperBound = size - 1;
    int middle;

    while (1) {
        middle = (upperBound + lowerBound) / 2;

        if (lowerBound > upperBound) {
            return -1;
        }

        else if (GetElement(middle) == e) {
            return middle;
        }

        else if (ordered == -1) {
            if (GetElement(middle) < e) {
                upperBound = middle - 1;
            }

            else {
                lowerBound = middle + 1;
            }
        }

        else {
            if (GetElement(middle) > e) {
                upperBound = middle - 1;
            }

            else {
                lowerBound = middle + 1;
            }
        }
    }
}

template <typename elmtype>
int CDA<elmtype>::LinearSearch(elmtype e) {
    for (int i = 0; i < size; ++i) {
        if (GetElement(i) == e) {
            return i;
        }
    }

    return -1;
}

template <typename elmtype>
elmtype & CDA<elmtype>::GetElement(int i) {
    return array[(i + front) % capacity];
}

#endif
