#include "Student.h"
#include "LinkedList.h"

#include <iostream>
#include <queue>
#include <fstream>

using namespace std;


class Course {
private:
    string code;
    string title;
    int credits;
    int maxCapacity;
    Course *prerequisites[2];
    LinkedList<Student> enrolledStudents;     
    queue<Student> waitlist;           
    queue<Student> priorityQueue;       

public:
    // Default constructor
    Course() {
        code = "";
        title = "";
        credits = 0;
        maxCapacity = 0;
        prerequisites[0] = nullptr;
        prerequisites[1] = nullptr;
    }

    // Primary constructor
    Course(string Code, string Title, int Credits, int MaxCapacity, Course *Prerequisites[2]) {
        code = Code;
        title = Title;
        credits = Credits;
        maxCapacity = MaxCapacity;
        prerequisites[0] = Prerequisites[0];
        prerequisites[1] = Prerequisites[1];
    }

    // Copy constructor
    Course(const Course &c) {
        code = c.code;
        title = c.title;
        credits = c.credits;
        maxCapacity = c.maxCapacity;
        prerequisites[0] = c.prerequisites[0];
        prerequisites[1] = c.prerequisites[1];
        enrolledStudents = c.enrolledStudents;
        waitlist = c.waitlist;
        priorityQueue = c.priorityQueue;
    }

    // Accessors and mutators
    string GetCode() { return code; }

    void SetCode(string Code) { code = code; }

    string GetTitle()  { return title; }
    void SetTitle(string newTitle) { title = newTitle; }

    int GetCredits() { return credits; }
    void SetCredits(int newCredits) { credits = newCredits; }

    int GetMaxCapacity() { return maxCapacity; }
    void SetMaxCapacity(int capacity) { maxCapacity = capacity; }

    Course* GetPrerequisites(int index) { return prerequisites[index]; }
    void SetPrerequisites(int index, Course *prereq) { prerequisites[index] = prereq; }

    LinkedList<Student> GetEnrolledStudents() { return enrolledStudents; }
    void SetEnrolledStudents(LinkedList<Student> students) { enrolledStudents = students; }

    queue<Student> GetWaitlist() { return waitlist; }
    void SetWaitlist(queue<Student> newWaitlist) { waitlist = newWaitlist; }

    queue<Student> GetPriorityQueue() { return priorityQueue; }
    void SetPriorityQueue(queue<Student> newPriorityQueue) { priorityQueue = newPriorityQueue; }

    void Display() {
        cout << "Course Code: " << code << endl;
        cout << "Title: " << title << endl;
        cout << "Credits: " << credits << endl;
        cout << "Max Capacity: " << maxCapacity << endl;
        cout << "Prerequisites: ";
        for (int i = 0; i < 2; i++) {
            if (prerequisites[i] != nullptr) {
                cout << prerequisites[i]->GetCode() << " ";
            }
        }
        cout << endl;
    }

    //ADDITIONAL FUNCTIONS
    void AddStudent(Student student) {
        if (enrolledStudents.Size() < maxCapacity) {
            //check if student meets prerequisites
            for (int i = 0; i < 2; i++) {
                if (prerequisites[i] != nullptr) {
                    if (student.GetEnrolledCourses().Search(*prerequisites[i]) == nullptr) {
                        cout << "Student " << student.GetName() << " does not meet prerequisites for " << title << endl;
                        return;
                    }
                }
            }
            enrolledStudents.Insert(student);
            cout << "Student " << student.GetName() << " added to " << title << endl;
        } else {
            if (student.GetIsPriority()) {
                priorityQueue.push(student);
                cout << "Student " << student.GetName() << " added to priority queue for " << title << endl;
            } else {
                waitlist.push(student);
                cout << "Student " << student.GetName() << " added to waitlist for " << title << endl;
            }

        }   
    }

    void RemoveStudent(Student student) {
        enrolledStudents.Remove(student);
        cout << "Student " << student.GetName() << " removed from " << title << endl;

        if (!priorityQueue.empty()) {
            Student nextPriorityStudent = priorityQueue.front();
            priorityQueue.pop();
            AddStudent(nextPriorityStudent);  
        } else if (!waitlist.empty()) {
            Student nextWaitlistStudent = waitlist.front();
            waitlist.pop();
            AddStudent(nextWaitlistStudent); 
        }
    }

    void DisplayEnrolledStudents() {
        cout << "Students enrolled in " << title << ":" << endl;
        enrolledStudents.DisplayList();
    }

    void DisplayWaitlist() const {
        cout << "Waitlist for " << title << ":" << endl;
        queue<Student> tempWaitlist = waitlist;
        while (!tempWaitlist.empty()) {
            cout << tempWaitlist.front().GetName() << endl;
            tempWaitlist.pop();
        }
    }

    void DisplayPriorityQueue() const {
        cout << "Priority queue for " << title << ":" << endl;
        queue<Student> tempPriorityQueue = priorityQueue;
        while (!tempPriorityQueue.empty()) {
            cout << tempPriorityQueue.front().GetName() << endl;
            tempPriorityQueue.pop();
        }
    }

     // Serialize the course data to a binary file
    void Serialize(ofstream& outFile) const {
        size_t courseCodeLength = courseCode.size();
        outFile.write(reinterpret_cast<const char*>(&courseCodeLength), sizeof(courseCodeLength));
        outFile.write(courseCode.c_str(), courseCodeLength);

        size_t titleLength = title.size();
        outFile.write(reinterpret_cast<const char*>(&titleLength), sizeof(titleLength));
        outFile.write(title.c_str(), titleLength);

        outFile.write(reinterpret_cast<const char*>(&credits), sizeof(credits));
        outFile.write(reinterpret_cast<const char*>(&maxCapacity), sizeof(maxCapacity));

        // Serialize enrolledStudents LinkedList
        int studentCount = enrolledStudents.Size();
        outFile.write(reinterpret_cast<const char*>(&studentCount), sizeof(studentCount));
        Node<Student>* currentStudent = enrolledStudents.GetHead();
        while (currentStudent != nullptr) {
            currentStudent->GetData().Serialize(outFile); // Assuming Student has Serialize
            currentStudent = currentStudent->GetNext();
        }
    }

    // Deserialize the course data from a binary file
    void Deserialize(ifstream& inFile) {
        size_t courseCodeLength;
        inFile.read(reinterpret_cast<char*>(&courseCodeLength), sizeof(courseCodeLength));
        courseCode.resize(courseCodeLength);
        inFile.read(&courseCode[0], courseCodeLength);

        size_t titleLength;
        inFile.read(reinterpret_cast<char*>(&titleLength), sizeof(titleLength));
        title.resize(titleLength);
        inFile.read(&title[0], titleLength);

        inFile.read(reinterpret_cast<char*>(&credits), sizeof(credits));
        inFile.read(reinterpret_cast<char*>(&maxCapacity), sizeof(maxCapacity));

        // Deserialize enrolledStudents LinkedList
        int studentCount;
        inFile.read(reinterpret_cast<char*>(&studentCount), sizeof(studentCount));
        enrolledStudents = LinkedList<Student>();
        for (int i = 0; i < studentCount; ++i) {
            Student student;
            student.Deserialize(inFile); // Assuming Student has Deserialize
            enrolledStudents.Insert(student);
        }
    }

};