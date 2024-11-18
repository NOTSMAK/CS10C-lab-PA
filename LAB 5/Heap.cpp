#include "Heap.h"
#include <iostream>
#include <algorithm>
using namespace std;

Heap::Heap() {
	numItems = 0; // new heaps starts with numItems as 0
}
Heap::~Heap (){
 // deletes every elements in arr as they are being added as dinamic allocated memories in main
}

void Heap::enqueue(PrintJob *Job) { 
    
	if(numItems < MAX_HEAP_SIZE) { // Only adds elements if numItem is less than max size
		arr[numItems] = Job; // adds job to the end of the array 
    int Child = numItems; // Child holds the newly added element of arr. it is the last element 
    PrintJob *holdJob = nullptr;
    int Parent = (numItems-2)/2; // Parent of the newly added element. parent can be found by subtracting numItems by 2 and dividng it by 2 
		while(Child >= 1 && arr[Child]->getPriority() > arr[Parent]->getPriority()) { // if child isn't less than the root and childs prioirty is greater than its parent then the loop continues
        holdJob = arr[Child]; // holds child for swap
        arr[Child] = arr[(Child-1)/2]; // parent and child are swapped
        arr[(Child-1)/2] = holdJob; // parent and child are swapped
         Child = (Child-1)/2; // child is updated for next interation
         Parent =(Child-2)/2; // parent is updated for next iteration
    }
		numItems++; // the number of total elements in the list is incremented as new item has just been added 
	}
    else {
        return; 
    }
}

void Heap::dequeue() {
	if(numItems == 1) { // case: checks if the size is 1
		numItems = 0;
		return;
	}
	if(numItems > 1) { // other case: if size is greater
		arr[0] = arr[numItems-1]; // arr[0] becomes the last node
		arr[numItems-1] = 0; // the last node is deleted 
		numItems--; // size is decremented once as the first node is the only node thats been deleted from the heap
		trickleDown(0); // helper function to fix the positions of the nodes to keep arr[] as a proper max heap
	}
}

PrintJob* Heap::highest() {
	if(numItems == 0) { // case: if there are no nodes in array
        return 0;
    }
    return arr[0]; // else it returns the first node as it has the highest priority
}

void Heap::print() { 
	if(numItems == 0) {
        return;
    }
    else { // prints the first node with the proper spacing and text use
        cout << "Priority: " << arr[0]->getPriority();
        cout << ", Job Number: " <<  arr[0]->getJobNumber();
        cout << ", Number of Pages: " <<  arr[0]->getPages() << endl;
    }
    return;
}

void Heap::trickleDown(int rootNode) { // used by dequeue to properly swap nodes into the correct place
	for(int j = 0; j < numItems; j++) { // loops until j increases to the same number as the numItems
		if(arr[rootNode]->getPriority() < arr[j]->getPriority()) // if the arr[rootNode] is < then the current node thats being checked than both of the nodes are swapped
        {
            PrintJob* holdJob = arr[rootNode];  // holds arr[rootNode]
            arr[rootNode] = arr[j]; // arr[j] because the new rootNode
            arr[j] = holdJob; // rootNode is swapped with arr[j] as it is less than arr[j]
            // this proccess continues until all nodes are in proper order 
        }
	}	
}
