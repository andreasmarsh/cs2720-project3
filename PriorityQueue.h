#pragma once

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include "Header.h"

// Exception classes
/*
class QueueOverflow{
};

class QueueUnderflow {
}; */

//LL Node definition
template <class ItemType>
struct QNode {
    ItemType info;
    int priority;
    QNode<ItemType>* next;
};

template <class ItemType>
class PriorityQueue
{
public:
    PriorityQueue();
    // Class constructor.

    ~PriorityQueue();
    // Class destructor.

    void makeEmpty();
    // Function: Initializes the queue to an empty state.
    // Post: Queue is empty.

    bool isEmpty() const;
    // Function: Determines whether the queue is empty.
    // Post: Function value = (queue is empty)

    bool isFull() const;
    // Function: Determines whether the queue is full.
    // Post: Function value = (queue is full)

    void enqueue(ItemType newItem, int priority);
    // Function: Adds newItem to the rear of priority group.
    // Post: If (queue is full) FullQueue exception is thrown
    //       else newItem is at rear of priority group.

    void enqueue(ItemType newItem);
    // Function: Adds newItem to the rear of priority group 1.
    // Post: If (queue is full) FullQueue exception is thrown
    //       else newItem is at rear of priority group.

  void dequeue(ItemType& item);
    // Function: Removes front item from the queue and returns it
    //in item.
    // Post: If (queue is empty) EmptyQueue exception is thrown
    //       and item is undefined
    //       else front element has been removed from queue and
    //       item is a copy of removed element.
  ItemType peek();
	// returns the item at the front of the queue without
		//removing the item from the queue
  int peekPriority();
	// returns the item at the front of the queue priority group without
		//removing the item from the queue
  int getLength();
	// Function: returns the number of items in the queue
  void printQueue(ofstream&);
  // displays QueueItems
private:
  QNode<ItemType>* listData;
  int length;

  // Function: Searches the list for item and returns a pointer to item's predecessor node.
  //pre: list is initialized
  // post: (1) If item is in the list, function value =  true
  //       (2) if item is not in the list, function value is false
  //       (3) predecessor contains the address of item's predecessor
  //node ( i.e node with largest value < item's key)
  //        if no predescessor exit, predecessor is set to NULL.
  void findItem(int priority, QNode<ItemType>*& predecessor);
};

#endif
