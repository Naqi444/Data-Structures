// CMSC 341 - Fall 2020 - Project 0
// queue.h: a templated, linked list-based queue implementation

// Assignment:
//   (1) Complete the copy constructor
//   (2) Complete the assignment operator
//   (3) Complete the destructor
//   (4) Write a test program (mytest.cpp) to test copy and assignment
//   (5) Verify destructor by running the test program in Valgrind

#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <exception>

using std::ostream;
using std::cout;
using std::endl;
using std::range_error;

// Forward declarations
template <class T> class Queue;
template <class T> class Node;
template <class T> ostream& operator<<(ostream&, const Node<T>&);

// Node class for linked list
template <class T>
class Node {

  friend Queue<T>;
  
public:
  Node(T data = T(), Node<T> *next = nullptr) {
    _data = data;
    _next = next;
  }

  friend ostream& operator<< <T>(ostream &sout, const Node<T> &x);
  
private:
  T _data;
  Node *_next;
};

// Overloaded insertion operator.  Must be overloaded for the template
// class T, or this won't work! For primitive types in C++ such as string 
// or int this is alredy overloaded
template <class T>
ostream& operator<<(ostream &sout, const Node<T> &x) {
  sout << "Data: " << x._data;
  return sout;
}


// Queue class.  Linked-list implementation of a queue. Uses the Node
// class.
template <class T>
class Queue {
public:
  // Constructor
  Queue();

  // Copy constructor, assignment operator, and destructor
  // DO NOT IMPLEMENT HERE.  SEE BELOW.
  Queue(const Queue &rhs);
  const Queue& operator=(const Queue& rhs);
  ~Queue();

  // Queue operations: enqueue(), head(), and dequeue()
  void enqueue(const T& data);//inserts at the end
  const T& head() const;      //returns the head value
  void dequeue();             //removes from the head           

  // Helpful functions
  bool empty() const;  // Returns 'true' if queue is empty
  void dump() const;   // Dump contents of the linked list

private:
  Node<T> *_head;

  // ***************************************************
  // Any private helper functions must be delared here!
  // ***************************************************
  
};

template <class T>
Queue<T>::Queue() {
  _head = nullptr;
}

template <class T>
Queue<T>::Queue(const Queue<T>& rhs) {
  
  // ********************************
  // Implement the copy constructor
  // ********************************
  //Checking for self assignment
  if (&rhs != this){
    //Check if source queue is empty
    if(rhs.empty()){
      _head = nullptr;
    } else {
      _head = nullptr;
      Node<T> *tmp = rhs._head;

      do{
        enqueue(tmp->_data);
        tmp = tmp->_next;
      } while(tmp!=nullptr);
    }
  }
}

template <class T>
const Queue<T>& Queue<T>::operator=(const Queue<T>& rhs) {

  // **********************************
  // Implement the assignment operator
  // **********************************
  //Checking for self-assignment
  if(&rhs !=this){

    //To clear already existing contents of the Queue
    while(not this->empty()){
      dequeue();
    }

    //To check if the copied queue is empty
    if(rhs.empty()){
      _head=nullptr;
      return *this;
    }else{
      _head = nullptr;
      Node<T> *tmp = rhs._head;
      do{
      enqueue(tmp->_data);
      tmp = tmp->_next;
      } while(tmp!=nullptr);
      tmp = nullptr;
      return *this;
    }
  }else{
    return *this;
  }
}

template <class T>
Queue<T>::~Queue() {

  // *************************
  // Implement the destructor
  // *************************

  while(not empty()){
    dequeue();
  }
}

template <class T>
void Queue<T>::enqueue(const T& data) {
  Node<T> *newPtr = new Node<T>(data);
  Node<T> *tempPtr;
  if (_head == nullptr){
    _head = newPtr;
  }
  else{
    tempPtr = _head;
    while ( tempPtr->_next != nullptr ) {
        tempPtr = tempPtr->_next;
    }
    tempPtr->_next = newPtr;
  }
}

template <class T>
const T& Queue<T>::head() const {
  if ( empty() ) {
    throw range_error("Queue<T>::head(): attempt to read empty Queue.");
  }

  return _head->_data;
}

template <class T>
void Queue<T>::dequeue() {
  if ( empty() ) {
    throw range_error("Queue<T>::dequeue(): attempt to dequeue an empty Queue.");
  }

  Node<T> *tmpPtr = _head->_next;
  delete _head;
  _head = tmpPtr;
}

template <class T>
bool Queue<T>::empty() const {
  return _head == nullptr;
}

template <class T>
void Queue<T>::dump() const {
  Node<T> *nodePtr = _head;
  while ( nodePtr != nullptr ) {
    cout << nodePtr->_data << endl;
    nodePtr = nodePtr->_next;
  }
}

#endif