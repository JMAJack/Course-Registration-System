//Joel Henry
//2300087
//10/20/2024

#ifndef Node_H
#define Node_H

#include "Student.h"
#include <iostream>
using namespace std;

//The Node acts as the container for both the data and the location of the next node. Crucial for Linked List
class Node{
	private:
		Student data;
		Node* next;

	public:
    //Default Constructor
		Node(){
			next = NULL;
		}

    //Primary Constructor
		Node(Student data){
			this->data = data;
		}

    //Primary Constructor
		Node(Student data, Node* next){
			this->data = data;
			this->next = next;
		}

    //Copy Constructor
		Node(const Node &n){
			data = n.data;
			next = n.next;
		}

		Student getData(){
			return data;
		}

		Node* getNext(){
			return next;
		}

		void setData(Student data){
			this->data = data;
		}

		void setNext(Node* next){
			this->next = next;
		}

    //this may need to be edited later
		void display(){
			data.show();
		}
};

#endif
