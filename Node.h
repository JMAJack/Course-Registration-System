//Joel Henry
//2300087
//10/20/2024

#ifndef Node_H
#define Node_H

#include "Student.h"
#include "Course.h"

#include <iostream>
using namespace std;

//MOCK UP FOR DERIVED CLASS APPROACH TO BE USED WITH LINKED LIST

//Parent Class
class Node{
	protected:
		Node* next;

	public:
    //Default Constructor
		Node(){
			next = NULL;
		}

    //Copy Constructor
		Node(const Node &n){
			next = n.next;
		}

		Node* GetNext(){
			return next;
		}

		void SetNext(Node* next){
			this->next = next;
		}
};

//Derived Class
class StudentNode : public Node{
	private:
		Student data;

	public:
	//Default Constructor
		StudentNode(){
			next = NULL;
		}

	//Copy Constructor
		StudentNode(const StudentNode &n){
			data = n.data;
			next = n.next;
		}

		Student GetData(){
			return data;
		}

		void SetData(Student data){
			this->data = data;
		}

	//this may need to be edited later
		void Display(){
			data.Display();
		}
};


//Derived Class
class CourseNode : public Node{
	private:
		Course data;

	public:
	//Default Constructor
		CourseNode(){
			next = NULL;
		}

	//Copy Constructor
		CourseNode(const CourseNode &n){
			data = n.data;
			next = n.next;
		}

		Course GetData(){
			return data;
		}

		void SetData(Course data){
			this->data = data;
		}

	//this may need to be edited later
		void Display(){
			data.Display();
		}
};

#endif
