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

Student FindStudent(LinkedList<Student> &studentList, int studentId)
{
    Node<Student> *curr = studentList.GetHead();
    while (curr != nullptr)
    {
        if (curr->GetData().GetId() == studentId)
        {
            return curr->GetData();
        }
        curr = curr->GetNext();
    }
    return Student();
}

Course FindCourse(LinkedList<Course> &courseList, string courseCode)
{
    Node<Course> *curr = courseList.GetHead();
    while (curr != nullptr)
    {
        if (curr->GetData().GetCode() == courseCode)
        {
            return curr->GetData();
        }
        curr = curr->GetNext();
    }
    return Course();
}

StudentTracker FindStudentTracker(LinkedList<StudentTracker> &studentTrackerList, Course course)
{
    Node<StudentTracker> *curr = studentTrackerList.GetHead();
    while (curr != nullptr)
    {
        if (curr->GetData().GetCourse() == course)
        {
            return curr->GetData();
        }
        curr = curr->GetNext();
    }
    return StudentTracker();
}

bool AuthenticateAdmin()
{
    string adminCode;
    cout << "Admin Login" << endl;
    cout << "Enter admin code: ";
    cin >> adminCode;
    return adminCode == "admin123";
}

Student AuthenticateStudent(LinkedList<Student> &studentList)
{
    cout << "Student Login" << endl;
    cout << "Enter your student ID: ";
    int studentId;
    cin >> studentId;

    // Check if student ID exists in the student list
    Student student = FindStudent(studentList, studentId);
    if (student.GetId() != 0)
    {
        cout << "Authentication successful." << endl << endl;
        return student;
    }else{
        cout << "Student ID not found. Please try again." << endl;
        return Student();
    }
}


//Puts temporary data into the files [TEST FUNCTION]
void prefileLoad(){
    //sample students and courses
    Course* prerequisites[2] = { nullptr, nullptr };
    Course course1("CS101", "Introduction to Computer Science", 3, 30, prerequisites);
    Course course2("CS102", "Data Structures", 3, 30, prerequisites);

    LinkedList<Course> courseList;
    courseList.Insert(course1);
    courseList.Insert(course2);


    Student student1(1, "John Doe", 3.5, courseList);
    Student student2(2, "Jane Smith", 3.0, courseList);

    LinkedList<Student> studentList;
    studentList.Insert(student1);
    studentList.Insert(student2);

    

    //sample student tracker
    StudentTracker tracker1(course1, studentList, queue<Student>(), queue<Student>());
    StudentTracker tracker2(course2, studentList, queue<Student>(), queue<Student>());

    LinkedList<StudentTracker> studentTrackerList;
    studentTrackerList.Insert(tracker1);
    studentTrackerList.Insert(tracker2);

    //save students, courses and trackers
    FileManager::SaveStudents(studentList, "students.dat");
    FileManager::SaveCourses(courseList, "courses.dat");
    FileManager::SaveStudentTrackers(studentTrackerList, "student_trackers.dat");


    //load students, courses and trackers
    LinkedList<Student> loadedStudents = FileManager::LoadStudents("students.dat");
    LinkedList<Course> loadedCourses = FileManager::LoadCourses("courses.dat");
    LinkedList<StudentTracker> loadedStudentTrackers = FileManager::LoadStudentTrackers("student_trackers.dat");
}

//TEST TO SEE IF DATA IS LOADED
void loadDisplay(Student student, LinkedList<StudentTracker> studentTrackerList)
{
    // Load the data of the student that signed in and their course in addition to tracker for that course
    student.Display();
    cout << endl
         << "Enrolled Courses:" << endl;

    if (student.GetEnrolledCourses().IsEmpty())
    {
        cout << "No courses enrolled" << endl << endl;
    }
    else
    {
        // Display the courses the student is enrolled in
        for (int i = 0; i < student.GetEnrolledCourses().Size(); i++)
        {
            Course course = student.GetEnrolledCourses().GetNode(i)->GetData();
            course.Display();
            cout << endl;

            // Display the student tracker for the course
            StudentTracker tracker = FindStudentTracker(studentTrackerList, course);
            tracker.Display();
            cout << endl;
        }
    }
}

int main()
{
    //prefileLoad();
    // Load Data from Files into Variables
    FileManager fileManager;
    LinkedList<Student> studentList = fileManager.LoadStudents("students.dat");
    LinkedList<Course> courseList = fileManager.LoadCourses("courses.dat");
    LinkedList<StudentTracker> studentTrackerList = fileManager.LoadStudentTrackers("student_trackers.dat");

    // Login prompt
    int choice;
    while (true)
    {
        cout << "Welcome to the Course Registration System!" << endl;
        cout << "Please select an option:" << endl;
        cout << "1. Login as student" << endl;
        cout << "2. Login as admin" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            {
                Student student = AuthenticateStudent(studentList);
                if (student.GetId() != 0)
                {
                    loadDisplay(student, studentTrackerList);
                }
            }
            break;

        case 2:
            if (!AuthenticateAdmin())
            {
                cout << "Incorrect admin code. Please try again" << endl;
            }
            break;

        case 3:
            cout << "Exiting..." << endl;
            return 0;
            break;

        default:
            cout << "Invalid choice. Please try again" << endl;
            break;
        }
    }
}
