// Source: given in class for a weekly assignment
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include <Arduino.h>
// #include <cassert>

using namespace std;

/*
  Practice problems:
    - implement insertBack()

    - implement insertAfter(), which is like insertBefore() except the item
      should appear after the one you insert

      HINT: Do you really need to juggle pointers or can you do it using
      the functions that already exist?

    - implement a method remove(const T& item) that will remove the first
      occurrence of the item in the list

    - implement a method removeAll(const T& item) that will remove all
      occurrences of the item in the list in O(n) time
*/

// struct for holding an item and pointers to the next and previous node
template <class T>
struct ListNode {
  // constructor
  ListNode(const T& item, ListNode<T> *prev = NULL, ListNode<T> *next = NULL) {
    this->item = item;
    this->prev = prev;
    this->next = next;
  }

  T item;
  ListNode<T> *next, *prev;
};

// A linked list, just as discussed in the slides.
template <class T>
class LinkedList {
public:
  LinkedList() {
    first = last = NULL;
    listSize = 0;
  }

  ~LinkedList() {
    // delete one item at a time until the list is empty
    while (size() > 0) {
      removeFront();
    }
  }

  void insertFront(const T& item);
  void insertBack(const T& item);

  void removeFront();
  void removeBack();

  // assumes the node is in this list
  // will insert the item just before this node in the list
  void insertBefore(const T& item, ListNode<T> *node);
  void insertAfter(const T& item, ListNode<T> *node);


  // assumes the node is in this list
  void removeNode(ListNode<T> *node);

  unsigned int size() const { return listSize; }

  // Get ListNode pointers to the first and last items in the list,
  // respectively. Both return a pointer to NULL if the list is empty.
  ListNode<T>* getFirst() const { return first; }
  ListNode<T>* getLast() const { return last; }

  // Find and return a pointer to the first node with the item.
  // Returns the NULL pointer if the item is not in the list.
  ListNode<T>* find(const T& item) const;

private:
  ListNode<T> *first, *last;
  unsigned int listSize;
};

template<class T>
void LinkedList<T>::insertFront(const T& item) {
  // get a new ListNode to hold the item
  // it points back to NULL and ahead to the first node in current list
  ListNode<T> *node = new ListNode<T>(item, NULL, first);
  // assert(node != NULL);

  // if the list is not empty, have the first node point back to the new node.
  if (first != NULL) {
    first->prev = node;
  }
  else {
    // otherwise, this new node is also the last node
    last = node;
  }

  // update the first node
  first = node;
  listSize++;
}

// YOU TRY IT
// implement the method insertBack
// try sketching out a diagram to see how the pointers should be reassigned
// don't forget to cover the case where the list is empty
template<class T>
void LinkedList<T>::insertBack(const T& item) {
  ListNode<T> *node = new ListNode<T>(item, last, NULL);
  // assert(node != NULL);

  // if the list is not empty, have the last node point forward to the new node.
  if (last != NULL) {
    last->next = node;
  }
  else {
    // otherwise, this node is also the first node
    first = node;
  }

  // update last node
  last = node;
  listSize++;
}


template <class T>
void LinkedList<T>::insertBefore(const T& item, ListNode<T> *link) {
  // if the link is the start of the list, just call insertFront
  if (link == first) {
    insertFront(item);
    return;
  }

  // get a new node to hold this item
  ListNode<T> *node = new ListNode<T>(item, link->prev, link);
  // assert(node != NULL);

  // redirect surrounding links, the order you do this is important!
  link->prev->next = node;
  link->prev = node;
  listSize++;
}


// YOU TRY IT
// implement the method insertAfter to insert an item after a given node
// template<class T>
// void LinkedList<T>::insertAfter(const T& item, ListNode<T> *node) {

// }


template <class T>
void LinkedList<T>::removeFront() {
  // assert(first != NULL);

  ListNode<T> *toDelete = first;

  // if this is not the only item in the list, redirect
  // the prev pointer of the 2nd item to NULL
  if (first != last) {
    first->next->prev = NULL;
  }
  else {
    // otherwise, the list will become empty
    last = NULL;
  }

  // works even if the list had size 1
  first = first->next;

  delete toDelete;
  listSize--;
}

template <class T>
void LinkedList<T>::removeBack() {
  // assert(first != NULL);

  ListNode<T> *toDelete = last;

  // if this is not the only item in the list, redirect
  // the next pointer of the 2nd last item to NULL
  if (first != last) {
    last->prev->next = NULL;
  }
  else {
    // the list will become empty
    first = NULL;
  }

  // works even if the list had size 1
  last = last->prev;

  delete toDelete;
  listSize--;
}


template <class T>
void LinkedList<T>::removeNode(ListNode<T>* node) {
  // if we are removing the first or the last item, call that function
  if (node == first) {
    removeFront();
    return; // something followed the first node
  }

  if (node == last) {
    removeBack();
    return; // nothing followed the last node
  }

  // bypass the node we are deleting by redirecting pointers of surrounding nodes
  node->prev->next = node->next;
  node->next->prev = node->prev;

  delete node;
  listSize--;
}

template <class T>
ListNode<T>* LinkedList<T>::find(const T& item) const {
  // crawl along the list until the item is found
  ListNode<T>* node = first;
  while (node != NULL && node->item != item) {
    node = node->next;
  }

  // returns NULL if the item was not found
  return node;
}

#endif
