#ifndef STUDENT_H
#define STUDENT_H

#include "Course.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>

using namespace std;

class Course; // Forward declaration

class Student {
private:
    int id;
    string name;
    float gpa;
    bool isPriority;
    LinkedList<Course> enrolledCourses;

public:
    // Default Constructor
    Student() : id(0), name(""), gpa(0.0), isPriority(false) {}

    // Primary Constructor
    Student(int Id, string Name, float Gpa, LinkedList<Course> EnrolledCourses)
        : id(Id), name(Name), gpa(Gpa), enrolledCourses(EnrolledCourses) {
            isPriority = (gpa >= 3.5);
        }

    // Copy Constructor
    Student(const Student& s)
        : id(s.id), name(s.name), gpa(s.gpa), isPriority(s.isPriority), enrolledCourses(s.enrolledCourses) {}

    // Accessors
    int GetId() const { return id; }
    string GetName() const { return name; }
    float GetGPA() const { return gpa; }
    bool GetIsPriority() const { return isPriority; }
    LinkedList<Course> GetEnrolledCourses() const { return enrolledCourses; }

    // Mutators
    void SetId(int Id) { id = Id; }
    void SetName(string Name) { name = Name; }
    void SetGPA(float Gpa) { gpa = Gpa; }
    void SetIsPriority(bool IsPriority) { isPriority = IsPriority; }
    void SetEnrolledCourses(LinkedList<Course> EnrolledCourses) { enrolledCourses = EnrolledCourses; }

    // Display student details
    void Display() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "GPA: " << gpa << endl;
        cout << "Priority: " << (isPriority ? "Yes" : "No") << endl;
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
            currentCourse->GetData().Serialize(outFile); // Assuming Course has Serialize
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
            course.Deserialize(inFile); // Assuming Course has Deserialize
            enrolledCourses.Insert(course);
        }
    }

    bool operator==(const Student& other) const {
        return id == other.id;
    }
};

#endif // STUDENT_H