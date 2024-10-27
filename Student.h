//variables should be camelCase for example id or idNUmber
//functions are PascalCase so thats good 
//I understand we havent had the LinkedList set up as yet however i strongly recommend you still include the course list into this code via comments. An example is in line 14
//iostream and using namespace std are included in the so their wont be any errors here.
#ifndef Student_H
#define Student_H

#include "LinkedList.h"
#include "Course.h"
#include <iostream>
using namespace std;

class Student {
//Class Attributes
private:
  int id;
  string name;
  float gpa;
  bool isPriority;
  LinkedList<Course> enrolledCourses;

public:
  // Default Constructor
  Student() {
    id = 0;
    name = "";
    gpa = 0;
    isPriority = false;
  }
  // Primary Constructor
    Student(int Id, string Name, float Gpa, bool IsPriority){
      id = Id;
      name = Name;
      gpa = Gpa;
      isPriority = IsPriority;
    }
  // Copy Constructor
    Student(const Student &s){
      id = s.id;
      name = s.name;
      gpa = s.gpa;
      isPriority = s.isPriority;
    }
  // Accessors
    int GetId(){
      return id;
    }
    string GetName(){
      return name;
    }
    float GetGPA(){
      return gpa;
    }

    //Using Student class to set the isPriority variable using GPA
    bool GetIsPriority(){
      if (gpa >= 3.5){
        isPriority = true;
      }
      else{
        isPriority = false;
      }
      return isPriority;
    }

    LinkedList<Course> GetEnrolledCourses(){
      return enrolledCourses;
    }

  // Mutators
    void SetId(int Id){
      id = Id;
    }
    void SetName(string Name){
      name = Name;
    }

    void SetGPA(float Gpa){
      gpa = Gpa;
    } 


    
    void SetEnrolledCourses(LinkedList<Course> EnrolledCourses){
      enrolledCourses = EnrolledCourses;
    }

    void Display(){
      cout << "Id: " << id << ", Name: " << name << ", GPA: " << gpa;
    }
};

#endif
