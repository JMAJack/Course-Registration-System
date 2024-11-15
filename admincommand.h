#include <iostream>
#include <vector>
#include "Course.h"

using namespace std;


void DisplayAllCourses(const vector<Course>& courses) {
    cout << "Available Courses for Registration:" << endl;
    for (const auto& course : courses) {
        cout << "Course Code: " << course.GetCourseCode() << ", Title: " << course.GetTitle()
             << ", Credits: " << course.GetCredits() << ", Max Capacity: " << course.GetMaxCapacity() << endl;
    }
}


void DisplayStudentsInCourse(const vector<Course>& courses, const string& courseCode, bool isAdmin) {
    if (!isAdmin) {
        cout << "Access denied. Only admins can view registered students." << endl;
        return;
    }

    bool courseFound = false;
    for (const auto& course : courses) {
        if (course.GetCourseCode() == courseCode) {
            cout << "Students enrolled in " << course.GetTitle() << ":" << endl;
            course.DisplayEnrolledStudents();
            courseFound = true;
            break;
        }
    }
    if (!courseFound) {
        cout << "Course with code " << courseCode << " not found." << endl;
    }
}


void DisplayFullCourseWaitlists(const vector<Course>& courses, bool isAdmin) {
    if (!isAdmin) {
        cout << "Access denied. Only admins can view waitlists for full courses." << endl;
        return;
    }

    cout << "Waitlists for Full Courses:" << endl;
    for (const auto& course : courses) {
        if (course.GetMaxCapacity() == course.GetMaxCapacity()) {  
         
            cout << "Course Code: " << course.GetCourseCode() << ", Title: " << course.GetTitle() << endl;
            course.DisplayWaitlist();
        }
    }
}

//menu section


void AddCourse(vector<Course>& courses);
void RemoveCourse(vector<Course>& courses);
void ModifyCourse(vector<Course>& courses);
void DisplayAllCourses(const vector<Course>& courses);
void DisplayStudentsInCourse(const vector<Course>& courses);
void DisplayFullCourseWaitlists(const vector<Course>& courses);

void AdminMenu(vector<Course>& courses) {
    int choice;

    do {
        cout << "\n Admin Menu \n";
        cout << "1. Add Course\n";
        cout << "2. Remove Course\n";
        cout << "3. Modify Course\n";
        cout << "4. Display All Courses\n";
        cout << "5. Display Students in a Specific Course\n";
        cout << "6. Display Waitlists for Full Courses\n";
        cout << "7. Exit Admin Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                AddCourse(courses);
                break;
            case 2:
                RemoveCourse(courses);
                break;
            case 3:
                ModifyCourse(courses);
                break;
            case 4:
                DisplayAllCourses(courses);
                break;
            case 5:
                DisplayStudentsInCourse(courses);
                break;
            case 6:
                DisplayFullCourseWaitlists(courses);
                break;
            case 7:
                cout << "Exiting Admin Menu.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);
}


void AddCourse(vector<Course>& courses) {
    string courseCode, title;
    int credits, maxCapacity;
    cout << "Enter course code: ";
    cin >> courseCode;
    cout << "Enter title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter credits: ";
    cin >> credits;
    cout << "Enter maximum capacity: ";
    cin >> maxCapacity;
    courses.emplace_back(courseCode, title, credits, maxCapacity);
    cout << "Course added successfully.\n";
}

void RemoveCourse(vector<Course>& courses) {
    string courseCode;
    cout << "Enter course code to remove: ";
    cin >> courseCode;

    auto it = remove_if(courses.begin(), courses.end(), [&](const Course& course) {
        return course.GetCourseCode() == courseCode;
    });

    if (it != courses.end()) {
        courses.erase(it, courses.end());
        cout << "Course removed successfully.\n";
    } else {
        cout << "Course not found.\n";
    }
}

void ModifyCourse(vector<Course>& courses) {
    string courseCode;
    cout << "Enter course code to modify: ";
    cin >> courseCode;

    for (auto& course : courses) {
        if (course.GetCourseCode() == courseCode) {
            string title;
            int credits, maxCapacity;
            cout << "Enter new title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter new credits: ";
            cin >> credits;
            cout << "Enter new maximum capacity: ";
            cin >> maxCapacity;

            course.SetTitle(title);
            course.SetCredits(credits);
            course.SetMaxCapacity(maxCapacity);
            cout << "Course modified successfully.\n";
            return;
        }
    }

    cout << "Course not found.\n";
}

void DisplayAllCourses(const vector<Course>& courses) {
    cout << "Available Courses for Registration:\n";
    for (const auto& course : courses) {
        cout << "Course Code: " << course.GetCourseCode() << ", Title: " << course.GetTitle()
             << ", Credits: " << course.GetCredits() << ", Max Capacity: " << course.GetMaxCapacity() << endl;
    }
}

void DisplayStudentsInCourse(const vector<Course>& courses) {
    string courseCode;
    cout << "Enter course code: ";
    cin >> courseCode;

    for (const auto& course : courses) {
        if (course.GetCourseCode() == courseCode) {
            course.DisplayEnrolledStudents();
            return;
        }
    }

    cout << "Course not found.\n";
}

void DisplayFullCourseWaitlists(const vector<Course>& courses) {
    for (const auto& course : courses) {
        if (course.GetMaxCapacity() == course.GetMaxCapacity()) {
            cout << "Course Code: " << course.GetCourseCode() << ", Title: " << course.GetTitle() << endl;
            course.DisplayWaitlist();
        }
    }
}
