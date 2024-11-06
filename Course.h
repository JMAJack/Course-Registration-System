#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <queue>
#include <fstream>

using namespace std;


class Course {
private:
    string code;
    string title;
    int credits;
    int maxCapacity;
    Course* prerequisites[2];

public:
    // Default constructor
    Course() : code(""), title(""), credits(0), maxCapacity(0) {
        prerequisites[0] = nullptr;
        prerequisites[1] = nullptr;
    }

    // Primary constructor
    Course(string Code, string Title, int Credits, int MaxCapacity, Course* Prerequisites[2])
        : code(Code), title(Title), credits(Credits), maxCapacity(MaxCapacity) {
        prerequisites[0] = Prerequisites[0];
        prerequisites[1] = Prerequisites[1];
    }

    // Copy constructor
    Course(const Course& c)
        : code(c.code), title(c.title), credits(c.credits), maxCapacity(c.maxCapacity) {
        prerequisites[0] = c.prerequisites[0];
        prerequisites[1] = c.prerequisites[1];
    }

    // Accessors and mutators
    string GetCode() const { return code; }
    void SetCode(string Code) { code = Code; }

    string GetTitle() const { return title; }
    void SetTitle(string newTitle) { title = newTitle; }

    int GetCredits() const { return credits; }
    void SetCredits(int newCredits) { credits = newCredits; }

    int GetMaxCapacity() const { return maxCapacity; }
    void SetMaxCapacity(int capacity) { maxCapacity = capacity; }

    Course* GetPrerequisites(int index) const { return prerequisites[index]; }
    void SetPrerequisites(int index, Course* prereq) { prerequisites[index] = prereq; }

    // Display course details
    void Display() const {
        cout << "Course Code: " << code << endl;
        cout << "Title: " << title << endl;
        cout << "Credits: " << credits << endl;
        cout << "Max Capacity: " << maxCapacity << endl;
        cout << "Prerequisites: ";
        for (int i = 0; i < 2; ++i) {
            if (prerequisites[i] != nullptr) {
                cout << prerequisites[i]->GetCode() << " ";
            }
        }
        cout << endl;
    }

    bool operator==(const Course& c) const {
        return code == c.code;
    }

    // Serialize the course data to a binary file
    void Serialize(ofstream& outFile) const {
        size_t codeLength = code.size();
        outFile.write(reinterpret_cast<const char*>(&codeLength), sizeof(codeLength));
        outFile.write(code.c_str(), codeLength);

        size_t titleLength = title.size();
        outFile.write(reinterpret_cast<const char*>(&titleLength), sizeof(titleLength));
        outFile.write(title.c_str(), titleLength);

        outFile.write(reinterpret_cast<const char*>(&credits), sizeof(credits));
        outFile.write(reinterpret_cast<const char*>(&maxCapacity), sizeof(maxCapacity));

        // Serialize prerequisites
        for (int i = 0; i < 2; ++i) {
            bool hasPrerequisite = (prerequisites[i] != nullptr);
            outFile.write(reinterpret_cast<const char*>(&hasPrerequisite), sizeof(hasPrerequisite));
            if (hasPrerequisite) {
                prerequisites[i]->Serialize(outFile);
            }
        }
    }

    // Deserialize the course data from a binary file
    void Deserialize(ifstream& inFile) {
        size_t codeLength;
        inFile.read(reinterpret_cast<char*>(&codeLength), sizeof(codeLength));
        code.resize(codeLength);
        inFile.read(&code[0], codeLength);

        size_t titleLength;
        inFile.read(reinterpret_cast<char*>(&titleLength), sizeof(titleLength));
        title.resize(titleLength);
        inFile.read(&title[0], titleLength);

        inFile.read(reinterpret_cast<char*>(&credits), sizeof(credits));
        inFile.read(reinterpret_cast<char*>(&maxCapacity), sizeof(maxCapacity));

        // Deserialize prerequisites
        for (int i = 0; i < 2; ++i) {
            bool hasPrerequisite;
            inFile.read(reinterpret_cast<char*>(&hasPrerequisite), sizeof(hasPrerequisite));
            if (hasPrerequisite) {
                prerequisites[i] = new Course();
                prerequisites[i]->Deserialize(inFile);
            } else {
                prerequisites[i] = nullptr;
            }
        }
    }
};

#endif // COURSE_H