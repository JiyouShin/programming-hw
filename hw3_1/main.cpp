#include <iostream> 
#include <climits> 
#include <queue>
#include <cmath>
using namespace std; 

#include "functions.hpp"
  
// Driver program to test above functions 
int main() 
{ 
    MaxHeap h; 
    h.enqueue(10);
    h.enqueue(30);
    h.enqueue(40);    
    h.enqueue(500);    
    h.enqueue(80);
    h.enqueue(170);
    h.enqueue(1000);
    h.enqueue(180);
    h.enqueue(180);
    h.enqueue(80);
    h.enqueue(90);
    h.enqueue(250);
    h.enqueue(580);

    h.dequeue();
    h.dequeue();

    h.printHeap();

    cout << "Maximum value of the heap: " << h.getMax()->val << endl; 

    return 0; 
} 