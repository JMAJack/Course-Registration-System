#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include "Course.h"
#include "Student.h"
#include "StudentTracker.h"
#include "LinkedList.h"

using namespace std;

class Course;
class Student;
class StudentTracker;

class FileManager {
public:
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

    // Save Course data to a binary file
    static void SaveCourse(const Course& course, const string& filename) {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            course.Serialize(outFile);
            outFile.close();
            cout << "Course saved to " << filename << " in binary format." << endl;
        } else {
            cerr << "Error opening file for saving course." << endl;
        }
    }

    // Load Course data from a binary file
    static Course LoadCourse(const string& filename) {
        Course course;
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            course.Deserialize(inFile);
            inFile.close();
            cout << "Course loaded from " << filename << " in binary format." << endl;
        } else {
            cerr << "Error opening file for loading course." << endl;
        }
        return course;
    }

    // Save StudentTracker data to a binary file
    static void SaveStudentTracker(const StudentTracker& tracker, const string& filename) {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            tracker.Serialize(outFile);
            outFile.close();
            cout << "StudentTracker saved to " << filename << " in binary format." << endl;
        } else {
            cerr << "Error opening file for saving StudentTracker." << endl;
        }
    }

    // Load StudentTracker data from a binary file
    static StudentTracker LoadStudentTracker(const string& filename) {
        StudentTracker tracker;
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            tracker.Deserialize(inFile);
            inFile.close();
            cout << "StudentTracker loaded from " << filename << " in binary format." << endl;
        } else {
            cerr << "Error opening file for loading StudentTracker." << endl;
        }
        return tracker;
    }
};

#endif // FILEMANAGER_H