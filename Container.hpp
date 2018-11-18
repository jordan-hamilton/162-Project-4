/*********************************************************************
** Description: Specification file for the Container class.
*********************************************************************/

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

class Container {

  struct ContainerNode {

    ContainerNode* next;
    ContainerNode* prev;
    int val;

  };

  public:
    Container();
    ~Container();
    bool isEmpty();
    void addBack(int val);
    void addFront(int val);
    int getFront();
    void removeFront();
    void printContainer();

  private:
    ContainerNode* head;

};

#endif
