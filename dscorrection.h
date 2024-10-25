class Course {
private:
    string courseCode;
    string title;
    int credits;
    int maxCapacity;
    list<Student> enrolledStudents;     
    queue<Student> waitlist;           
    queue<Student> priorityQueue;       

public:
    
    Course() : courseCode(""), title(""), credits(0), maxCapacity(0) {}

    
    Course(string courseCode, string title, int credits, int maxCapacity) 
        : courseCode(courseCode), title(title), credits(credits), maxCapacity(maxCapacity) {}

    
    Course(const Course& other)
        : courseCode(other.courseCode), title(other.title), credits(other.credits), maxCapacity(other.maxCapacity),
          enrolledStudents(other.enrolledStudents), waitlist(other.waitlist), priorityQueue(other.priorityQueue) {}

    
    string GetCourseCode() const { return courseCode; }
    void SetCourseCode(const string& code) { courseCode = code; }

    string GetTitle() const { return title; }
    void SetTitle(const string& newTitle) { title = newTitle; }

    int GetCredits() const { return credits; }
    void SetCredits(int newCredits) { credits = newCredits; }

    int GetMaxCapacity() const { return maxCapacity; }
    void SetMaxCapacity(int capacity) { maxCapacity = capacity; }

    
    void AddStudent(Student student, bool isPriority) {
        if (enrolledStudents.size() < maxCapacity) {
            enrolledStudents.push_back(student);
            cout << "Student " << student.GetName() << " enrolled in " << title << endl;
        } else {
            if (isPriority) {
                priorityQueue.push(student);
                cout << "Student " << student.GetName() << " added to priority queue for " << title << endl;
            } else {
                waitlist.push(student);
                cout << "Student " << student.GetName() << " added to waitlist for " << title << endl;
            }
        }
    }

    void RemoveStudent(Student student) {
        enrolledStudents.remove(student);
        cout << "Student " << student.GetName() << " removed from " << title << endl;

        
        if (!priorityQueue.empty()) {
            Student nextPriorityStudent = priorityQueue.front();
            priorityQueue.pop();
            AddStudent(nextPriorityStudent, true);  
        } else if (!waitlist.empty()) {
            Student nextWaitlistStudent = waitlist.front();
            waitlist.pop();
            AddStudent(nextWaitlistStudent, false); 
        }
    }

    void DisplayEnrolledStudents() const {
        cout << "Students enrolled in " << title << ":" << endl;
        for (const auto& student : enrolledStudents) {
            cout << student.GetName() << endl;
        }
    }

    void DisplayWaitlist() const {
        cout << "Waitlist for " << title << ":" << endl;
        queue<Student> tempWaitlist = waitlist;
        while (!tempWaitlist.empty()) {
            cout << tempWaitlist.front().GetName() << endl;
            tempWaitlist.pop();
        }
    }

    void DisplayPriorityQueue() const {
        cout << "Priority queue for " << title << ":" << endl;
        queue<Student> tempPriorityQueue = priorityQueue;
        while (!tempPriorityQueue.empty()) {
            cout << tempPriorityQueue.front().GetName() << endl;
            tempPriorityQueue.pop();
        }
    }
};