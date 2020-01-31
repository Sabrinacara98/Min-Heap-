#include <iostream>
#include <string>
#include <vector>
#include <fstream>


/* Analysis of Algorithms 2
 * Assignment 2
 * Student Name: Sabrina Cara
 * Student Number: 150160914
 */

using namespace std;

//Class Event to store name, time and type of event(starting or ending)
class Event{
public:
    string nameStart;
    string nameEnd;
    int time;
    int type;
};
//function to swap two objects(parent and child, used in heapify)
void swap(Event  &x, Event &y){
    Event temp = x;
    x = y;
    y = temp;
}

class MinHeap{
public:
    vector<Event>events;
    int size;
    int heap_capacity;

    MinHeap(int capacity); //constructor for heap
    void Heapify (int ); //heapify function

    //we get index of parent and left, right child node in the array.
    int parent(int i) { return (i-1)/2; }

    int left(int i) { return (2*i + 1); }

    int right(int i) { return (2*i + 2); }

    // Extracts the root which is the minimum element
    Event extractMin();

    // Returns the value of root from min heap without popping it
    Event getMin() { return events[0]; }

    // Inserts a new event object
    void insertObject(Event object);

};

//constructor of heap by taking its size
MinHeap::MinHeap(int Capacity) {
    heap_capacity = 0;
    size = Capacity;
    vector<Event>events;
}
//function inserts objects one by one by checking also if they fulfill the min heap condition
void MinHeap::insertObject(Event object) {
    if(heap_capacity == size){
        cout << "Cannot insert node. Heap is full. " << endl;
    }
    heap_capacity++;
    int i = heap_capacity - 1;
    events.push_back(object);
    while(i!=0 && events[parent(i)].time > events[i].time){
        swap(events[i], events[parent(i)]);
        i = parent(i);
    }
}
//function extracts minimum value which is value of root
Event MinHeap::extractMin() {
    if(heap_capacity <= 0){
        cout <<"No more capacity !" <<endl;
    }
    if(heap_capacity == 1){
        heap_capacity--;
        return events[0];
    }
    Event root = events[0];
    events[0] = events[heap_capacity-1];
    heap_capacity--;
    Heapify(0); //we call heapify to make sure the remaining nodes are organized in such a way that fulfills the condition of min heap
    return root;
}
//recursive function to make sure all nodes of a heap fulfill the condition of the min heap, so that parent should always be smaller than children nodes.
void MinHeap::Heapify(int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l <heap_capacity && events[l].time < events[i].time) {
        smallest = l; //if left child has the smallest value we assign it to smallest
    }
    if (r < heap_capacity && events[r].time < events[smallest].time) {
        smallest = r;//if right child has the smallest value we assign it to smallest
    }
    if (smallest != i){
        swap(events[i], events[smallest]);//we swap the smallest so it can be parent node
        Heapify(smallest);
    }
}

int main(int argc, char * argv[]) {

    vector<Event>events;
    vector <int> maxValue;
    string Name, Filename;
    int Value, Value2;
    //If we don't have enough arguments, we display an error message, else we read file
    if (argc == 2) {
        Filename = argv[1];
    } else {
        cout << "Not enough arguments given." << endl;
    }
    ifstream myReadFile;
    myReadFile.open(Filename.c_str());

    //We create two event objects, one for starting events and one for ending events
    Event Object1;
    Event Object2;
    //We read the file line by line and store the values in objects

    while (myReadFile >> Name >> Value >> Value2) {
        Object1.nameStart = Name + " STARTED";
        Object1.time = Value;
        Object1.type = 1;
        events.push_back(Object1);

        Object2.nameEnd = Name + " ENDED";
        Object2.time = Value2;
        Object2.type = 2;
        events.push_back(Object2);
    }
    MinHeap m(events.size()); //We create min heap with the size of vector

    for (int i  = 0; i < events.size(); i++){
       m.insertObject(events[i]); //we insert the nodes one by one
    }
    int n = 1;
    int size = events.size();

    if(events.size() == 0){
        cout<<" NO EVENTS IN THIS FILE."<<endl;
        return 0 ;
    }

    // This part gets the minimum value (root), without extracting it.
    // If time doesn't match root time we show NO EVENT

    while(size!=0) {
        if (n != m.getMin().time) {
            cout << "TIME " << n << ": NO EVENT" << endl;
        }
        // If time matches root time, we check the type, starting or ending event and we display it accordingly
        while (n == m.getMin().time) {
            if (m.getMin().type == 1) {
                cout << "TIME " << m.getMin().time << ": " << m.getMin().nameStart << endl;
                m.extractMin();
                size--;
                if (size == 0) {
                    cout << "TIME " << n << ": NO MORE EVENTS, SCHEDULER EXITS" << endl;
                    break;
                }
            }
            else if (m.getMin().type == 2) {
                cout << "TIME " << m.getMin().time << ": " << m.getMin().nameEnd << endl;
                m.extractMin();
                size--;
                if (size == 0) {
                    cout << "TIME " << n << ": NO MORE EVENTS, SCHEDULER EXITS" << endl;
                    break;
                }
            }
            MinHeap m(size); //We create the min heap again this time with the new size (one less).
        }
        n++;
    }
return 0;
}

