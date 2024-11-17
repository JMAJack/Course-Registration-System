#include <iostream>
#include <fstream>
#include <stack>
#include <string>

#include "Course.h"
#include "Student.h"
#include "StudentTracker.h"
#include "FileManager.h"
#include "LinkedList.h"
#include "Node.h"

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
        Pause();
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

    Course *FindCoursePtr(string courseCode)
    {
        // Find a course by code
        Node<Course> *curr = courseList.GetHead();
        while (curr != nullptr)
        {
            if (curr->GetData().GetCode() == courseCode)
            {
                return &curr->GetData();
            }
            curr = curr->GetNext();
        }
        return nullptr;
    }

    Course FindEnrolledCourse(Student &student, string courseCode)
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

    StudentTracker FindStudentTracker(const Course &course)
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

    int GetValidInteger(string prompt)
    {
        int input;
        while (true)
        {
            string rawInput;
            cin >> rawInput; // Read input as a string to validate it manually.

            // Check if the input is a positive integer.
            bool isValid = true;
            for (char c : rawInput)
            {
                if (!isdigit(c)) // Ensure all characters are digits.
                {
                    isValid = false;
                    break;
                }
            }

            if (isValid)
            {
                try
                {
                    // Convert the input to an integer and ensure it's positive.
                    input = stoi(rawInput);
                    if (input > 0)
                    {
                        return input;
                    }
                    else
                    {
                        isValid = false;
                    }
                }
                catch (const exception &e)
                {
                    isValid = false; // Handle overflow or invalid conversion.
                }
            }

            // Handle invalid input.
            cout << endl;
            cout << FormatError("Invalid input. Please enter a valid positive integer.") << endl;
            cout << prompt;

            // Clear the input buffer in case of invalid raw input.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    float GetValidFloat(string prompt)
    {
        float input;
        while (true)
        {
            cin >> input;

            // Check if the input failed
            if (cin.fail() || input < 0)
            {
                cin.clear();                                         // Clear the failbit
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << endl;
                cout << FormatError("Invalid input. Please enter a valid positive float") << endl;
                cout << prompt;
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover input
                return input;                                        // Valid input
            }
        }
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
        studentId = GetValidInteger("Enter your student ID: ");

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

    // Course Registration functions
    void StudentInfo(Student &student)
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
                cout << endl;
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

    void CourseEnrollment(Student &student)
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
            choice = GetValidInteger("Enter your choice: ");
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

                Course course = FindEnrolledCourse(student, courseCode);
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

                        // Add the student to the student tracker
                        StudentTracker tracker = FindStudentTracker(course);
                        tracker.AddStudent(student);

                        if (tracker.GetEnrolledStudents().Search(student) == nullptr)
                        {
                            // If student is not in the enrolled students list, display error message
                            // This could be for if they dont meet the prerequisites
                            cout << FormatError("Course Enrollment Failed") << endl;
                            Pause();
                        }
                        else
                        {
                            // Update tracker in StudentTrackerList
                            studentTrackerList.EditNode(FindStudentTracker(course), tracker);
                            cout << FormatCorrect("Course enrolled successfully.") << endl;
                            Pause();
                        }
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
                    if (FindEnrolledCourse(student, course.GetCode()).GetCode() == "")
                    {
                        cout << FormatError("Student is already not enrolled in this course.") << endl;
                        Pause();
                        break;
                    }
                    else
                    {
                        StudentTracker tracker = FindStudentTracker(course);
                        tracker.RemoveStudent(student);
                        studentTrackerList.EditNode(FindStudentTracker(course), tracker);
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

    void CourseRemoval(Student &student)
    {
        // Handle course removal for a student
        int choice;
        bool inList = false;

        while (true)
        {
            system("cls");
            cout << "\tCourse Removal" << endl;
            cout << "1. Drop a course" << endl;
            cout << "2. Undo last drop" << endl;
            cout << "3. Go Back" << endl;
            cout << "Enter your choice: ";
            choice = GetValidInteger("Enter your choice: ");
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
                    cout << endl;
                }

                if (student.GetIsPriority())
                {
                    cout << "Priority Queue: " << endl;
                    for (int i = 0; i < courseList.Size(); i++)
                    {
                        Course course = courseList.GetNode(i)->GetData();
                        StudentTracker tracker = FindStudentTracker(course);
                        if (tracker.IsInPriorityQueue(student))
                        {
                            cout << course.GetCode() << ": " << course.GetTitle()
                                 << " (" << course.GetCredits() << " credits)" << endl;
                            inList = true;
                        }
                    }

                    if (!inList)
                    {
                        cout << "No courses in Priority Queue" << endl;
                        cout << endl;
                    }
                }
                else
                {
                    cout << "Waitlist: " << endl;
                    for (int i = 0; i < courseList.Size(); i++)
                    {
                        Course course = courseList.GetNode(i)->GetData();
                        StudentTracker tracker = FindStudentTracker(course);
                        if (tracker.IsInWaitlist(student))
                        {
                            cout << course.GetCode() << ": " << course.GetTitle()
                                 << " (" << course.GetCredits() << " credits)" << endl;
                            inList = true;
                        }
                    }

                    if (!inList)
                    {
                        cout << "No courses in waitlist" << endl;
                        cout << endl;
                    }
                }

                // Ask the student to enter the course code
                cout << "Enter the course code to drop: ";
                string courseCode;
                cin >> courseCode;

                // Check if the student is in the priority queue or waitlist for course then remove them there
                for (int i = 0; i < courseList.Size(); i++)
                {
                    Course course = courseList.GetNode(i)->GetData();
                    StudentTracker tracker = FindStudentTracker(course);
                    if (tracker.IsInPriorityQueue(student) && course.GetCode() == courseCode)
                    {
                        dropStack.push(course);
                        tracker.RemoveStudent(student);
                        studentTrackerList.EditNode(FindStudentTracker(course), tracker);
                        cout << FormatCorrect("Student removed from priority queue.") << endl;
                        Pause();
                        break;
                    }
                    else if (tracker.IsInWaitlist(student) && course.GetCode() == courseCode)
                    {
                        dropStack.push(course);
                        tracker.RemoveStudent(student);
                        studentTrackerList.EditNode(FindStudentTracker(course), tracker);
                        cout << FormatCorrect("Student removed from waitlist.") << endl;
                        Pause();
                        break;
                    }
                }

                // Check if the course is in the student's enrolled courses
                Course course = FindEnrolledCourse(student, courseCode);
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
                    studentTrackerList.EditNode(FindStudentTracker(course), tracker);
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
                    if (FindEnrolledCourse(student, course.GetCode()).GetCode() != "")
                    {
                        cout << FormatError("Student is already enrolled in this course.") << endl;
                        Pause();
                        break;
                    }
                    else
                    {

                        // Add the student back to the student tracker
                        StudentTracker tracker = FindStudentTracker(course);
                        tracker.AddStudent(student);

                        if (tracker.GetEnrolledStudents().Search(student) == nullptr)
                        {
                            // If student is not in the enrolled students list, display error message
                            // This could be for if they dont meet the prerequisites
                            cout << FormatError("Course Enrollment Failed") << endl;
                            Pause();
                        }
                        else
                        {
                            // Update tracker in StudentTrackerList
                            studentTrackerList.EditNode(FindStudentTracker(course), tracker);
                            cout << FormatCorrect("Last drop undone.") << endl;
                            Pause();
                        }
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

    void StudentScreen(Student &student)
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
            choice = GetValidInteger("Enter your choice: ");
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

    void StudentManagementScreen()
    {
        // Options to add, remove or modify students

        int choice;
        while (true)
        {
            system("cls");

            cout << "\tStudent Management Panel" << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Remove Student" << endl;
            cout << "3. Modify Student" << endl;
            cout << "4. Go Back" << endl;
            cout << "Enter your choice: ";
            choice = GetValidInteger("Enter your choice: ");

            switch (choice)
            {
            case 1:
            {
                // Ask for student details and add student
                Student student;
                cout << "Enter student ID: ";
                int id;
                id = GetValidInteger("Enter student ID: ");

                cout << "Enter student name: ";
                string name;
                cin.ignore();
                getline(cin, name); // clearing buffer and getting the whole line

                cout << "Enter student GPA: ";
                float gpa;
                gpa = GetValidFloat("Enter student GPA: ");

                student.SetId(id);
                student.SetName(name);
                student.SetGPA(gpa);

                Student checkStudent = FindStudent(id);
                // Student already exists
                if (checkStudent.GetId() == id)
                {
                    cout << FormatError("Student already exists.") << endl;
                }
                else
                {

                    studentList.Insert(student);
                    cout << FormatCorrect("Student added successfully.") << endl;
                }

                Pause();
                break;
            }

            case 2:
            {
                // Display students (ID and Name) and ask for ID to remove

                cout << "Students:" << endl;
                for (int i = 0; i < studentList.Size(); i++)
                {
                    Student student = studentList.GetNode(i)->GetData();
                    cout << "ID " << student.GetId() << ": " << student.GetName() << endl;
                }
                cout << endl;
                cout << "Enter student ID of the student you would like to remove: ";
                int id;
                id = GetValidInteger("Enter student ID of the student you would like to remove: ");

                Student student = FindStudent(id);
                if (student.GetId() == 0)
                {
                    cout << FormatError("Student not found.") << endl;
                }
                else
                {
                    // Check if student is enrolled in any courses, or is in the waitlist or priority queue
                    // for any courses and remove student from them accordingly
                    for (int i = 0; i < courseList.Size(); i++)
                    {
                        Course course = courseList.GetNode(i)->GetData();
                        StudentTracker tracker = FindStudentTracker(course);
                        tracker.RemoveStudent(student);
                    }

                    studentList.Remove(student);
                    cout << FormatCorrect("Student removed successfully.") << endl;
                }

                Pause();
                break;
            }

            case 3:
            {
                // Display students (ID and Name) and ask for ID to modify

                cout << "Students:" << endl;
                for (int i = 0; i < studentList.Size(); i++)
                {
                    Student student = studentList.GetNode(i)->GetData();
                    cout << "ID " << student.GetId() << ": " << student.GetName() << endl;
                }
                cout << endl;
                cout << "Enter the student ID of the student you would like to modify: ";
                int id;
                id = GetValidInteger("Enter the student ID of the student you would like to modify: ");

                Student check = FindStudent(id);
                if (check.GetId() == 0)
                {
                    cout << FormatError("Student not found.") << endl;
                }
                else
                {
                    Student student = FindStudent(id);
                    // Ask for new student details and modify student
                    cout << "Enter new or current student id: ";
                    int newId;
                    newId = GetValidInteger("Enter new or current student id: ");
                    Student temp = FindStudent(newId);
                    // Check if the new ID is unique or the current ID of the student being modified
                    if (temp == check || temp.GetId() == 0)
                    {
                        cout << "Enter new or current student name: ";
                        string name;
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter new or current student GPA: ";
                        float gpa;
                        gpa = GetValidFloat("Enter new or current student GPA: ");
                        student.SetId(newId);
                        student.SetName(name);
                        student.SetGPA(gpa);

                        // Update the student in the queues and waitlists
                        for (int i = 0; i < courseList.Size(); i++)
                        {
                            Course course = courseList.GetNode(i)->GetData();
                            StudentTracker tracker = FindStudentTracker(course);
                            if (tracker.IsInPriorityQueue(check))
                            {
                                tracker.RemoveStudent(check);
                                tracker.AddStudent(student);
                            }
                            else if (tracker.IsInWaitlist(check))
                            {
                                tracker.RemoveStudent(check);
                                tracker.AddStudent(student);
                            }
                        }

                        studentList.EditNode(check, student);

                        cout << FormatCorrect("Student modified successfully.") << endl;
                    }
                    else
                    {
                        cout << FormatError("Student ID must be new or the current ID of the Student you are modifying.") << endl;
                    }
                }
                Pause();
                break;
            }

            case 4:
                // go back
                return;

            default:
                cout << FormatError("Invalid choice. Please try again") << endl;
                Pause();
            }
        }
    }

    void CourseManagementScreen()
    {
        // Options to add, remove or modify courses

        int choice;
        while (true)
        {
            system("cls");

            cout << "\tCourse Management Panel" << endl;
            cout << "1. Add Course" << endl;
            cout << "2. Remove Course" << endl;
            cout << "3. Modify Course" << endl;
            cout << "4. Go Back" << endl;
            cout << "Enter your choice: ";
            choice = GetValidInteger("Enter your choice: ");

            switch (choice)
            {
            case 1:
            {
                // Ask for course details and add course
                Course course;
                cout << "Enter course code: ";
                string code;
                cin >> code;

                cout << "Enter course title: ";
                string title;
                cin.ignore();
                getline(cin, title);

                cout << "Enter course credits: ";
                int credits;
                credits = GetValidInteger("Enter course credits: ");

                cout << "Enter course max capacity: ";
                int maxCapacity;
                maxCapacity = GetValidInteger("Enter course max capacity: ");

                // Enter prerequisites if any
                Course *prerequisites[2] = {nullptr, nullptr};
                string prereqCode;
                for (int i = 0; i < 2; i++)
                {
                    cout << "Enter prerequisite course code " << i + 1 << ". (or Enter 'None'): ";
                    cin >> prereqCode;
                    if (prereqCode != "None")
                    {
                        Course *prereq = FindCoursePtr(prereqCode);
                        if (prereq == nullptr || prereq->GetCode() == code)
                        {
                            cout << FormatError("Prerequisite course not valid or found.") << endl;
                            i--;
                        }
                        else
                        {
                            prerequisites[i] = prereq;
                        }
                    }
                    else
                    {
                        break;
                    }
                }

                course.SetCode(code);
                course.SetTitle(title);
                course.SetCredits(credits);
                course.SetMaxCapacity(maxCapacity);
                course.SetPrerequisites(prerequisites);

                Course checkCourse = FindCourse(code);
                // Course already exists
                if (checkCourse.GetCode() == code)
                {
                    cout << FormatError("Course already exists.") << endl;
                }
                else
                {
                    courseList.Insert(course);
                    StudentTracker tracker(course, LinkedList<Student>(), queue<Student>(), queue<Student>());
                    studentTrackerList.Insert(tracker);
                    cout << FormatCorrect("Course added successfully.") << endl;
                }

                Pause();
                break;
            }

            case 2:
            {
                // Display courses (Code and Title) and ask for Code to remove

                cout << "Courses:" << endl;
                for (int i = 0; i < courseList.Size(); i++)
                {
                    Course course = courseList.GetNode(i)->GetData();
                    cout << "Course Code " << course.GetCode() << ": " << course.GetTitle() << endl;
                }
                cout << endl;
                cout << "Enter course code of the course you would like to remove: ";
                string code;
                cin >> code;

                Course course = FindCourse(code);
                if (course.GetCode() == "")
                {
                    cout << FormatError("Course not found.") << endl;
                }
                else
                {
                    StudentTracker tracker = FindStudentTracker(course);
                    // Check if any students are enrolled in the course and remove them
                    for (int i = 0; i < tracker.GetEnrolledStudents().Size(); i++)
                    {
                        Student student = tracker.GetEnrolledStudents().GetNode(i)->GetData();
                        student.GetEnrolledCourses().Remove(course);
                        studentList.EditNode(FindStudent(student.GetId()), student);
                    }

                    courseList.Remove(course);
                    studentTrackerList.Remove(tracker);
                    cout << FormatCorrect("Course removed successfully.") << endl;
                }
                Pause();
                break;
            }

            case 3:
            {
                // Display courses (Code and Title) and ask for Code to modify

                cout << "Courses:" << endl;
                for (int i = 0; i < courseList.Size(); i++)
                {
                    Course course = courseList.GetNode(i)->GetData();
                    cout << "Course Code " << course.GetCode() << ": " << course.GetTitle() << endl;
                }
                cout << endl;
                cout << "Enter the course code of the course you would like to modify: ";
                string code;
                cin >> code;

                Course check = FindCourse(code);
                if (check.GetCode() == "")
                {
                    cout << FormatError("Course not found.") << endl;
                }
                else
                {
                    Course course = FindCourse(code);
                    // Ask for new course details and modify course
                    cout << "Enter new or current course code: ";
                    string newCode;
                    cin >> newCode;
                    Course temp = FindCourse(newCode);
                    // Check if the new code is unique or the current code of the course being modified
                    if (temp == check || temp.GetCode() == "")
                    {
                        cout << "Enter new or current course title: ";
                        string title;
                        cin.ignore();
                        getline(cin, title);
                        cout << "Enter new or current course credits: ";
                        int credits;
                        credits = GetValidInteger("Enter new or current course credits: ");
                        cout << "Enter new or current course max capacity: ";
                        int maxCapacity;
                        maxCapacity = GetValidInteger("Enter new or current course max capacity: ");

                        // Enter prerequisites if any
                        Course *prerequisites[2] = {nullptr, nullptr};
                        string prereqCode;
                        for (int i = 0; i < 2; i++)
                        {
                            cout << "Enter new or current prerequisite course code " << i + 1 << ". (or Enter 'None'): ";
                            cin >> prereqCode;
                            if (prereqCode != "None")
                            {
                                Course *prereq = FindCoursePtr(prereqCode);
                                if (prereq == nullptr || prereq->GetCode() == code)
                                {
                                    cout << FormatError("Prerequisite course not valid or found.") << endl;
                                    i--;
                                }
                                else
                                {
                                    prerequisites[i] = prereq;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }

                        course.SetCode(newCode);
                        course.SetTitle(title);
                        course.SetCredits(credits);
                        course.SetMaxCapacity(maxCapacity);
                        course.SetPrerequisites(prerequisites);

                        StudentTracker tracker = FindStudentTracker(check);
                        tracker.SetCourse(course);
                        for (int i = 0; i < tracker.GetEnrolledStudents().Size(); i++)
                        {
                            Student student = tracker.GetEnrolledStudents().GetNode(i)->GetData();
                            student.GetEnrolledCourses().EditNode(check, course);
                            studentList.EditNode(FindStudent(student.GetId()), student);
                        }

                        courseList.EditNode(check, course);
                        studentTrackerList.EditNode(FindStudentTracker(check), tracker);

                        cout << FormatCorrect("Course modified successfully.") << endl;
                    }
                    else
                    {
                        cout << FormatError("Course code must be new or the current code of the Course you are modifying.") << endl;
                    }
                }
                Pause();
                break;
            }

            case 4:
                // go back
                return;

            default:
                cout << FormatError("Invalid choice. Please try again") << endl;
                Pause();
            }
        }
    }

    void DatabaseScreen()
    {
        // Option to view all courses
        // Option to view all students
        // Option to view all student trackers (Displaying students within the course [Enrolled, Waitlist, Priority Queue])

        int choice;
        while (true)
        {
            system("cls");

            cout << "\tDatabase Screen" << endl;
            cout << "1. View All Courses" << endl;
            cout << "2. View All Students" << endl;
            cout << "3. View All Students in a Course" << endl;
            cout << "4. Go Back" << endl;
            cout << "Enter your choice: ";
            choice = GetValidInteger("Enter your choice: ");

            switch (choice)
            {
            case 1:
                cout << endl;
                cout << "Courses:" << endl;
                for (int i = 0; i < courseList.Size(); i++)
                {
                    Course course = courseList.GetNode(i)->GetData();
                    course.Display();
                    cout << endl;
                }
                Pause();
                break;

            case 2:
                cout << endl;
                cout << "Students:" << endl;
                for (int i = 0; i < studentList.Size(); i++)
                {
                    Student student = studentList.GetNode(i)->GetData();
                    student.Display();
                    cout << endl;
                }
                Pause();
                break;

            case 3:
            {
                // Display all courses and ask for course code
                cout << endl;
                cout << "Courses:" << endl;
                for (int i = 0; i < courseList.Size(); i++)
                {
                    Course course = courseList.GetNode(i)->GetData();
                    cout << "Course Code " << course.GetCode() << ": " << course.GetTitle() << endl;
                }
                cout << endl;

                cout << "Enter the course code of the course you would like to view students for: ";
                string code;
                cin >> code;

                Course course = FindCourse(code);
                if (course.GetCode() == "")
                {
                    cout << FormatError("Course not found.") << endl;
                }
                else
                {
                    StudentTracker tracker = FindStudentTracker(course);
                    cout << endl;
                    cout << "Enrolled Students (" << tracker.GetEnrolledStudents().Size() << "): " << endl;
                    for (int i = 0; i < tracker.GetEnrolledStudents().Size(); i++)
                    {
                        Student student = tracker.GetEnrolledStudents().GetNode(i)->GetData();
                        cout << "ID " << student.GetId() << ": " << student.GetName() << endl;
                    }

                    cout << endl;
                    cout << "Priority Queue (" << tracker.GetPriorityQueue().size() << "):" << endl;
                    if (tracker.GetPriorityQueue().empty())
                    {
                        cout << "No students in priority queue" << endl;
                    }
                    else
                    {
                        for (int i = 0; i < tracker.GetPriorityQueue().size(); i++)
                        {
                            Student student = tracker.GetPriorityQueue().front();
                            cout << "ID " << student.GetId() << ": " << student.GetName() << endl;
                            tracker.GetPriorityQueue().pop();
                            tracker.GetPriorityQueue().push(student);
                            cout << endl;
                        }
                    }

                    cout << endl;
                    cout << "Waitlist (" << tracker.GetWaitlist().size() << "):" << endl;
                    if (tracker.GetWaitlist().empty())
                    {
                        cout << "No students in waitlist" << endl;
                    }
                    else
                    {
                        for (int i = 0; i < tracker.GetWaitlist().size(); i++)
                        {
                            Student student = tracker.GetWaitlist().front();
                            cout << "ID " << student.GetId() << ": " << student.GetName() << endl;
                            tracker.GetWaitlist().pop();
                            tracker.GetWaitlist().push(student);
                            cout << endl;
                        }
                    }
                }

                Pause();
                break;
            }

            case 4:
                // go back
                return;

            default:
                cout << FormatError("Invalid choice. Please try again") << endl;
                Pause();
            }
        }
    }

    void AdminScreen()
    {
        // Display the admin screen with options
        // Option to add, remove or modify courses (new screen)
        // Option to add, remove or modify students (new screen)
        // Option to view all courses (and students in those courses or in the queue or waitlist for other courses)
        // And students

        int choice;
        while (true)
        {
            system("cls");

            cout << "\tWelcome to the Admin Panel!" << endl;
            cout << "1. View Student Management" << endl;
            cout << "2. View Course Management" << endl;
            cout << "3. View Database" << endl;
            cout << "4. Go Back" << endl;
            cout << "Enter your choice: ";
            choice = GetValidInteger("Enter your choice: ");

            switch (choice)
            {
            case 1:
                StudentManagementScreen();
                break;
            case 2:
                CourseManagementScreen();
                break;
            case 3:
                DatabaseScreen();
                break;
            case 4:
                return;
            default:
                cout << FormatError("Invalid choice. Please try again") << endl;
                Pause();
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
            choice = GetValidInteger("Enter your choice: ");
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
                    AdminScreen();
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
