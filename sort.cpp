#include <iostream>
#include <windows.h>
using namespace std;

///////////////////
// Utils
///////////////////
void printArray(int* a, int length)
{
    cout << '[';
    for (int i = 0; i < length; ++i)
    {
        if (i > 0)
        {
            cout << ", ";
        }

        cout << a[i];
    }

    cout << ']' << endl;
}

///////////////////
// Data Structures
///////////////////
// - Stack
// Operates as LIFO (Last In First Out) structure where things are
// added to the end of the stack and pulled off the end first

// - Queue
// Operates as a FIFO (First In First Out) structure where
// things are added to the end and removed from the front

// - Deque (Double Ended Queue)
// Operates similary to a queue, but items can be removed or added
// at both ends. A queue and stack are usually special cases of a deque

// - Binary Tree
// A graph where each node has only two children and the nodes are
// arranged such that all nodes to the right are > the parent, and
// all nodes to the left are < the parent.
// This provides log(n) search and as such is the basis of many algorithms
// where possible

// - Heap
// Treats an array as an incomplete/imbalanced binary tree, which allows us
// to perform many sort and queuing operations in log(n) time
// by implementing different heapify functions to shape the heap
// and give it different properties
// The root node is at index 0 of the array, and the nodes are indexed:
//     0
//  1     2
// 3 4   5 6
// left(i) = 2(i + 1) - 1, right(i) = 2(i + 1)

///////////////////
// Algorithms
///////////////////

// 1) Sorting

// - Insertion Sort
// go forward through the array shifting the current
// value down into it's sorted position at the earlier 
// part of the array, through a series of swaps
// Time: O(n^2) Space: O(1)
void insertionSort(int* a, int length)
{
    for (int i = 1; i < length; ++i)
    {
        int v = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > v)
        {
            a[j + 1] = a[j];
            a[j] = v;
            --j;
        }
    }
}

// - Merge Sort
// recursively break the array into halves until we arrive at 1 element
// then merge the two halves into a temporary holding area by putting the smalest
// between each half into it first until both halves are exhausted
// Time O(n*lg(n)) Space: O(n)

void merge(int* left, int leftSize, int* right, int rightSize, int* mergeArea)
{
    if (leftSize > 1)
    {
        int half = leftSize / 2;
        merge(left, half, left + half, leftSize - half, mergeArea);
    }

    if (rightSize > 1)
    {
        int half = rightSize / 2;
        merge(right, half, right + half, rightSize - half, mergeArea + leftSize);
    }

    int mergeSize = leftSize + rightSize;
    int mergeIndex = 0;
    int leftIndex = 0;
    int rightIndex = 0;
    while (leftIndex < leftSize && rightIndex < rightSize)
    {
        if (left[leftIndex] < right[rightIndex])
        {
            mergeArea[mergeIndex++] = left[leftIndex++];
        }
        else
        {
            mergeArea[mergeIndex++] = right[rightIndex++];
        }
    }

    // Roll up any remaning data in the longer array
    while (leftIndex < leftSize)
    {
        mergeArea[mergeIndex++] = left[leftIndex++];
    }

    while (rightIndex < rightSize)
    {
        mergeArea[mergeIndex++] = right[rightIndex++];
    }

    // Copy the results back out to the original
    for(int i = 0; i < mergeSize; ++i)
    {
        left[i] = mergeArea[i];
    }
}

void mergeSort(int* a, int length)
{
    // Since mergesort is slower at a certain size and we need to take care of
    // the small length case anyway. we'll see this optimization in most sorts going forward
    if (length < 10)
    {
        insertionSort(a, length);
        return;
    }

    // This may not work for sufficiently large lengths
    int* mergeArea = (int*)malloc(length * sizeof(int));
    int halfLength = length / 2;
    merge(a, halfLength, a + halfLength, length - halfLength, mergeArea);
    free(mergeArea);
}

// - Heap Sort
// Turns the array into a max heap, we can then pull the top off the heap
// to the back until out of elements and doing so will result in a sorted array
// Beneficial when you want n lg(n) complexity without using up space
// Time: O(n*lg(n)) Space: O(1)
void heapify(int* a, int length, int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    if (left < length && a[left] > a[index])
    {
        largest = left;
    }

    if (right < length && a[right] > a[largest])
    {
        largest = right;
    }

    if (largest != index)
    {
        int temp = a[largest];
        a[largest] = a[index];
        a[index] = temp;
        heapify(a, length, largest);
    }
}

void heapSort(int* a, int length)
{
    // turn into a max heap
    for (int i = length/2 - 1; i >= 0; --i)
    {
        heapify(a, length, i);
    }

    // swap first item with the end of the list, then heapify
    for (int i = length - 1; i > 0; --i)
    {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        heapify(a, i, 0);
    }
}

////////////////////
// Test code
////////////////////
#define ArrayCount(a) (sizeof(a) / sizeof(a[0]))

int main(int argc, char** argv)
{
    LARGE_INTEGER startTime;
    LARGE_INTEGER currentTime;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    double pcFrequency = double(frequency.QuadPart) / 1000.0;

    cout << "Inserton Sort" << endl;
    {
        int a[] = {20, 12, 13, 11, 7, 9, 2, 1};
        int length = ArrayCount(a);
        printArray(a, length);
        QueryPerformanceCounter(&startTime);
        insertionSort(a, length);
        QueryPerformanceCounter(&currentTime);
        printArray(a, length);
        double time = double(currentTime.QuadPart - startTime.QuadPart) / pcFrequency;
        cout << "Time " << time << endl;
    }

    cout << "Merge Sort" << endl;
    {
        int a[] = {20, 12, 13, 11, 7, 9, 2, 1};
        int length = ArrayCount(a);
        printArray(a, length);
        QueryPerformanceCounter(&startTime);
        mergeSort(a, length);
        QueryPerformanceCounter(&currentTime);
        printArray(a, length);
        double time = double(currentTime.QuadPart - startTime.QuadPart) / pcFrequency;
        cout << "Time " << time << endl;
    }

    cout << "Heap Sort" << endl;
    {
        int a[] = {20, 12, 13, 11, 7, 9, 2, 1};
        int length = ArrayCount(a);
        printArray(a, length);
        QueryPerformanceCounter(&startTime);
        heapSort(a, length);
        QueryPerformanceCounter(&currentTime);
        printArray(a, length);
        double time = double(currentTime.QuadPart - startTime.QuadPart) / pcFrequency;
        cout << "Time " << time << endl;
    }

    cout.flush();
    return 0;
}