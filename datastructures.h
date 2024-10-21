#include <iostream>
#include <list>
#include <queue>
#include <string>
 
using namespace std;
 
class Student {
public:
    string name;
    list<string> enrolledCourses;
 
    Student(string name) : name(name) {}
 
    string GetName() const {
        return name;
    }
 
    list<string>& GetEnrolledCourses() {
        return enrolledCourses;
    }
};
 
class Course {
private:
    string courseCode;
    string title;
    int credits;
    int maxCapacity;
    //student class isnt available yet
    list<Student*> enrolledStudents; // Linked list of students
    queue<Student*> waitlist;  // Waitlist queue for students when course is full
    queue<Student*> priorityQueue;  // Priority queue students
 
public:
    // Default constructor
    Course() : courseCode(""), title(""), credits(0), maxCapacity(0) {}
 
    // Parameterized constructor
    Course(string courseCode, string title, int credits, int maxCapacity) 
        : courseCode(courseCode), title(title), credits(credits), maxCapacity(maxCapacity) {}
 
    // Copy constructor
    Course(const Course& other)
        : courseCode(other.courseCode), title(other.title), credits(other.credits), maxCapacity(other.maxCapacity),
          enrolledStudents(other.enrolledStudents), waitlist(other.waitlist), priorityQueue(other.priorityQueue) {}
 
    // Getters and Setters
    string GetCourseCode() const {
        return courseCode;
    }
 
    void SetCourseCode(const string& code) {
        courseCode = code;
    }
 
    
    string GetTitle() const {
        return title;
    }
 
    void SetTitle(const string& newTitle) {
        title = newTitle;
    }
 
    
    int GetCredits() const {
        return credits;
    }
 
    void SetCredits(int newCredits) {
        credits = newCredits;
    }
 
    
    int GetMaxCapacity() const {
        return maxCapacity;
    }
 
    void SetMaxCapacity(int capacity) {
        maxCapacity = capacity;
    }
 
    //student class isnt available yet 
    list<Student*>& GetEnrolledStudents() {
        return enrolledStudents;
    }
 
    
    queue<Student*>& GetWaitlist() {
        return waitlist;
    }
 
   
    queue<Student*>& GetPriorityQueue() {
        return priorityQueue;
    }
 
    // ddds a student to the course or add students to the waitlist/priority queue if the course is full
    void AddStudent(Student* student, bool isPriority) {
        if (enrolledStudents.size() < maxCapacity) {
            enrolledStudents.push_back(student);
            student->GetEnrolledCourses().push_back(courseCode); // Updates student enrolled courses
            cout << "Student " << student->GetName() << " added to " << title << endl;
        } else {
            if (isPriority) {
                priorityQueue.push(student);
                cout << "Student " << student->GetName() << " added to priority queue for " << title << endl;
            } else {
                waitlist.push(student);
                cout << "Student " << student->GetName() << " added to waitlist for " << title << endl;
            }
        }
    }
 
    // Remove a student from the course
    void RemoveStudent(Student* student) {
        auto it = find(enrolledStudents.begin(), enrolledStudents.end(), student);
        if (it != enrolledStudents.end()) {
            enrolledStudents.erase(it);
            // Update the students enrolled courses
            student->GetEnrolledCourses().remove(courseCode); 
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
    void ModifyCourse(const string& newTitle, int newCredits, int newMaxCapacity) {
        SetTitle(newTitle);
        SetCredits(newCredits);
        SetMaxCapacity(newMaxCapacity);
        cout << "Course details updated to: " << title << " (" << credits << " credits, max capacity: " << maxCapacity << ")" << endl;
    }
 
    // Display enrolled students
    void DisplayEnrolledStudents() const {
        cout << "Students enrolled in " << title << ":" << endl;
        for (const auto& student : enrolledStudents) {
            cout << student->GetName() << endl;
        }
    }
 
    // Display waitlist students
    void DisplayWaitlist() const {
        cout << "Waitlist for " << title << ":" << endl;
        // Copy the queue to repeat
        queue<Student*> tempWaitlist = waitlist; 
        while (!tempWaitlist.empty()) {
            Student* student = tempWaitlist.front();
            tempWaitlist.pop();
            cout << student->GetName() << endl;
        }
    }
 
    // Display priority queue students
    void DisplayPriorityQueue() const {
        cout << "Priority queue for " << title << ":" << endl;
        // Copy the queue to repeat
        queue<Student*> tempPriorityQueue = priorityQueue; 
        while (!tempPriorityQueue.empty()) {
            Student* student = tempPriorityQueue.front();
            tempPriorityQueue.pop();
            cout << student->GetName() << endl;
        }
    }
};
