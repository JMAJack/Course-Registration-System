#ifndef STUDENTTRACKER_H
#define STUDENTTRACKER_H

#include "Course.h"
#include "Student.h"
#include "LinkedList.h"
#include <queue>
#include <fstream>

class StudentTracker {
private:
    Course course;
    LinkedList<Student> enrolledStudents;
    queue<Student> waitlist;
    queue<Student> priorityQueue;

public:
    // Default constructor
    StudentTracker() {}

    // Parameterized constructor
    StudentTracker(const Course& course, const LinkedList<Student>& enrolled, const queue<Student>& wait, const queue<Student>& priority)
        : course(course), enrolledStudents(enrolled), waitlist(wait), priorityQueue(priority) {}

    // Accessors
    Course GetCourse() const { return course; }
    LinkedList<Student> GetEnrolledStudents() const { return enrolledStudents; }
    queue<Student> GetWaitlist() const { return waitlist; }
    queue<Student> GetPriorityQueue() const { return priorityQueue; }

    // Mutators
    void SetCourse(const Course& course) { this->course = course; }
    void SetEnrolledStudents(const LinkedList<Student>& enrolled) { enrolledStudents = enrolled; }
    void SetWaitlist(const queue<Student>& wait) { waitlist = wait; }
    void SetPriorityQueue(const queue<Student>& priority) { priorityQueue = priority; }
    void Display() {
        cout << "Enrolled Students: " << enrolledStudents.Size() << endl;
        cout << "Waitlist: " << waitlist.size() << endl;
        cout << "Priority Queue: " << priorityQueue.size() << endl;
    }
    

    // Serialize the StudentTracker data to a binary file
    void Serialize(ofstream& outFile) const {
        course.Serialize(outFile);

        // Serialize enrolledStudents LinkedList
        int studentCount = enrolledStudents.Size();
        outFile.write(reinterpret_cast<const char*>(&studentCount), sizeof(studentCount));
        Node<Student>* currentStudent = enrolledStudents.GetHead();
        while (currentStudent != nullptr) {
            currentStudent->GetData().Serialize(outFile); // Assuming Student has Serialize
            currentStudent = currentStudent->GetNext();
        }

        // Serialize waitlist queue
        int waitlistSize = waitlist.size();
        outFile.write(reinterpret_cast<const char*>(&waitlistSize), sizeof(waitlistSize));
        queue<Student> tempWaitlist = waitlist;
        while (!tempWaitlist.empty()) {
            tempWaitlist.front().Serialize(outFile); // Assuming Student has Serialize
            tempWaitlist.pop();
        }

        // Serialize priority queue
        int priorityQueueSize = priorityQueue.size();
        outFile.write(reinterpret_cast<const char*>(&priorityQueueSize), sizeof(priorityQueueSize));
        queue<Student> tempPriorityQueue = priorityQueue;
        while (!tempPriorityQueue.empty()) {
            tempPriorityQueue.front().Serialize(outFile); // Assuming Student has Serialize
            tempPriorityQueue.pop();
        }
    }

    // Deserialize the StudentTracker data from a binary file
    void Deserialize(ifstream& inFile) {
        course.Deserialize(inFile);

        // Deserialize enrolledStudents LinkedList
        int studentCount;
        inFile.read(reinterpret_cast<char*>(&studentCount), sizeof(studentCount));
        enrolledStudents = LinkedList<Student>();
        for (int i = 0; i < studentCount; ++i) {
            Student student;
            student.Deserialize(inFile); // Assuming Student has Deserialize
            enrolledStudents.Insert(student);
        }

        // Deserialize waitlist queue
        int waitlistSize;
        inFile.read(reinterpret_cast<char*>(&waitlistSize), sizeof(waitlistSize));
        for (int i = 0; i < waitlistSize; ++i) {
            Student student;
            student.Deserialize(inFile); // Assuming Student has Deserialize
            waitlist.push(student);
        }

        // Deserialize priority queue
        int priorityQueueSize;
        inFile.read(reinterpret_cast<char*>(&priorityQueueSize), sizeof(priorityQueueSize));
        for (int i = 0; i < priorityQueueSize; ++i) {
            Student student;
            student.Deserialize(inFile); // Assuming Student has Deserialize
            priorityQueue.push(student);
        }
    }

