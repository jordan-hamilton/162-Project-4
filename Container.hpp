/*********************************************************************
** Description: Specification file for the Container class.
*********************************************************************/

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <memory>

#include "Character.hpp"

class Container {

  struct ContainerNode {

    ContainerNode* next;
    ContainerNode* prev;
    std::shared_ptr<Character> gameCharacter;

  };

  public:
    Container();
    ~Container();
    bool isEmpty();
    void addBack(std::shared_ptr<Character> backCharacter);
    void addFront(std::shared_ptr<Character> frontCharacter);
    std::shared_ptr<Character> getFront();
    void removeFront();
    void printContainer();

  private:
    ContainerNode* head;

};

#endif
