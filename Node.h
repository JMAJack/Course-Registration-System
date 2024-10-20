//Joel Henry
//2300087
//10/20/2024

#ifndef Node_H
#define Node_H

#include "Student.h"
#include <iostream>
using namespace std;

//The Node acts as the container for both the data and the location of the next node. Crucial for Linked List
// Cause courses also need a linked list just derive and override functions to
// take in Course as a parameter. We may also need to rename this class and node
// as well
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

		Student GetData(){
			return data;
		}

		Node* GetNext(){
			return next;
		}

		void SetData(Student data){
			this->data = data;
		}

		void SetNext(Node* next){
			this->next = next;
		}

    //this may need to be edited later
		void Display(){
			//data.show();
		}
};

#endif
