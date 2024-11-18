
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

using std::clock_t;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; 

#include <chrono>
using std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::time_point;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

// Define a constant for the size of the arrays.
const int NUMBERS_SIZE = 50000;

// Function to generate a random integer between low and high (inclusive).
int genRandInt(int low, int high) {
    return low + rand() % (high - low + 1); // Calculate a random number in the range [low, high].
}

// Function to fill three arrays with random integers.
void fillArrays(int arr1[], int arr2[], int arr3[]) {
    for (int i = 0; i < NUMBERS_SIZE; ++i) { // Loop through each index up to NUMBERS_SIZE.
        arr1[i] = genRandInt(0, NUMBERS_SIZE); // Fill arr1 with a random integer.
        arr2[i] = arr1[i]; // Copy the value from arr1 to arr2.
        arr3[i] = arr1[i]; // Copy the value from arr1 to arr3.
    }
}

// Function to partition the array using the midpoint as the pivot.
int midpoint_Partition(int numbers[], int low, int high) {
    int midpoint = (low + high) / 2; // Calculate the midpoint index.
    int pivot = numbers[midpoint]; // Choose the midpoint value as the pivot.
    bool end_Partition = false; // Boolean flag to end the partition process.

    while (!end_Partition) { // Continue partitioning until the end_Partition flag is set to true.
        while (pivot < numbers[high]) { // While pivot is less than the number at high index,
            --high; // move the high index to the left.
        }
        while (numbers[low] < pivot) { // While the number at low index is less than the pivot,
            ++low; // move the low index to the right.
        }
        if (low >= high) { // If low index meets or surpasses high index,
            end_Partition = true; // set the end_Partition flag to true to end the loop.
        } else { // Otherwise,
            swap(numbers[low], numbers[high]); // swap the elements at low and high indices.
            ++low; // Move the low index to the right.
            --high; // Move the high index to the left.
        }
    }
    return high; // Return the high index as the partition point.
}

// Recursive quicksort function using the midpoint pivot.
void Quicksort_midpoint(int numbers[], int low, int high) {
    if (low >= high) { // Base case: if the segment has 1 or 0 elements,
        return; // return without doing anything.
    }

    int partition = midpoint_Partition(numbers, low, high); // Partition the array and get the partition point.

    Quicksort_midpoint(numbers, low, partition); // Recursively sort the left partition.
    Quicksort_midpoint(numbers, partition + 1, high); // Recursively sort the right partition.
}

// Function to partition the array using the median of three values as the pivot.
int medianOfThree_partition(int numbers[], int i, int k) {
    int midpoint = (i + k) / 2; // Calculate the midpoint index.
    int pivotIndex = 0; // Variable to store the pivot index.

    // Determine the median of the three: start, middle, and end.
    if ((numbers[i] < numbers[midpoint] && numbers[midpoint] < numbers[k]) || 
        (numbers[k] < numbers[midpoint] && numbers[midpoint] < numbers[i])) {
        pivotIndex = midpoint; // If the midpoint is the median, set pivotIndex to midpoint.
    } else if ((numbers[midpoint] < numbers[i] && numbers[i] < numbers[k]) || 
               (numbers[k] < numbers[i] && numbers[i] < numbers[midpoint])) {
        pivotIndex = i; // If the start is the median, set pivotIndex to start.
    } else {
        pivotIndex = k; // Otherwise, the end is the median, so set pivotIndex to end.
    }

    int pivot = numbers[pivotIndex]; // Choose the pivot value from the pivot index.
    swap(numbers[pivotIndex], numbers[k]); // Move the pivot to the end of the array.
    int left = i; // Left index starts at the beginning of the segment.
    int right = k - 1; // Right index starts just before the pivot.
    while (left <= right) { // Continue until left index surpasses right index.
        while (numbers[left] < pivot) { // While the element at left is less than the pivot,
            ++left; // move the left index to the right.
        }
        while (pivot < numbers[right]) { // While the pivot is less than the element at right,
            --right; // move the right index to the left.
        }
        if (left <= right) { // If left index has not surpassed right index,
            swap(numbers[left], numbers[right]); // swap the elements at left and right indices.
            ++left; // Move the left index to the right.
            --right; // Move the right index to the left.
        }
    }
    swap(numbers[left], numbers[k]); // Place the pivot in its correct position.
    return left; // Return the left index as the partition point.
}

// Recursive quicksort function using the median of three as the pivot.
void Quicksort_medianOfThree(int numbers[], int i, int k) {
    if (i < k) { // If the segment has more than one element,
        int partition = medianOfThree_partition(numbers, i, k); // Partition the array and get the partition point.
        Quicksort_medianOfThree(numbers, i, partition - 1); // Recursively sort the left partition.
        Quicksort_medianOfThree(numbers, partition + 1, k); // Recursively sort the right partition.
    }
}

// Function to perform insertion sort on an array.
void InsertionSort(int numbers[], int numbersSize) {
    for (int i = 1; i < numbersSize; i++) { // Loop through each element starting from the second element.
        for (int j = i; j > 0; j--) { // Inner loop to compare the current element with the previous elements.
            if (numbers[j] < numbers[j - 1]) { // If the current element is less than the previous element,
                swap(numbers[j], numbers[j - 1]); // swap them.
            }
        }
    }
}


int main() {
  vector<int> sample;
  sample.reserve(NUMBERS_SIZE);
  for(int i=0; i<NUMBERS_SIZE; ++i) {
    sample.push_back(rand() % (NUMBERS_SIZE + 1));
  }
  
  int test_sizes[4] = { 10, 100, 1000, 50000 };
  for(int i=0; i<4; ++i) {
    int size = test_sizes[i];
    cout << endl;
    cout << "-------------------- size " << size << " --------------------" << endl;
  }
  return 0;
}
