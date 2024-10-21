#include "Student.h"
#include "LinkedList.h"

#include <iostream>
#include <queue>

using namespace std;

class Course {
private:
    int code;
    string title;
    int credits;
    int maxCapacity;
    int maxPriority;
    // LinkedList<Student> enrolledStudents; // Linked list of students
    queue<Student> waitlist;  // Waitlist queue for students when course is full
    queue<Student> priorityQueue; // Priority queue students

    //STUDENT DOES NOT HAVE TO BE A POINTER FOR THIS CASE
    

public:
    // Default constructor
    Course() : code(""), title(""), credits(0), maxCapacity(0) {}

    // Parameterized constructor
    Course(string code, int title, int credits, int maxCapacity)
        : code(code), title(title), credits(credits), maxCapacity(maxCapacity) {}

    // Copy constructor
    Course(const Course& other)
        : code(other.code), title(other.title), credits(other.credits), maxCapacity(other.maxCapacity),
          enrolledStudents(other.enrolledStudents), waitlist(other.waitlist), priorityQueue(other.priorityQueue) {}

    // Getters and Setters
    int GetCode(){
        return code;
    }

    //This is for the LinkedList
    int GetId() {
        return code;
    }

    void SetCode(string code) {
        code = code;
    }

    string GetTitle() {
        return title;
    }

    void SetTitle(string newTitle) {
        title = newTitle;
    }

    int GetCredits() {
        return credits;
    }

    void SetCredits(int newCredits) {
        credits = newCredits;
    }

    int GetMaxCapacity(){
        return maxCapacity;
    }

    void SetMaxCapacity(int capacity) {
        maxCapacity = capacity;
    }

    // student class isn't available yet 
    /*LinkedList<Student*>& GetEnrolledStudents() {
        return enrolledStudents;
    }*/

    queue<Student>& GetWaitlist() {
        return waitlist;
    }

    queue<Student>& GetPriorityQueue() {
        return priorityQueue;
    }

    //ENROLLED STUDENTS IS A LINKEDLIST NOT A QUEUE THUS THIS SECTION NEEDS TO BE REVISTED
    // Adds a student to the course or add students to the waitlist/priority queue if the course is full
    void AddStudent(Student student, bool isPriority) {

        // DUE TO PRIORITY BEING BASED ON GPA, WHAT I WILL DO IS JUST MAKE THE STUDENT CLASS
        // HAVE A FUNCTION THAT CHECKS IF ITS PRIORITIZED OR NOT.
        // MAKING IT student.isPriority() WILL RETURN TRUE IF GPA IS ABOVE 3.0

        if (enrolledStudents.size() < maxCapacity) {
            enrolledStudents.push_back(student);

            // ONCE LINKED LIST IS AVAILABLE ADD COURSE TO STUDENT ENROLLED COURSES

            cout << "Student " << student.GetName() << " added to " << title << endl;
        } else {
            if (isPriority && priorityQueue.size() < maxPriority) {
                priorityQueue.push(student);
                cout << "Student " << student.GetName() << " added to priority queue for " << title << endl;
            } else {
                waitlist.push(student);
                cout << "Student " << student.GetName() << " added to waitlist for " << title << endl;
            }
        }
    }

    // Remove a student from the course
    //ENROLLED STUDENTS IS A LINKEDLIST NOT A QUEUE THUS THIS SECTION NEEDS TO BE REVISTED
    void RemoveStudent(Student student) {
        auto it = find(enrolledStudents.begin(), enrolledStudents.end(), student);
        if (it != enrolledStudents.end()) {
            enrolledStudents.erase(it);
            // Update the students enrolled courses
            student->GetEnrolledCourses().remove(code);
            cout << "Student " << student->GetName() << " removed from " << title << endl;

            // Enroll next student in priority queue or waitlist if there is space
            if (!priorityQueue.empty()) {
                Student* nextPriorityStudent = priorityQueue.front();
                priorityQueue.pop();
                AddStudent(nextPriorityStudent, true); // Move student from priority queue to course
            } else if (!waitlist.empty()) {
                Student* nextWaitlistStudent = waitlist.front();
                waitlist.pop();
                AddStudent(nextWaitlistStudent, false); // Move student from waitlist to course
            }
        } else {
            cout << "Student not found in this course." << endl;
        }
    }

    // Modify courses 
    void ModifyCourse(string newTitle, int newCredits, int newMaxCapacity) {
        SetTitle(newTitle);
        SetCredits(newCredits);
        SetMaxCapacity(newMaxCapacity);
        cout << "Course details updated to: " << title << " (" << credits << " credits, max capacity: " << maxCapacity << ")" << endl;
    }

    // Display enrolled students
    void DisplayEnrolledStudents(){
        cout << "Students enrolled in " << title << ":" << endl;
        for (Student student : enrolledStudents) {
            cout << student->GetName() << endl;
        }
    }

    // Display waitlist students
    void DisplayWaitlist(){
        cout << "Waitlist for " << title << ":" << endl;
        // Copy the queue to repeat
        queue<Student tempWaitlist = waitlist;
        while (tempWaitlist.empty()) {
            Student student = tempWaitlist.front();
            tempWaitlist.pop();
            cout << student->GetName() << endl;
        }
    }

    // Display priority queue students
    void DisplayPriorityQueue(){
        cout << "Priority queue for " << title << ":" << endl;
        // Copy the queue to repeat
        queue<Student> tempPriorityQueue = priorityQueue;
        while (!tempPriorityQueue.empty()) {
            Student student = tempPriorityQueue.front();
            tempPriorityQueue.pop();
            cout << student->GetName() << endl;
        }
    }
};