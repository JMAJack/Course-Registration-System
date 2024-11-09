#include <iostream>
#include <fstream>
#include "Admin.h"
#include "Course.h"
#include "Student.h"
#include "StudentTracker.h"
#include "FileManager.h"
#include "LinkedList.h"
#include "Node.h"

using namespace std;

bool authenticateAdmin() {
    string adminCode;
    cout << "Enter admin code: ";
    cin >> adminCode;
    return adminCode == "admin123";
}

bool authenticateStudent(LinkedList<Student>& studentList) {
    int studentId;
    cout << "Enter your student ID: ";
    cin >> studentId;
    
    // Check if student ID exists in the student list
    Node<Student>* current = studentList.GetHead();
    while (current != nullptr) {
        if (current->GetData().GetId() == studentId) {
            cout << "Welcome, " << current->GetData().GetName() << "!" << endl;
            return true;
        }
        current = current->GetNext();
    }
    
    cout << "Student ID not found." << endl;
    return false;
}

int main() {
    // Sample students and courses setup
    Student student1(1, "John Doe", 3.8, true);
    Student student2(2, "Jane Smith", 3.2, false);

    LinkedList<Student> studentList;
    studentList.Insert(student1);
    studentList.Insert(student2);

    Course* prerequisites[2] = { nullptr, nullptr };
    Course course1("CS101", "Introduction to Computer Science", 3, 30, prerequisites);
    Course course2("CS102", "Data Structures", 3, 30, prerequisites);

    // Login prompt
    string userType;
    cout << "Are you a 'student' or 'admin'? ";
    cin >> userType;

    if (userType == "admin") {
        if (!authenticateAdmin()) {
            cout << "Incorrect admin code." << endl;
            return 0; // End program if admin authentication fails
        }
        cout << "Admin access granted." << endl;
        // Admin-specific functionality can be added here
    } else if (userType == "student") {
        if (!authenticateStudent(studentList)) {
            cout << "Authentication failed." << endl;
            return 0; // End program if student authentication fails
        }
        // Student-specific functionality can be added here
    } else {
        cout << "Invalid user type." << endl;
        return 0;
    }

    // The rest of the main program continues here
    // Enroll students in courses
    student1.GetEnrolledCourses().Insert(course1);
    student2.GetEnrolledCourses().Insert(course2);

    // Create StudentTracker
    StudentTracker tracker(course1, studentList, queue<Student>(), queue<Student>());

    // Save and load student tracker as shown previously
    FileManager::SaveStudentTracker(tracker, "student_tracker.dat");
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
