/*********************************************************************
** Description: Specification file for the Container class.
*********************************************************************/

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

#include "Character.hpp"

class Container {

  struct ContainerNode {

    ContainerNode* next;
    ContainerNode* prev;
    Character* gameCharacter;

  };

  public:
    Container();
    ~Container();
    bool isEmpty();
    void addBack(Character* backCharacter);
    void addFront(Character* frontCharacter);
    Character* getFront();
    void removeFront();
    void printContainer();

  private:
    ContainerNode* head;

};

#endif
