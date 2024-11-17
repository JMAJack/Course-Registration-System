#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include "Course.h"
#include "Student.h"
#include "StudentTracker.h"
#include "LinkedList.h"

using namespace std;

class FileManager {
public:
    FileManager() {
        //Checks if files exist, if not creates them
        ifstream studentFile("students.dat");
        if (!studentFile.good()) {
            ofstream studentFile("students.dat");
            cout << "Student file created." << endl;
            studentFile.close();
        }

        ifstream courseFile("courses.dat");
        if (!courseFile.good()) {
            ofstream courseFile("courses.dat");
            cout << "Course file created." << endl;
            courseFile.close();
        }

        ifstream studentTrackerFile("student_trackers.dat");
        if (!studentTrackerFile.good()) {
            ofstream studentTrackerFile("student_trackers.dat");
            cout << "StudentTracker file created." << endl;
            studentTrackerFile.close();
        }
    }


    // Save Students to a binary file
    static void SaveStudents(const LinkedList<Student>& studentList, const string& filename) {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            Node<Student>* curr = studentList.GetHead();
            while (curr != nullptr) {
                curr->GetData().Serialize(outFile);
                curr = curr->GetNext();
            }
            outFile.close();
            cout << "Students saved to " << filename << " in binary format." << endl;
        } else {
            cerr << "Error opening file for saving students." << endl;
        }
    }

    // Load Students from a binary file
    static LinkedList<Student> LoadStudents(const string& filename) {
        LinkedList<Student> studentList;
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            while (inFile.peek() != EOF) {
                Student student;
                student.Deserialize(inFile);
                studentList.Insert(student);
            }
            inFile.close();
            cout << "Students loaded from " << filename << " in binary format." << endl;
        } else {
            cerr << "Error opening file for loading students." << endl;
        }
        return studentList;
    }

    // Save Courses to a binary file
    static void SaveCourses(const LinkedList<Course>& courseList, const string& filename) {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            Node<Course>* curr = courseList.GetHead();
            while (curr != nullptr) {
                curr->GetData().Serialize(outFile);
                curr = curr->GetNext();
            }
            outFile.close();
            cout << "Courses saved to " << filename << " in binary format." << endl;
        } else {
            cerr << "Error opening file for saving courses." << endl;
        }
    }

    // Load Courses from a binary file
    static LinkedList<Course> LoadCourses(const string& filename) {
        LinkedList<Course> courseList;
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            while (inFile.peek() != EOF) {
                Course course;
                course.Deserialize(inFile);
                courseList.Insert(course);
            }
            inFile.close();
            cout << "Courses loaded from " << filename << " in binary format." << endl;
        } else {
            cerr << "Error opening file for loading courses." << endl;
        }
        return courseList;
    }

    // Save StudentTrackers to a binary file
    static void SaveStudentTrackers(const LinkedList<StudentTracker>& trackerList, const string& filename) {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            Node<StudentTracker>* curr = trackerList.GetHead();
            while (curr != nullptr) {
                curr->GetData().Serialize(outFile);
                curr = curr->GetNext();
            }
            outFile.close();
            cout << "StudentTrackers saved to " << filename << " in binary format." << endl;
        } else {
            cerr << "Error opening file for saving StudentTrackers." << endl;
        }
    }

    // Load StudentTrackers from a binary file
    static LinkedList<StudentTracker> LoadStudentTrackers(const string& filename) {
        LinkedList<StudentTracker> trackerList;
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            while (inFile.peek() != EOF) {
                StudentTracker tracker;
                tracker.Deserialize(inFile);
                trackerList.Insert(tracker);
            }
            inFile.close();
            cout << "StudentTrackers loaded from " << filename << " in binary format." << endl;
        } else {
            cerr << "Error opening file for loading StudentTrackers." << endl;
        }
        return trackerList;
    }
};

#endif // FILEMANAGER_H