#include <iostream>
#include <fstream>
#include "Admin.h"
#include "Course.h"
#include "Student.h"
#include "StudentTracker.h"
#include "FileManager.h"
#include "LinkedList.h"
#include "Node.h"
#include <stack>

using namespace std;

// Helper functions
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

void Pause()
{
    cout << endl
         << "\033[34mPress Enter to Continue...\033[0m";
    cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string FormatError(const string &message)
{
    return "\033[31m" + message + "\033[0m"; // 31 is the ANSI code for red text
}

// Authentication functions
bool AuthenticateAdmin()
{
    system("cls");
    string adminCode;
    cout << "\tAdmin Login" << endl;
    cout << "Enter your Admin ID: ";
    cin >> adminCode;
    if (adminCode == "admin123")
    {
        cout << "Authentication successful." << endl;
        Pause();
        return true;
    }
    else
    {
        cout << FormatError("Incorrect admin code. Please try again.") << endl;
        Pause();
        return false;
    }
}

Student AuthenticateStudent(LinkedList<Student> &studentList)
{
    system("cls");
    cout << "\tStudent Login" << endl;

    cout << "Enter your student ID: ";
    int studentId;
    cin >> studentId;

    // Check if student ID exists in the student list
    Student student = FindStudent(studentList, studentId);
    if (student.GetId() != 0)
    {
        return student;
    }
    else
    {
        cout << FormatError("Student ID not found. Please try again.") << endl;
        Pause();
        return Student();
    }
}

// Puts temporary data into the files [TEST FUNCTION]
void prefileLoad()
{
    // sample students and courses
    Course *prerequisites[2] = {nullptr, nullptr};
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

    // sample student tracker
    StudentTracker tracker1(course1, studentList, queue<Student>(), queue<Student>());
    StudentTracker tracker2(course2, studentList, queue<Student>(), queue<Student>());

    LinkedList<StudentTracker> studentTrackerList;
    studentTrackerList.Insert(tracker1);
    studentTrackerList.Insert(tracker2);

    // save students, courses and trackers
    FileManager::SaveStudents(studentList, "students.dat");
    FileManager::SaveCourses(courseList, "courses.dat");
    FileManager::SaveStudentTrackers(studentTrackerList, "student_trackers.dat");

    // load students, courses and trackers
    LinkedList<Student> loadedStudents = FileManager::LoadStudents("students.dat");
    LinkedList<Course> loadedCourses = FileManager::LoadCourses("courses.dat");
    LinkedList<StudentTracker> loadedStudentTrackers = FileManager::LoadStudentTrackers("student_trackers.dat");
}

// Course Enrollment Functions

// Student Info function
void StudentInfo(Student student, LinkedList<StudentTracker> studentTrackerList)
{
    // Load the data of the student that signed in and their course in addition to tracker for that course
    cout << endl
         << "\tStudent Info:" << endl;
    student.Display();
    cout << endl
         << "\tEnrolled Courses:" << endl;

    if (student.GetEnrolledCourses().IsEmpty())
    {
        cout << "No courses enrolled" << endl
             << endl;
    }
    else
    {
        // Display the courses the student is enrolled in
        for (int i = 0; i < student.GetEnrolledCourses().Size(); i++)
        {
            Course course = student.GetEnrolledCourses().GetNode(i)->GetData();
            course.Display();
            cout << endl
                 << endl;
        }
    }
}

// Course Enrollment Screen
stack<Course> CourseEnrollment(Student student, LinkedList<StudentTracker> studentTrackerList, LinkedList<Course> courseList,
                               stack<Course> addStack)
{
    int choice;
    while (true)
    {
        system("cls");
        cout << "\tCourse Enrollment" << endl;
        cout << "1. Enroll in a course" << endl;
        cout << "2. Undo last enrollment" << endl;
        cout << "3. Go Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            // Display the courses available for enrollment
            cout << "Available Courses:" << endl;
            for (int i = 0; i < student.GetEnrolledCourses().Size(); i++)
            {
                Course course = student.GetEnrolledCourses().GetNode(i)->GetData();
                cout << i + 1 << ". ";
                course.Display();
                cout << endl;
            }

            // Ask the student to enter the course code
            cout << "Enter the course code to enroll: ";
            string courseCode;
            cin >> courseCode;

            // Check if the student is already enrolled in the course
            Course course = FindCourse(student.GetEnrolledCourses(), courseCode);
            if (course.GetCode() != "")
            {
                cout << FormatError("Course already enrolled.") << endl
                     << endl;
                Pause();
            }
            else
            {
                // Check if the course exists in the course list
                course = FindCourse(courseList, courseCode);
                if (course.GetCode() == "")
                {
                    cout << FormatError("Course not found.") << endl;
                    Pause();
                }
                else
                {
                    addStack.push(course);

                    // Add the course to the student's enrolled courses
                    student.GetEnrolledCourses().Insert(course);

                    // Add the student to the student tracker
                    StudentTracker tracker = FindStudentTracker(studentTrackerList, course);
                    tracker.AddStudent(student);


                    cout << "Course " << course.GetCode() << ": " << course.GetTitle() << " enrolled successfully." << endl;
                    Pause();
                }
            }
        }
        break;

        case 2:
            if (!addStack.empty())
            {
                Course course = addStack.top();
                addStack.pop();

                // Remove the course from the student's enrolled courses
                student.GetEnrolledCourses().Remove(course);

                // Remove the student from the student tracker
                StudentTracker tracker = FindStudentTracker(studentTrackerList, course);
                tracker.RemoveStudent(student);

                cout << "Last enrolled course " << course.GetCode() << ": " << course.GetTitle() << " removed successfully." << endl;
                Pause();
            }
            else
            {
                cout << FormatError("No courses have been enrolled in the current session.") << endl;
                Pause();
            }
            break;

        case 3:
            return addStack;
            break;

        default:
            cout << FormatError("Invalid choice. Please try again") << endl;
            Pause();
            break;
        }
    }
}

