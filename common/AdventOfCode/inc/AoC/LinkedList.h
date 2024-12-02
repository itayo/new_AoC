//
// Created by snyg9u on 2023-12-08.
//

#ifndef ADVENTOFCODE_COMMON_ADVENTOFCODE_SRC_LINKEDLIST_H_
#define ADVENTOFCODE_COMMON_ADVENTOFCODE_SRC_LINKEDLIST_H_

namespace AoC {

#include <iostream>
using namespace std;

// Making a node struct containing an int data and a pointer
// to next node
struct Node {
  int data;
  Node *next;

  // Parameterised constructor with default argument
  Node(int val=0) :data(val),next(nullptr){}
  // Parameterise constructor
  Node(int val, Node *tempNext):data(val),next(tempNext){}
};

class LinkedList
{
  // Head pointer
  Node* head;

 public:
  // default constructor. Initializing head pointer
  LinkedList():head(nullptr)
  {
  }

  // inserting elements (At start of the list)
  void insert(int val)
  {
    // make a new node
    Node* new_node = new Node(val);

    // If list is empty, make the new node, the head
    if (head == nullptr)
    {
      head = new_node;
    }
      // else, make the new_node the head and its next, the previous
      // head
    else
    {
      new_node->next = head;
      head = new_node;
    }
  }

    bool search(int val)
  {
    Node* temp = head;
    while(temp != nullptr)
    {
      if (temp->data == val)
        return true;
      temp = temp->next;
    }
    return false;
  }

  void remove(int val)
  {
    Node* temp = head;
    if (temp != nullptr && temp->data == val)
    {
      head = temp->next;
      delete temp;
      return;
    }
    else
    {
      Node* curr = head;
      while(temp != nullptr && temp->data != val)
      {
        curr = temp;
        temp = temp->next;
      }
      if(!temp)
      {
        return;
      }

      curr->next = temp->next;
      delete temp;
    }
  }

  void display()
  {
    Node* temp = head;
    while(temp != nullptr)
    {
      cout << temp->data << " ";
      temp = temp->next;
    }
    cout << endl;
  }
};

} // AoC

#endif //ADVENTOFCODE_COMMON_ADVENTOFCODE_SRC_LINKEDLIST_H_
