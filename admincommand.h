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

#include <iostream>
#include <vector>
#include "Course.h"

using namespace std;


void AddCourse(vector<Course>& courses);
void RemoveCourse(vector<Course>& courses);
void ModifyCourse(vector<Course>& courses);
void DisplayAllCourses(const vector<Course>& courses);
void DisplayStudentsInCourse(const vector<Course>& courses);
void DisplayFullCourseWaitlists(const vector<Course>& courses);
void AddStudentToCourse(vector<Course>& courses);
void RemoveStudentFromCourse(vector<Course>& courses);
void DisplayPriorityList(const vector<Course>& courses);

void AdminMenu(vector<Course>& courses) {
    int choice;

    do {
        cout << "\n Admin Menu \n";
        cout << "1. Add Course\n";
        cout << "2. Remove Course\n";
        cout << "3. Modify Course\n";
        cout << "4. Display All Courses\n";
        cout << "5. Add Student to a Course\n";
        cout << "6. Remove Student from a Course\n";
        
        cout << "7. Display Students in a Specific Course\n";
        cout << "8. Edit Student Data\n";
        cout << "9. Display Waitlists for Full Courses\n";
        cout << "10. Display Priority List for a Course\n";
        cout << "11. Exit Admin Menu\n";
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
                AddStudentToCourse(courses);
                break;
            case 6:    
                RemoveStudentFromCourse(courses);
                break;
            case 7:    
                DisplayStudentsInCourse(courses);
                break;
            case 8:
                EditStudentInCourse(courses);
                break;
            case 9:    
                DisplayFullCourseWaitlists(courses);
                break;
            case 10:
                DisplayPriorityList(courses);
                break;
            case 11:
                cout << "Exiting Admin Menu.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 11);
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

void AddStudentToCourse(vector<Course>& courses) {
    string courseCode, studentName, studentID;
    bool isPriority;

    cout << "Enter course code: ";
    cin >> courseCode;

    for (auto& course : courses) {
        if (course.GetCourseCode() == courseCode) {
            cout << "Enter student ID: ";
            cin >> studentID;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, studentName);

            cout << "Is this a priority student? (1 for Yes, 0 for No): ";
            cin >> isPriority;

            Student newStudent(studentID, studentName);
            course.AddStudent(newStudent, isPriority);

            cout << "Student " << studentName << " added to the course " << course.GetTitle() << ".\n";
            return;
        }
    }

    cout << "Course with code " << courseCode << " not found.\n";
}

void RemoveStudentFromCourse(vector<Course>& courses) {
    string courseCode, studentID;

    cout << "Enter course code: ";
    cin >> courseCode;

    for (auto& course : courses) {
        if (course.GetCourseCode() == courseCode) {
            cout << "Enter student ID to remove: ";
            cin >> studentID;

            
            Student studentToRemove(studentID, ""); 
            course.RemoveStudent(studentToRemove);

            cout << "Student removed from course " << course.GetTitle() << ".\n";
            return;
        }
    }

    cout << "Course with code " << courseCode << " not found.\n";
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

void EditStudentInCourse(vector<Course>& courses) {
    string courseCode, studentID, newName, newID;
    cout << "Enter course code: ";
    cin >> courseCode;

    
    for (auto& course : courses) {
        if (course.GetCourseCode() == courseCode) {
            cout << "Enter student ID to edit: ";
            cin >> studentID;

            
            for (auto& student : course.GetEnrolledStudents()) { 
                if (student.GetID() == studentID) {
                    
                    cout << "Enter new student ID (or press Enter to skip): ";
                    cin.ignore();
                    getline(cin, newID);

                    cout << "Enter new student name (or press Enter to skip): ";
                    getline(cin, newName);

                    if (!newID.empty()) student.SetID(newID);
                    if (!newName.empty()) student.SetName(newName);

                    cout << "Student data updated successfully.\n";
                    return;
                }
            }

            cout << "Student with ID " << studentID << " not found in the course.\n";
            return;
        }
    }

    cout << "Course with code " << courseCode << " not found.\n";
}


void DisplayFullCourseWaitlists(const vector<Course>& courses) {
    for (const auto& course : courses) {
        if (course.GetMaxCapacity() == course.GetMaxCapacity()) {
            cout << "Course Code: " << course.GetCourseCode() << ", Title: " << course.GetTitle() << endl;
            course.DisplayWaitlist();
        }
    }
}

void DisplayPriorityList(const vector<Course>& courses) {
    string courseCode;

    cout << "Enter course code: ";
    cin >> courseCode;

    for (const auto& course : courses) {
        if (course.GetCourseCode() == courseCode) {
            cout << "Priority list for course " << course.GetTitle() << ":\n";
            course.DisplayPriorityQueue();
            return;
        }
    }

    cout << "Course with code " << courseCode << " not found.\n";
}



