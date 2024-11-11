{\rtf1\ansi\ansicpg1252\cocoartf2818
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <iostream>\
#include <vector>\
#include "Course.h"\
\
using namespace std;\
\
\
void DisplayAllCourses(const vector<Course>& courses) \{\
    cout << "Available Courses for Registration:" << endl;\
    for (const auto& course : courses) \{\
        cout << "Course Code: " << course.GetCourseCode() << ", Title: " << course.GetTitle()\
             << ", Credits: " << course.GetCredits() << ", Max Capacity: " << course.GetMaxCapacity() << endl;\
    \}\
\}\
\
\
void DisplayStudentsInCourse(const vector<Course>& courses, const string& courseCode, bool isAdmin) \{\
    if (!isAdmin) \{\
        cout << "Access denied. Only admins can view registered students." << endl;\
        return;\
    \}\
\
    bool courseFound = false;\
    for (const auto& course : courses) \{\
        if (course.GetCourseCode() == courseCode) \{\
            cout << "Students enrolled in " << course.GetTitle() << ":" << endl;\
            course.DisplayEnrolledStudents();\
            courseFound = true;\
            break;\
        \}\
    \}\
    if (!courseFound) \{\
        cout << "Course with code " << courseCode << " not found." << endl;\
    \}\
\}\
\
\
void DisplayFullCourseWaitlists(const vector<Course>& courses, bool isAdmin) \{\
    if (!isAdmin) \{\
        cout << "Access denied. Only admins can view waitlists for full courses." << endl;\
        return;\
    \}\
\
    cout << "Waitlists for Full Courses:" << endl;\
    for (const auto& course : courses) \{\
        if (course.GetMaxCapacity() == course.GetMaxCapacity()) \{  \
         \
            cout << "Course Code: " << course.GetCourseCode() << ", Title: " << course.GetTitle() << endl;\
            course.DisplayWaitlist();\
        \}\
    \}\
\}\
}