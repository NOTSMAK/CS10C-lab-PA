#include <iostream>
#ifndef stack_h
#define stack_h
using namespace std;
#include<stdexcept>
template<typename T>
class stack {
private:
    static const int MAX_SIZE = 20; // Sets the max size to 20 using const so the its never changed
    T data[MAX_SIZE]; // creates an array of T type using the mex_size (storage of the stack)
    int size; // size to keep track of the stacks size
public:
stack(){
    size = 0; // a new stack starts of with size 0 after its created 
    }
void push(T val) { 
    if(size >= 20){ // if size is greated that 20 than new data can't be added to the stack(array) therefore gives an overflow error
        throw overflow_error("Called push on full stack.");
    }
    if(empty()){ // if its empty then val is simply pushed into the stack
        data[0] = val;
        size++; // the size is increased to 1 as there is a new data in the empty stack
        return;
    }

    if(size == 1){ // if size is one 
        size++; // size increased as a new data is being added to the stack
        T hold = data[0]; // adds val to the front and moves the old front to the back
        data[0] = val; // val is the new front of the stack
        data[1] = hold; // the old data is the second data in stack
        return;
    }
    else{ // the last case where data is being added to the front while the rest is being pushed back
        size++; // size increased as a new data is being added to the stack
        T holdData[size]; // new array to change the order of vals 
        holdData[0] = val; // val is added as the first value in stack
        int i = 1;
        while(i != size){ // after the first value the rest of the old array is added to the new array
            holdData[i] = data[i-1];
            i++;
        }
        i = 0;
        while(i != size){ // old arrays values are updated with new array
            data[i] = holdData[i];
            i++;
        }   
    }
}
void pop() { // poping the front of the array
    if(empty()){ // if empty then return error
        throw out_of_range("Called pop on empty stack.");
    } 
    if(size == 1){ // case where size is 1 the size is decreased by 1 and the value at array[0] can't be reached
       size--;
       return;
    }
    else{
    int i = 0;
    T holdData[size]; // new hold array with the current size is created 
    while(i != size){ // adds all values of the array after the first one to the hold array in order to delete the first one
        if((i+1)<= size){
            holdData[i] = data[i+1];
        }
        i++;
    }
    
    i = 0;
    while(i != size){ // updates the stack using data from holdData as the first value of the stack is erased
        data[i] = holdData[i];
        i++;
    }
    size--;
  
    }
}
void pop_two() {
    if(empty()){ // if size  ==  0 then calls error messaga as pop wont work
        throw out_of_range("Called pop_two on empty stack.");
    }
    if(size == 1){ // if size  == 1 then calls error message as poping twice is not possible
        throw out_of_range("Called pop_two on a stack of size 1.");
    }
    else{ // deletes two values from the top of the stack using pop
        pop(); 
        pop();
    }
}
T top(){
    if(empty()){ // if the stack is empty gives an error message
       throw underflow_error("Called top on empty stack.");
    }
    else {
        return data[0]; // returns the first value
    }
}
bool empty(){
   return size == 0; // returns true if the size  == 0
}
};



#endif