#include "Student.h"
#include "LinkedList.h"

#include <iostream>
#include <queue>

using namespace std;


class Course {
private:
    string courseCode;
    string title;
    int credits;
    int maxCapacity;
    LinkedList<Student> enrolledStudents;     
    queue<Student> waitlist;           
    queue<Student> priorityQueue;       

public:
    // Default constructor
    Course() : courseCode(""), title(""), credits(0), maxCapacity(0) {}

    // Primary constructor
    Course(string courseCode, string title, int credits, int maxCapacity) 
        : courseCode(courseCode), title(title), credits(credits), maxCapacity(maxCapacity) {}

    // Copy constructor
    Course(const Course& other)
        : courseCode(other.courseCode), title(other.title), credits(other.credits), maxCapacity(other.maxCapacity),
          enrolledStudents(other.enrolledStudents), waitlist(other.waitlist), priorityQueue(other.priorityQueue) {}

    // Accessors and mutators
    string GetCourseCode() { return courseCode; }

    void SetCourseCode(string code) { courseCode = code; }

    string GetTitle()  { return title; }
    void SetTitle(string newTitle) { title = newTitle; }

    int GetCredits() { return credits; }
    void SetCredits(int newCredits) { credits = newCredits; }

    int GetMaxCapacity() { return maxCapacity; }
    void SetMaxCapacity(int capacity) { maxCapacity = capacity; }

    LinkedList<Student> GetEnrolledStudents() { return enrolledStudents; }
    void SetEnrolledStudents(LinkedList<Student> students) { enrolledStudents = students; }

    queue<Student> GetWaitlist() { return waitlist; }
    void SetWaitlist(queue<Student> newWaitlist) { waitlist = newWaitlist; }

    queue<Student> GetPriorityQueue() { return priorityQueue; }
    void SetPriorityQueue(queue<Student> newPriorityQueue) { priorityQueue = newPriorityQueue; }

    void Display() {
        cout << "Course Code: " << courseCode << endl;
        cout << "Title: " << title << endl;
        cout << "Credits: " << credits << endl;
        cout << "Max Capacity: " << maxCapacity << endl;
    }

    //ADDITIONAL FUNCTIONS
    void AddStudent(Student student) {
        if (enrolledStudents.Size() < maxCapacity) {
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
};