// Course Removal Screen
stack<Course> CourseRemoval(Student student, LinkedList<StudentTracker> studentTrackerList, stack<Course> dropStack)
{
    int choice;
    while (true)
    {
        system("cls");
        cout << "\tCourse Removal" << endl;
        cout << "1. Drop a course" << endl;
        cout << "2. Undo last drop" << endl;
        cout << "3. Go Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            // Display the courses the student is already enrolled in
            cout << "Enrolled Courses:" << endl;
            for (int i = 0; i < student.GetEnrolledCourses().Size(); i++)
            {
                Course course = student.GetEnrolledCourses().GetNode(i)->GetData();
                cout << i + 1 << ". " << course.GetCode() << ": " << course.GetTitle()
                     << " (" << course.GetCredits() << " credits)" << endl;
            }

            // Ask the student to enter the course code
            cout << "Enter the course code to drop: ";
            string courseCode;
            cin >> courseCode;

            // Check if the student is already enrolled in the course
            Course course = FindCourse(student.GetEnrolledCourses(), courseCode);
            if (course.GetCode() == "")
            {
                cout << FormatError("Course not found in enrolled courses.") << endl;
                Pause();
            }
            else
            {
                // Add the course to the drop stack
                dropStack.push(course);

                // Remove the course from the student's enrolled courses
                student.GetEnrolledCourses().Remove(course);

                // Remove the student from the student tracker
                StudentTracker tracker = FindStudentTracker(studentTrackerList, course);
                tracker.RemoveStudent(student);

                cout << "Course " << course.GetCode() << ": " << course.GetTitle() << " dropped successfully." << endl;
                Pause();
            }
        }
        break;

        case 2:
            if (!dropStack.empty())
            {
                Course course = dropStack.top();
                dropStack.pop();

                // Add the course back to the student's enrolled courses
                student.GetEnrolledCourses().Insert(course);

                // Add the student back to the student tracker
                StudentTracker tracker = FindStudentTracker(studentTrackerList, course);
                tracker.AddStudent(student);

                cout << "Last dropped course " << course.GetCode() << ": " << course.GetTitle() << " added back successfully." << endl;
                Pause();
            }
            else
            {
                cout << FormatError("No courses have been dropped in the current session.") << endl;
                Pause();
            }
            break;

        case 3:
            return dropStack;
            break;

        default:
            cout << FormatError("Invalid choice. Please try again") << endl;
            Pause();
            break;
        }
    }
}

// Student Screen
void StudentScreen(Student student, LinkedList<StudentTracker> studentTrackerList, LinkedList<Course> courseList)
{
    stack<Course> dropStack;
    stack<Course> addStack;
    int choice;
    while (true)
    {
        system("cls");
        cout << "\tWelcome to the Course Registraion System " << student.GetName() << endl;
        cout << "1. Enroll in a course" << endl;
        cout << "2. Drop a course" << endl;
        cout << "3. View Student Data" << endl;
        cout << "4. Go Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {

        // Enroll in a course
        case 1:
            addStack = CourseEnrollment(student, studentTrackerList, courseList, addStack);
            break;

        // Drop a course
        case 2:
            dropStack = CourseRemoval(student, studentTrackerList, dropStack);
            break;

        // View Student Data
        case 3:
            StudentInfo(student, studentTrackerList);
            Pause();
            break;

        case 4:
            return;
            break;

        default:
            cout << FormatError("Invalid choice. Please try again") << endl;
            Pause();
            break;
        }
    }
}

void loadData(FileManager fileManager, LinkedList<Student> &studentList, LinkedList<Course> &courseList, LinkedList<StudentTracker> &studentTrackerList){
    // Load Data from Files into Variables
    studentList = fileManager.LoadStudents("students.dat");
    courseList = fileManager.LoadCourses("courses.dat");
    studentTrackerList = fileManager.LoadStudentTrackers("student_trackers.dat");
}
void saveData(FileManager fileManager, LinkedList<Student> &studentList, LinkedList<Course> &courseList, LinkedList<StudentTracker> &studentTrackerList){
    // Save Data from Variables into Files
    fileManager.SaveStudents(studentList, "students.dat");
    fileManager.SaveCourses(courseList, "courses.dat");
    fileManager.SaveStudentTrackers(studentTrackerList, "student_trackers.dat");
}

int main()
{
    //prefileLoad();
    //  Load Data from Files into Variables
    FileManager fileManager;
    LinkedList<Student> studentList = fileManager.LoadStudents("students.dat");
    LinkedList<Course> courseList = fileManager.LoadCourses("courses.dat");
    LinkedList<StudentTracker> studentTrackerList = fileManager.LoadStudentTrackers("student_trackers.dat");

    // Login prompt
    int choice;
    while (true)
    {
        system("cls");

        cout << "\tWelcome to the Course Registration System!" << endl;
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
                StudentScreen(student, studentTrackerList, courseList);
            }
        }
        break;

        case 2:
            if (AuthenticateAdmin())
            {
                cout << "Debug run function" << endl;
                Pause();
            }
            break;

        case 3:
            cout << "Exiting..." << endl;
            return 0;
            break;

        default:
            cout << FormatError("Invalid choice. Please try again") << endl;
            Pause();
            break;
        }
    }
}