    // ADDITIONAL FUNCTIONS
    void AddStudent(Student student) {
        if (enrolledStudents.Size() < course.GetMaxCapacity()) {
            // check if student meets prerequisites
            for (int i = 0; i < 2; i++) {
                if (course.GetPrerequisites(i) != nullptr) {
                    if (student.GetEnrolledCourses().Search(*course.GetPrerequisites(i)) == nullptr) {
                        cout << "Student " << student.GetName() << " does not meet prerequisites for " << course.GetTitle() << endl;
                        return;
                    }
                }
            }
            student.GetEnrolledCourses().Insert(course);
            enrolledStudents.Insert(student);
            cout << "Student " << student.GetName() << " added to " << course.GetCode()<< ": "<< course.GetTitle() << endl;
        } else {
            if (student.GetIsPriority()) {
                priorityQueue.push(student);
                cout << "Student " << student.GetName() << " added to priority queue for " << course.GetCode()<< ": "<< course.GetTitle() << endl;
            } else {
                waitlist.push(student);
                cout << "Student " << student.GetName() << " added to waitlist for " << course.GetCode()<< ": "<< course.GetTitle() << endl;
            }
        }
    }

    void RemoveStudent(Student student) {
        // if student is in enrolledStudents
        if (enrolledStudents.Search(student) != nullptr) {
            student.GetEnrolledCourses().Remove(course);
            enrolledStudents.Remove(student);
            cout << "Student " << student.GetName() << " removed from " << course.GetCode()<< ": "<< course.GetTitle() << endl;
            // if priorityQueue is not empty
            if (!priorityQueue.empty()) {
                Student nextPriorityStudent = priorityQueue.front();
                priorityQueue.pop();
                AddStudent(nextPriorityStudent);
            }
            // if waitlist is not empty
            else if (!waitlist.empty()) {
                Student nextWaitlistStudent = waitlist.front();
                waitlist.pop();
                AddStudent(nextWaitlistStudent);
            }
        }

        // if student is in priorityQueue
        else if (priorityQueue.front() == student) {
            priorityQueue.pop();
            cout << "Student " << student.GetName() << " removed from priority queue for " << course.GetCode()<< ": "<< course.GetTitle() << endl;
        }

        // if student is in waitlist
        else if (waitlist.front() == student) {
            waitlist.pop();
            cout << "Student " << student.GetName() << " removed from waitlist for " << course.GetCode()<< ": "<< course.GetTitle() << endl;
        }
    }

    void DisplayEnrolledStudents()  {
        cout << "Students enrolled in " << course.GetCode()<< ": "<< course.GetTitle() << ":" << endl;
        enrolledStudents.DisplayList();
    }

    void DisplayWaitlist() const {
        cout << "Waitlist for " << course.GetCode()<< ": "<< course.GetTitle() << ":" << endl;
        queue<Student> tempWaitlist = waitlist;
        while (!tempWaitlist.empty()) {
            cout << tempWaitlist.front().GetName() << endl;
            tempWaitlist.pop();
        }
    }

    void DisplayPriorityQueue() const {
        cout << "Priority queue for " << course.GetCode()<< ": "<< course.GetTitle() << ":" << endl;
        queue<Student> tempPriorityQueue = priorityQueue;
        while (!tempPriorityQueue.empty()) {
            cout << tempPriorityQueue.front().GetName() << endl;
            tempPriorityQueue.pop();
        }
    }

    bool IsInPriorityQueue(Student student) const {
        queue<Student> tempPriorityQueue = priorityQueue;
        while (!tempPriorityQueue.empty()) {
            if (tempPriorityQueue.front() == student) {
                return true;
            }
            tempPriorityQueue.pop();
        }
        return false;
    }

    bool IsInWaitlist(Student student) const {
        queue<Student> tempWaitlist = waitlist;
        while (!tempWaitlist.empty()) {
            if (tempWaitlist.front() == student) {
                return true;
            }
            tempWaitlist.pop();
        }
        return false;
    }
};

#endif // STUDENTTRACKER_H