#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student {
public:
    string id;
    string name;
    vector<string> enrolledCourses;

    Student(string studentId, string studentName) {
        id = studentId;
        name = studentName;
    }

    void EnrollCourse(string courseCode) {
        enrolledCourses.push_back(courseCode);
    }

    void ViewInfo() {
        cout << "Student ID: " << id << ", Name: " << name << endl;
    }

    vector<string> GetEnrolledCourses() {
        return enrolledCourses;
    }
};

class Admin {
public:
    string adminId;
    string name;

    Admin(string id, string adminName) {
        adminId = id;
        name = adminName;
    }

    void UpdateCourseCapacities(int courseID, int newCapacity) {
        // Code to update course capacity
        cout << "[DEBUG] Updating capacity for course: " << courseID << " to " << newCapacity << endl;
    }
};

vector<Student> students;
vector<Admin> admins;

Student* FindStudentById(string id) {
    for (auto& student : students) {
        if (student.id == id) {
            return &student;
        }
    }
    return nullptr;
}

Admin* FindAdminById(string id) {
    for (auto& admin : admins) {
        if (admin.adminId == id) {
            return &admin;
        }
    }
    return nullptr;
}

void StudentLogin() {
    string studentId;
    cout << "Enter Student ID: ";
    cin >> studentId;

    Student* student = FindStudentById(studentId);
    if (student != nullptr) {
        cout << "Welcome, " << student->name << endl;
        student->ViewInfo(); // Display student info
        // Add code for student menu here
    } else {
        cout << "Invalid Student ID. Please try again." << endl;
    }
}

void AdminLogin() {
    string adminId;
    cout << "Enter Admin ID: ";
    cin >> adminId;

    Admin* admin = FindAdminById(adminId);
    if (admin != nullptr) {
        cout << "Welcome, Admin " << admin->name << endl;
        // Add code for admin menu here
    } else {
        cout << "Invalid Admin ID. Please try again." << endl;
    }
}

int main() {
    // Adding some dummy data
    students.push_back(Student("12345", "John Doe"));
    students.push_back(Student("67890", "Jane Smith"));
    admins.push_back(Admin("admin", "Admin User"));

    while (true) {
        cout << "\n--- Course Registration System ---" << endl;
        cout << "\t1. Student Login" << endl;
        cout << "\t2. Admin Login" << endl;
        cout << "\t3. Exit" << endl;
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                StudentLogin();
                break;
            case 2:
                AdminLogin();
                break;
            case 3:
                cout << "\n\t***Exiting the system. Goodbye!***\n" << endl;
                return 0;
            default:
                cout << "\nInvalid choice. Please enter 1, 2, or 3." << endl;
        }
    }
}
