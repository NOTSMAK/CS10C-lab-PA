#ifndef __HEAP_H
#define __HEAP_H

#include "PrintJob.h"

const int MAX_HEAP_SIZE = 10;

class Heap {
private:
  PrintJob* arr[MAX_HEAP_SIZE];   // Max size hold Pring Job
  int numItems;   // keeps track of the amount of nodes in the heap
 
public:
  Heap(); // default heap
  ~Heap(); // heap deconstructor
  Heap(const Heap&) = delete; // heap copy operator 
  Heap& operator=(const Heap&) = delete;  // heap cpy operator
  void enqueue ( PrintJob* ); // to add new elements to the heap
  void dequeue (); //delete elements from the heap
  PrintJob* highest (); // gives the nodes with the higest priority 
  void print (); // prints the highest Printjob Node
private:
  void trickleDown(int); // helper fuction in dequeue to move the root down
};
#endif