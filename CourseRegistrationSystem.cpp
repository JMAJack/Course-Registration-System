#include <iostream>
#include <fstream>
#include "Course.h"
#include "Student.h"
#include "StudentTracker.h"
#include "FileManager.h"
#include "LinkedList.h"
#include "Node.h"

using namespace std;

int main() {
    // Create sample students
    Student student1(1, "John Doe", 3.8, true);
    Student student2(2, "Jane Smith", 3.2, false);

    // Create sample courses
    Course* prerequisites[2] = { nullptr, nullptr };
    Course course1("CS101", "Introduction to Computer Science", 3, 30, prerequisites);
    Course course2("CS102", "Data Structures", 3, 30, prerequisites);

    // Enroll students in courses
    student1.GetEnrolledCourses().Insert(course1);
    student2.GetEnrolledCourses().Insert(course2);

    // Create LinkedLists for students
    LinkedList<Student> studentList;
    studentList.Insert(student1);
    studentList.Insert(student2);

    // Create StudentTracker
    StudentTracker tracker(course1, studentList, queue<Student>(), queue<Student>());

    // Save StudentTracker to binary file
    FileManager::SaveStudentTracker(tracker, "student_tracker.dat");

    // Load StudentTracker from binary file
    StudentTracker loadedTracker = FileManager::LoadStudentTracker("student_tracker.dat");

    // Display loaded data
    cout << "Loaded Course:" << endl;
    loadedTracker.GetCourse().Display();

    cout << "Loaded Enrolled Students:" << endl;
    loadedTracker.DisplayEnrolledStudents();

    cout << "Loaded Waitlist:" << endl;
    loadedTracker.DisplayWaitlist();

    cout << "Loaded Priority Queue:" << endl;
    loadedTracker.DisplayPriorityQueue();

    return 0;
}