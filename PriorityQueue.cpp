#include <iostream>
using namespace std;
#include "PriorityQueue.h"

template <class ItemType>
PriorityQueue<ItemType>::PriorityQueue()
// Class constructor
// Pre: None
// Post: List is intialized
{
    length = 0;
    listData = NULL;
}

template <class ItemType>
PriorityQueue<ItemType>::~PriorityQueue()
// Class deconstructor
// Deallocates all dynamically allocated data members
// Pre: List is initalized
{
    makeEmpty();
}

template <class ItemType>
void PriorityQueue<ItemType>::makeEmpty()
// Function: Deallocates all dynamically allocated data members.
// Reinitializes the list to empty state.
// Pre: None
// Post: Queue is empty
{
    QNode<ItemType>* tempPtr;
    while (listData != NULL) {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
    length = 0;
}

template <class ItemType>
bool PriorityQueue<ItemType>::isEmpty() const
// Function: Determines whether the queue is empty.
// Pre: Queue is initialized
// Post: Function value = (queue is empty)
{
    if (listData == NULL) {
        return true;
    } else {
        return false;
    }
}

template <class ItemType>
bool PriorityQueue<ItemType>::isFull() const
// Function: Determines whether the queue is full.
// Pre: Queue is initialized
// Post: Function value = (queue is full)
{
    QNode<ItemType>* location;
    try
    {
        location = new QNode<ItemType>;
        delete location;
        return false;
    }
    catch(const std::bad_alloc&)
    {
        return true;
    }
}

template <class ItemType>
void PriorityQueue<ItemType>::enqueue(ItemType newItem, int priority)
// Function: Adds newItem to the rear of its priority group.
// Post: If (queue is full) FullQueue exception is thrown
//       else newItem is at end of priority group
{
    if (isFull()) { // no space to add element
        throw QueueOverflow();
        return;
    }

    if (priority <= 0) priority = 1; // changes all 0 or negative priorities to 1

    QNode<ItemType>* predecessor = NULL;
    findItem(priority, predecessor);

    QNode<ItemType>* newNode = new QNode<ItemType>;
    newNode->info = newItem;
    newNode->priority = priority;
    // pred is NULL if the list is empty or priority is smaller than listData->info
    // thus newNode should be set to the front
    if (predecessor == NULL) {
        newNode->next = listData;
        listData = newNode;
    } else {
        newNode->next = predecessor->next;
        predecessor->next = newNode;
    }
    length++;
    return;
}

template <class ItemType>
void PriorityQueue<ItemType>::enqueue(ItemType newItem)
// Function: Adds newItem to the rear of priority group 1.
// Post: If (queue is full) FullQueue exception is thrown
//       else newItem is at end of priority group
{
    if (isFull()) { // no space to add element
        throw QueueOverflow();
        return;
    }

    int priority = 1;

    QNode<ItemType>* predecessor = NULL;
    findItem(priority, predecessor);

    QNode<ItemType>* newNode = new QNode<ItemType>;
    newNode->info = newItem;
    newNode->priority = priority;
    // pred is NULL if the list is empty or priority is smaller than listData->info
    // thus newNode should be set to the front
    if (predecessor == NULL) {
        newNode->next = listData;
        listData = newNode;
    } else {
        newNode->next = predecessor->next;
        predecessor->next = newNode;
    }
    length++;
    return;
}

template <class ItemType>
void PriorityQueue<ItemType>::dequeue(ItemType& item)
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

    item = listData->info;
    QNode<ItemType>* tempPtr = listData;
    listData = listData->next;
    delete tempPtr;
    length--;
    return;
}

template <class ItemType>
ItemType PriorityQueue<ItemType>::peek()
// returns the item at the front of the queue without
//removing the item from the queue
{
    if (!isEmpty()) { // if front exists, return it
        return listData->info;
    } else {
        throw QueueUnderflow(); // empty Queue
    }
}

template <class ItemType>
int PriorityQueue<ItemType>::peekPriority()
// returns the item at the front of the queue without
//removing the item from the queue
{
    if (!isEmpty()) { // if front exists, return its priority
        return listData->priority;
    } else {
        throw QueueUnderflow(); // empty Queue
    }
}

template <class ItemType>
int PriorityQueue<ItemType>::getLength()
// Function: returns the number of items in the queue
{
    return length;
}

template <class ItemType>
void PriorityQueue<ItemType>::printQueue(ofstream& outFile)
// displays QueueItems
{
    QNode<ItemType>* p = listData;
    for (int i = 0; i < length; i++) {
        outFile << p->info.getCustomerName() << " ";
        if (p->next != NULL){
            p = p->next;
        }
    }
    if (length == 0) outFile << "Empty Queue";
    outFile<<"\n";
}

template <class ItemType>
void PriorityQueue<ItemType>::findItem(int priority, QNode<ItemType>*& predecessor)
// Searches the list for end of given priority
// group and returns a pointer to the item's
// predecessor node.
// Pre: list is initialized
// Post: (1) if item is in the list, function value = true
//       (2) if the item is not in the list, function value is false
//       (3) predecessor contains the address of item's predecessor node
//           if no predecessor exist, predecessor is set to NULL
{
    predecessor = NULL;
    if (listData == NULL || priority < listData->priority) {
        return;
    }

    if (isFull()){
        throw QueueOverflow();
        return;
    }

    QNode<ItemType>* location;
    location = listData;

    if (length == 1 && priority >= listData->priority) {
        predecessor = location;
        return;
    }

    while (location->next != NULL) { // && !found) {
        if(priority < location->next->priority){
            predecessor = location;
            return;
        } else {
            location = location->next;
            predecessor = location;
        }
    }
    return;
}
