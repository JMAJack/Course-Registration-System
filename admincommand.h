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

