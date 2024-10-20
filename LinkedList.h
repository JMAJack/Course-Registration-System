// Joel Henry
// 2300087
// 10/20/2024

// LinkedList Class
#ifndef LinkedList_H
#define LinkedList_H

#include "Node.h"

// Cause courses also need a linked list just derive and override functions to
// take in Course as a parameter. We may also need to rename this class and node
// as well
class LinkedList {
private:
  Node *head;

public:
  // Default constructor
  LinkedList() { head = NULL; }

  // Primary constructor
  LinkedList(Node *h) { head = h; }

  // Accessors
  Node *Gethead() { return head; }

  // Mutators
  void Sethead(Node *head) { head = head; }

  void InsertAtFront(Student data) {
    Node *temp = new Node(data);
    if (temp != NULL) {
      if (IsFull()) {
        cerr << "List is full, Data cannot be added" << endl;
      } else {
        if (IsEmpty()) {
          head = temp;
        } else {
          temp->SetNext(head);
          head = temp;
        }
      }
    }
  }

  void InsertAtBack(Student data) {
    Node *temp = new Node(data);
    if (temp != NULL) {
      if (IsFull()) {
        cerr << "List is full, Data cannot be added" << endl;
      } else {
        if (IsEmpty()) {
          head = temp;
        } else {
          Node *curr = head;
          while (curr->getNext() != NULL) {
            curr = curr->getNext();
          }
          curr->SetNext(temp);
        }
      }
    }
  }

  int CountNodes() {
    int count = 0;
    Node *curr = head;
    while (curr != NULL) {
      count++;
      curr = curr->GetNext();
    }
    return count;
  }

  // There could be more search methods thus this part will be updated
  Student SearchForANode(int id) {
    Node *curr = head;
    while (curr != NULL) {
      if (curr->getData().getLicenseNo() == id) {
        return curr->getData();
      }
      curr = curr->getNext();
    }
    return Student();
  }

  bool IsEmpty() { return head == NULL; }

  bool IsFull() {
    Node *temp = new Node;
    if (temp != NULL) {
      delete temp;
      return false;
    }
    return true;
  }

  // May need to be updated
  void DisplayList() {
    Node *curr = head;
    if (!IsEmpty()) {
      while (curr != NULL) {
        cout << "[";
        curr->GetData().Display();
        cout << "]->";
        curr = curr->GetNext();
      }
      cout << "NULL";
    } else {
      cout << "List is empty" << endl;
    }
  }

  Student DeleteANode(int id) {
    Student dataToReturn;

    if (!IsEmpty()) {
      Node *curr = head, *prev = NULL;

      while (curr != NULL) {
        if (curr->GetData().GetId() == id) {
          if (curr == head) {
            head = head->GetNext();
          } else {
            prev->SetNext(curr->GetNext());
          }
          dataToReturn = curr->GetData();
          delete curr;
          break;
        }
        prev = curr;
        curr = curr->GetNext();
      }
    } else {
      cerr << "The list is empty; there is nothing to delete!" << endl;
    }
    return dataToReturn;
  }
};

#endif
