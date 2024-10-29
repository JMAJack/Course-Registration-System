//variables should be camelCase for example id or idNUmber
//functions are PascalCase so thats good 
//I understand we havent had the LinkedList set up as yet however i strongly recommend you still include the course list into this code via comments. An example is in line 14
//iostream and using namespace std are included in the so their wont be any errors here.
#ifndef Student_H
#define Student_H

#include "LinkedList.h"
#include "Course.h"
#include <iostream>
#include <fstream>

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

     // Serialize the student data to a binary file
    void Serialize(ofstream& outFile) const {
        outFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
        size_t nameLength = name.size();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        outFile.write(name.c_str(), nameLength);
        outFile.write(reinterpret_cast<const char*>(&gpa), sizeof(gpa));
        outFile.write(reinterpret_cast<const char*>(&isPriority), sizeof(isPriority));

        // Serialize enrolledCourses LinkedList
        int courseCount = enrolledCourses.Size();
        outFile.write(reinterpret_cast<const char*>(&courseCount), sizeof(courseCount));
        Node<Course>* currentCourse = enrolledCourses.GetHead();
        while (currentCourse != nullptr) {
            currentCourse->GetData().Serialize(outFile);
            currentCourse = currentCourse->GetNext();
        }
    }

    // Deserialize the student data from a binary file
    void Deserialize(ifstream& inFile) {
        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        
        size_t nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        name.resize(nameLength);
        inFile.read(&name[0], nameLength);
        
        inFile.read(reinterpret_cast<char*>(&gpa), sizeof(gpa));
        inFile.read(reinterpret_cast<char*>(&isPriority), sizeof(isPriority));

        // Deserialize enrolledCourses LinkedList
        int courseCount;
        inFile.read(reinterpret_cast<char*>(&courseCount), sizeof(courseCount));
        enrolledCourses = LinkedList<Course>();
        for (int i = 0; i < courseCount; ++i) {
            Course course;
            course.Deserialize(inFile);
            enrolledCourses.Insert(course);
        }
    }
};

#endif
