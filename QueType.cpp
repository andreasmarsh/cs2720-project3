#include <iostream>
using namespace std;
#include "QueType.h"

template <class ItemType>
QueType<ItemType>::QueType()
// Class constructor
{
    maxQue = 500;
    front = maxQue-1;
    rear = maxQue-1;
    items = new ItemType[maxQue];
}

template <class ItemType>
QueType<ItemType>::QueType(int max)
// Parameterized class constructor
{
    maxQue = max;
    front = maxQue-1;
    rear = maxQue-1;
    items = new ItemType[maxQue];
}

template <class ItemType>
QueType<ItemType>::~QueType()
// Class deconstructor
{
    delete[] items;
}

template <class ItemType>
void QueType<ItemType>::makeEmpty()
// Function: Initializes the queue to an empty state.
// Post: Queue is empty
{
    rear = front;
    items[((front + 1) % maxQue)].setCustomerName("error"); // sets first value to NULL
}

template <class ItemType>
bool QueType<ItemType>::isEmpty() const
// Function: Determines whether the queue is empty.
// Post: Function value = (queue is empty)
{
    // if rear == front and first value is NULL
    if ((rear == front) && (items[((front + 1) % maxQue)].getCustomerName() == "error")) {
        return true;
    } else {
        return false;
    }
}

template <class ItemType>
bool QueType<ItemType>::isFull() const
// Function: Determines whether the queue is full.
// Post: Function value = (queue is full)
{
    // if rear == front and first value is not NULL
    if ((front == rear) && items[((front + 1) % maxQue)].getCustomerName() != "error") {
        return true;
    } else {
        return false;
    }
}

template <class ItemType>
void QueType<ItemType>::enqueue(ItemType newItem)
// Function: Adds newItem to the rear of the queue.
// Post: If (queue is full) FullQueue exception is thrown
//       else newItem is at rear of queue.
{
    if (isFull()) { // no space to add element
        throw QueueOverflow();
        return;
    }

    rear = ((rear + 1) % maxQue); // move up rear
    items[rear] = newItem; // set rear
    return;
}

template <class ItemType>
void QueType<ItemType>::dequeue(ItemType& item)
// Function: Removes front item from the queue and returns it
//in item.
// Post: If (queue is empty) EmptyQueue exception is thrown
//       and item is undefined
//       else front element has been removed from queue and
//       item is a copy of removed element.
{
    if (isEmpty()) { // nothing to deque
        throw QueueUnderflow();
        return;
    }

    item = items[((front + 1) % maxQue)]; // set item to first element
    items[((front + 1) % maxQue)].setCustomerName("error"); // set first element to NULL
    front = ((front + 1) % maxQue); // move up front of queue
}

/*
template <class ItemType>
ItemType QueType<ItemType>::min()
// returns the item with min departure time without
//removing the item from the queue
{
    if (!isEmpty()) { // if front exists, return it
        int mini;
        int minVal = items[((front + 1) % maxQue)].getCustomerDeparture();
        for (i = front + 2; i < front + length; i++) {
            if (items[((i) % maxQue)].getCustomerDeparture() < minVal) {
                mini = i;
                minVal = items[((i) % maxQue)].getCustomerDeparture();
            }
        }
        return items[((mini) % maxQue)];
    } else {
        throw QueueUnderflow(); // empty Que
    }
    }*/

template <class ItemType>
ItemType QueType<ItemType>::peek()
// returns the item at the front of the queue without
//removing the item from the queue
{
    if (!isEmpty()) { // if front exists, return it
        return items[((front + 1) % maxQue)];
    } else {
        throw QueueUnderflow(); // empty Que
    }
}

template <class ItemType>
int QueType<ItemType>::length()
// Function: returns the number of items in the queue
{
    if (isFull()) { // if full length is maxQue
        return maxQue;
    } else if (isEmpty()) { // if empty length is 0
        return 0;
    } else {
        if (front == (maxQue - 1)) { // if front is at end of array
            return (rear + 1);
        } else if (front > rear) { // if front comes after rear
            return ((maxQue - (front + 1) + (rear + 1)));
        } else if (front < rear) { // if front comes before rear
            return (rear - front);
        }
    }
    return 0; // resolves warning, all previous if's catch all options
}

template <class ItemType>
void QueType<ItemType>::printQueue(ofstream& outFile)
// displays QueueItems
{
    if (isEmpty()) { // if empty length is 0
        outFile << "Queue is Empty\n\n";
        return;
    } else {
        if (front == (maxQue - 1)) { // if front is at end of array
            for (int i = 0; i <= rear; i++) {
                outFile << items[i];
            }
            outFile << "\n";
            return;
        } else if (front > rear) { // if front comes after rear
            for (int i = (front + 1); i < maxQue; i++) {
                outFile << items[i];
            }
            for (int i = 0; i <= rear; i++) {
                outFile << items[i];
            }
            outFile << "\n";
            return;
        } else if (front < rear) { // if front comes before rear
            for (int i = (front + 1); i <= rear; i++) {
                outFile << items[i];
            }
            outFile << "\n";
            return;
        } else { // queue is full
            for (int i = (front + 1); i < maxQue; i++) {
                outFile << items[i];
            }
            for (int i = 0; i <= rear; i++) {
                outFile << items[i];
            }
            outFile << "\n";
            return;
        }
    }
}
