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
protected:
  Node *head;

public:
  // Default constructor
  LinkedList() { head = NULL; }



  int CountNodes() {
    int count = 0;
    Node *curr = head;
    while (curr != NULL) {
      count++;
      curr = curr->GetNext();
    }
    return count;
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
};

class StudentLinkedList : public LinkedList {
public:
    StudentLinkedList() : LinkedList() {}


    // Override the functions to use Course instead of Student

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

    void InsertAtBack(Student data){
        Node *temp = new Node(data);
        if (temp != NULL) {
            if (IsFull()) {
                cerr << "List is full, Data cannot be added" << endl;
            } else {
                if (IsEmpty()) {
                    head = temp;
                } else {
                    Node *curr = head;
                    while (curr->GetNext() != NULL) {
                        curr = curr->GetNext();
                    }
                    curr->SetNext(temp);
                }
            }
        }
    }

    Student SearchForANode(int code){
        Node *curr = head;
        while (curr != NULL) {
            if (curr->GetData().GetId() == code) {  // GetCode() for Course
                return curr->GetData();
            }
            curr = curr->GetNext();
        }
        return Student();  // Return empty Course if not found
    }

    Student DeleteANode(int code) {
        Student dataToReturn;
        if (!IsEmpty()) {
            Node *curr = head, *prev = NULL;

            while (curr != NULL) {
                if (curr->GetData().GetId() == code) {
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


class CourseLinkedList : public LinkedList {
public:
    CourseLinkedList() : LinkedList() {}

    // Override the functions to use Course instead of Student

    void InsertAtFront(Course data){
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

    void InsertAtBack(Course data){
        Node *temp = new Node(data);
        if (temp != NULL) {
            if (IsFull()) {
                cerr << "List is full, Data cannot be added" << endl;
            } else {
                if (IsEmpty()) {
                    head = temp;
                } else {
                    Node *curr = head;
                    while (curr->GetNext() != NULL) {
                        curr = curr->GetNext();
                    }
                    curr->SetNext(temp);
                }
            }
        }
    }

    Course SearchForANode(int code){
        Node *curr = head;
        while (curr != NULL) {
            if (curr->GetData().GetCode() == code) {  // GetCode() for Course
                return curr->GetData();
            }
            curr = curr->GetNext();
        }
        return Course();  // Return empty Course if not found
    }

    Course DeleteANode(int code){
        Course dataToReturn;
        if (!IsEmpty()) {
            Node *curr = head, *prev = NULL;

            while (curr != NULL) {
                if (curr->GetData().GetCode() == code) {
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

