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

class CourseRegistrationSystem
{
private:
    LinkedList<Student> studentList;
    LinkedList<Course> courseList;
    LinkedList<StudentTracker> studentTrackerList;
    stack<Course> addStack;
    stack<Course> dropStack;
    FileManager fileManager;

public:
    CourseRegistrationSystem()
    {
        LoadData();
    }

    // Helper functions
    void LoadData()
    {
        // Load Data from Files into Variables
        studentList = fileManager.LoadStudents("students.dat");
        courseList = fileManager.LoadCourses("courses.dat");
        studentTrackerList = fileManager.LoadStudentTrackers("student_trackers.dat");
    }

    void SaveData()
    {
        // Save Data from Variables into Files
        fileManager.SaveStudents(studentList, "students.dat");
        fileManager.SaveCourses(courseList, "courses.dat");
        fileManager.SaveStudentTrackers(studentTrackerList, "student_trackers.dat");
    }

    Student FindStudent(int studentId)
    {
        // Find a student by ID
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

    Course FindCourse(string courseCode)
    {
        // Find a course by code
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

    Course FindCourse(Student student, string courseCode)
    {
        // Find a course by code in a student's enrolled courses
        Node<Course> *curr = student.GetEnrolledCourses().GetHead();
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

    StudentTracker FindStudentTracker(Course course)
    {
        // Find a student tracker by course
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
        // Pause the system and wait for user input
        cout << endl
             << "\033[34mPress Enter to Continue...\033[0m";
        cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string FormatError(const string &message)
    {
        // Format error messages in red text
        return "\033[31m" + message + "\033[0m"; // 31 is the ANSI code for red text
    }

    string FormatCorrect(const string &message)
    {
        // Format correct messages in green text
        return "\033[32m" + message + "\033[0m"; // 32 is the ANSI code for green text
    }

    // Authentication functions
    bool AuthenticateAdmin()
    {
        // Authenticate admin user
        system("cls");
        string adminCode;
        cout << "\tAdmin Login" << endl;
        cout << "Enter your Admin ID: ";
        cin >> adminCode;
        if (adminCode == "admin123")
        {
            cout << FormatCorrect("Authentication successful.") << endl;
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

    Student AuthenticateStudent()
    {
        // Authenticate student user
        system("cls");
        cout << "\tStudent Login" << endl;

        cout << "Enter your student ID: ";
        int studentId;
        cin >> studentId;

        // Check if student ID exists in the student list
        Student student = FindStudent(studentId);
        if (student.GetId() != 0)
        {
            cout << FormatCorrect("Authentication successful.") << endl;
            Pause();
            return student;
        }
        else
        {
            cout << FormatError("Student ID not found. Please try again.") << endl;
            Pause();
            return Student();
        }
    }

    void prefileLoad()
    {
        // Preload some data into the system
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

        StudentTracker tracker1(course1, studentList, queue<Student>(), queue<Student>());
        StudentTracker tracker2(course2, studentList, queue<Student>(), queue<Student>());

        LinkedList<StudentTracker> studentTrackerList;
        studentTrackerList.Insert(tracker1);
        studentTrackerList.Insert(tracker2);

        fileManager.SaveStudents(studentList, "students.dat");
        fileManager.SaveCourses(courseList, "courses.dat");
        fileManager.SaveStudentTrackers(studentTrackerList, "student_trackers.dat");
    }

    // Course Registration functions
    void StudentInfo(Student student)
    {
        StudentTracker tracker;
        bool inList = false;

        cout << endl
             << "\tStudent Info:" << endl;
        student.Display();

        // Display Student's Enrolled Courses that they are not in a waitlist or queue for
        cout << endl
             << "\tEnrolled Courses:" << endl;

        if (student.GetEnrolledCourses().IsEmpty())
        {
            cout << "No courses enrolled" << endl
                 << endl;
        }
        else
        {
            for (int i = 0; i < student.GetEnrolledCourses().Size(); i++)
            {
                Course course = student.GetEnrolledCourses().GetNode(i)->GetData();
                course.Display();
                    cout << endl
                         << endl;
            }
        }

        if (student.GetIsPriority())
        {
            // Check if student is in any priority queue
            cout << endl
                 << "\tCourses in Priority Queue:" << endl;

            for (int i = 0; i < courseList.Size(); i++)
            {
                Course course = courseList.GetNode(i)->GetData();
                tracker = FindStudentTracker(course);
                if (tracker.IsInPriorityQueue(student))
                {
                    course.Display();
                    inList = true;
                }
            }

            if (!inList)
            {
                cout << "No courses in priority queue" << endl;
            }
        }
        else
        {
            // Display Student's Courses in Waitlist
            cout << endl
                 << "\tCourses in Waitlist:" << endl;
            for (int i = 0; i < courseList.Size(); i++)
            {
                Course course = courseList.GetNode(i)->GetData();
                tracker = FindStudentTracker(course);
                if (tracker.IsInWaitlist(student))
                {
                    course.Display();
                    inList = true;
                }
            }

            if (!inList)
            {
                cout << "No courses in waitlist" << endl;
            }
        }
    }

    void CourseEnrollment(Student student)
    {
        // Handle course enrollment for a student
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
                cout << "Available Courses:" << endl;
                for (int i = 0; i < courseList.Size(); i++)
                {
                    Course course = courseList.GetNode(i)->GetData();
                    cout << i + 1 << ". ";
                    course.Display();
                    cout << endl
                         << endl;
                }

                cout << "Enter the course code to enroll: ";
                string courseCode;
                cin >> courseCode;

                Course course = FindCourse(student, courseCode);
                if (course.GetCode() != "")
                {
                    cout << FormatError("Course already enrolled.") << endl
                         << endl;
                    Pause();
                }
                else
                {
                    // Check if the course exists in the course list
                    course = FindCourse(courseCode);
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
                        StudentTracker tracker = FindStudentTracker(course);
                        tracker.AddStudent(student);
                        cout << FormatCorrect("Course enrolled successfully.") << endl;
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

                    // Check to see if the student was already removed from course
                    if (FindCourse(student, course.GetCode()).GetCode() == "")
                    {
                        cout << FormatError("Student is already not enrolled in this course.") << endl;
                        Pause();
                        break;
                    }
                    else
                    {
                        student.GetEnrolledCourses().Remove(course);
                        StudentTracker tracker = FindStudentTracker(course);
                        tracker.RemoveStudent(student);
                        cout << FormatCorrect("Last enrollment undone.") << endl;
                        Pause();
                    }
                }
                else
                {
                    cout << FormatError("No courses have been enrolled in the current session.") << endl;
                    Pause();
                }
                break;

            case 3:
                return;
                break;

            default:
                cout << FormatError("Invalid choice. Please try again") << endl;
                Pause();
                break;
            }
        }
    }

    void CourseRemoval(Student student)
    {
        // Handle course removal for a student
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
                if (student.GetEnrolledCourses().IsEmpty())
                {
                    cout << "No courses enrolled" << endl;
                    Pause();
                    break;
                }
                else
                {
                    for (int i = 0; i < student.GetEnrolledCourses().Size(); i++)
                    {
                        Course course = student.GetEnrolledCourses().GetNode(i)->GetData();
                        if (course.GetCode() != "")
                        {
                            cout << course.GetCode() << ": " << course.GetTitle()
                                 << " (" << course.GetCredits() << " credits)" << endl;
                        }
                    }
                }

                // Ask the student to enter the course code
                cout << "Enter the course code to drop: ";
                string courseCode;
                cin >> courseCode;

                // Check if the student is already enrolled in the course
                Course course = FindCourse(student, courseCode);
                if (course.GetCode() == "")
                {
                    cout << FormatError("Course not found in enrolled courses.") << endl;
                    Pause();
                }
                else
                {
                    // Add the course to the drop stack
                    dropStack.push(course);

                    // Remove the student from the student tracker
                    StudentTracker tracker = FindStudentTracker(course);
                    tracker.RemoveStudent(student);
                    cout << FormatCorrect("Course dropped successfully.") << endl;
                    Pause();
                }
            }
            break;

            case 2:
                if (!dropStack.empty())
                {
                    Course course = dropStack.top();
                    dropStack.pop();

                    // Check to see if the student is already in course before adding back
                    if (FindCourse(student, course.GetCode()).GetCode() != "")
                    {
                        cout << FormatError("Student is already enrolled in this course.") << endl;
                        Pause();
                        break;
                    }
                    else
                    {

                        // Add the course back to the student's enrolled courses
                        student.GetEnrolledCourses().Insert(course);

                        // Add the student back to the student tracker
                        StudentTracker tracker = FindStudentTracker(course);
                        tracker.AddStudent(student);
                        cout << FormatCorrect("Last drop undone.") << endl;
                        Pause();
                    }
                }
                else
                {
                    cout << FormatError("No courses have been dropped in the current session.") << endl;
                    Pause();
                }
                break;

            case 3:
                return;
                break;

            default:
                cout << FormatError("Invalid choice. Please try again") << endl;
                Pause();
                break;
            }
        }
    }

    void StudentScreen(Student student)
    {
        // Display the student screen with options
        int choice;
        while (true)
        {
            system("cls");
            cout << "\tWelcome to the Course Registration System " << student.GetName() << endl;
            cout << "1. Enroll in a course" << endl;
            cout << "2. Drop a course" << endl;
            cout << "3. View Student Data" << endl;
            cout << "4. Go Back" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cout << endl;

            switch (choice)
            {
            case 1:
                CourseEnrollment(student);
                break;

            case 2:
                CourseRemoval(student);
                break;
            case 3:
                StudentInfo(student);
                Pause();
                break;
            case 4:
                return;
            default:
                cout << FormatError("Invalid choice. Please try again") << endl;
                Pause();
                break;
            }
        }
    }

    void MainMenu()
    {
        // Display the main menu with options
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
                Student student = AuthenticateStudent();
                if (student.GetId() != 0)
                {
                    StudentScreen(student);
                }
            }
            break;

            case 2:
                if (AuthenticateAdmin())
                {
                    cout << "Admin access granted." << endl;
                    Pause();
                }
                break;

            case 3:
                SaveData();
                cout << "Exiting..." << endl;
                return;
            default:
                cout << FormatError("Invalid choice. Please try again") << endl;
                Pause();
            }
        }
    }
};

int main()
{
    CourseRegistrationSystem system;
    system.MainMenu();
    return 0;
}
