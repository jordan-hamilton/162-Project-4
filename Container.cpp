#include "Container.hpp"

using std::cout;
using std::endl;

/***********************************************************************************************
** Description: Constructor that initializes the head data member to nullptr.
***********************************************************************************************/
Container::Container() {
  head = nullptr;
}


/***********************************************************************************************
** Description: Destructor that removes items from the container until the isEmpty method
** determines that the circular linked list is empty.
***********************************************************************************************/
Container::~Container() {

  while (!isEmpty()) {
    removeFront();
  }

}


/***********************************************************************************************
** Description: Returns a boolean to indicate that the circular linked list has no nodes if the
** head data member is not a valid pointer.
***********************************************************************************************/
bool Container::isEmpty() {

  if (head) {
    return false;
  } else {
    return true;
  }

}


/*****************************************************************************************************
** Description: This method takes a integer, allocates memory and adds a pointer to a
** ContainerNode object to the back of the container, setting its val data member to equal the integer
** passed to the method. If the container was previously empty, the pointer to the object is
** assigned to the Container's head data member and the ContainerNode's prev and next pointers also
** to indicate that this is the only node in a circular linked list. Otherwise, the head is
** assigned to the object's next data member, and the head's prev data member is then assigned
** to the object's prev to place this value before the head and after the ContainerNode that was the
** most recently at the back of the container. Finally, the next data member of the ContainerNode that
** was previously at the back of the container is set to the pointer to the new ContainerNode object,
** as is the head's prev data member.
*****************************************************************************************************/
void Container::addBack(int val) {

  if ( isEmpty() ) {

    head = new ContainerNode;
    head->prev = head;
    head->next = head;
    head->val = val;

  } else {

    ContainerNode* newBack = new ContainerNode {head, head->prev, val};

    head->prev->next = newBack;
    head->prev = newBack;

  }


}



/******************************************************************************************************
** Description: This method takes a integer, allocates memory and adds a pointer to a
** ContainerNode object to the front of the container, setting its val data member to equal the integer
** passed to the method. If the container was previously empty, the pointer to the object is
** assigned to the Container's head data member and the ContainerNode's prev and next pointers also
** to indicate that this is the only node in a circular linked list. Otherwise, the head is
** assigned to the object's next data member, and the head's prev data member is then assigned
** to the object's prev to place this value before the head and after the ContainerNode at the back of
** the container. Finally, the next data member of the ContainerNode at the back of the container is
** set to the pointer to the new ContainerNode object, as is the head's prev data member. The new
** object is then set as the head of the container.
******************************************************************************************************/
void Container::addFront(int val) {

  if ( isEmpty() ) {

    head = new ContainerNode;
    head->prev = head;
    head->next = head;
    head->val = val;

  } else {

    ContainerNode* newFront = new ContainerNode {head, head->prev, val};

    head->prev->next = newFront;
    head->prev = newFront;
    head = newFront;

  }


}


/***********************************************************************************************
** Description: Returns the integer assigned to the val data member of the ContainerNode object.
** Note that to prevent getFront from trying to dereference to pointer when head is nullptr,
** the switch statement in main.cpp calls the isEmpty method first to ensure that getFront
** can be called safely.
***********************************************************************************************/
int Container::getFront() {
    return head->val;
}


/***********************************************************************************************
** Description: This method checks that head is a valid pointer, then assigns the object
** after head to a temporary pointer, nextHead. nextHead's prev pointer is set to the head's prev
** pointer, the last node in the container, and this node's next pointer is set to the nextHead.
** Finally, memory allocated for the current head is freed and head is assigned the pointer to
** nextHead. If head's next pointer is equal to head, indicating that head was the only node in
** the container, then memory is simply freed and head is assigned nullptr.
***********************************************************************************************/
void Container::removeFront() {

  if (head) {

    if (head->next != head) {

      ContainerNode* nextHead = head->next;
      nextHead->prev = head->prev;
      head->prev->next = nextHead;
      delete head;
      head = nextHead;

    } else {

      delete head;
      head = nullptr;

    }

  }

}


/**************************************************************************************************
** Description: This method checks that the container is not empty using the isEmpty method, then
** initializes a temporary pointer, currentNode, to the head pointer, and loops through the
** circular linked list with a do-while loop to output each ContainerNode's val. currentNode is set
** to the node's next pointer at the end of each loop, stopping the loop once currentNode is
** once again equal to the head pointer. If the container is empty, an error message is displayed
** instead.
**************************************************************************************************/
void Container::printContainer() {

  if ( !isEmpty() ) {

    ContainerNode* currentNode = head;

    do {

      cout << currentNode->val << endl;
      currentNode = currentNode->next;

    } while (currentNode != head);

  } else {
    cout << "No values exist in this container." << endl;
  }


}
