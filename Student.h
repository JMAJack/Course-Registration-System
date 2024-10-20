//variables should be camelCase for example id or idNUmber
//functions are PascalCase so thats good 
//I understand we havent had the LinkedList set up as yet however i strongly recommend you still include the course list into this code via comments. An example is in line 14
//iostream and using namespace std are included in the so their wont be any errors here.

#include <iostream>
using namespace std;

class Student {

private:
  int id;
  string name;
  float GPA;
  Linkedlist enrolledCourses;
//LinkedList enrolledCourses; [will be inlcuded later]

public:
  // Default Constructor
  Student() {
    id = 0;
    name = "";
    GPA = 0;
  }
  // Primary Constructor
    Student(int Id, string Name, float gpa){
      id = Id;
      name = Name;
      GPA = gpa;
    }
  // Copy Constructor
    Student(const Student &s){
      id = s.id;
      name = s.name;
      GPA = s.GPA;
    }
  // Accessors
    int GetId(){
      return id;
    }
    string GetName(){
      return name;
    }
    float GetGPA(){
      return GPA;
    }
    Linkedlist GetEnrolledCourses(){
      return enrolledCourses;
    }
  // Mutators
    void SetId(int Id){
      id = Id;
    }
    void SetName(string Name){
      name = Name;
    }
    void SetGPA(float gpa){
      GPA = gpa;
    }
    void Display(){
      cout << "Id: " << id << ", Name: " << name << ", GPA: " << GPA;
    }
};