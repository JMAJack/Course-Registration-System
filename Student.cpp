#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student {
private:
    string id;
    string name;
    vector<string> enrolledCourses;

public:
    Student(string studentId, string studentName) {
        id = studentId;
        name = studentName;
    }

    string GetId() {
        return id;
    }

    string GetName() {
        return name;
    }

    vector<string> GetEnrolledCourses() {
        return enrolledCourses;
    }

    void EnrollCourse(string courseCode) {
        enrolledCourses.push_back(courseCode);
    }

    void DropCourse(string courseCode) {
        enrolledCourses.erase(remove(enrolledCourses.begin(), enrolledCourses.end(), courseCode), enrolledCourses.end());
    }

    string ToString() {
        string result = "Student{id='" + id + "', name='" + name + "', enrolledCourses=[";
        for (const auto& course : enrolledCourses) {
            result += course + ", ";
        }
        result += "]}";
        return result;
    }
};
