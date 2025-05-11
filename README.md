# Course Registration System
This repository contains a group project for a CLI Course Management application for a Data Structures module in 2025.

[Project Description and Rules](https://github.com/JMAJack/Course-Registration-System/blob/main/Data%20Structures%20sem1_2024-25%20Project.pdf)

[User Manual](https://github.com/JMAJack/Course-Registration-System/blob/main/Course%20Registration%20System%20User%20Manual.pdf)

[Application and Source Code Download](https://github.com/JMAJack/Course-Registration-System/releases/tag/v1.0.0) 

## Table of Contents
- [Introduction](#introduction) 
- [Traversing between Menu and Information Screens](#traversing-between-menu-and-information-screens) 
- [Startup Process](#startup-process)
- [Logging in](#logging-in)
- [Student Menu](#student-menu)
  - [Course Enrollment](#course-enrollment)
  - [Course Removal](#course-removal)
  - [View Student Data](#view-student-data)
- [Admin Menu](#admin-menu)
  - [Student Management](#student-management)
  - [Course Management](#course-management)
  - [Database](#database)
- [Logging Out](#logging-out)
- [Exiting the Program](#exiting-the-program)

## Introduction
The Course Registration System is designed to assist students and administrators in course enrollment and management. This manual should provide a detailed guide on how to use each system function, ensuring that even new users can easily navigate the application.

To run the software, open the “CourseRegistrationSystem.exe” which will open a terminal/command prompt on your computer to interact with the application. Any new information entered within the database will be immediately updated and available. There are three encrypted files which are type `dat`, the first file is the “students.dat” which contains the student’s ID, name, GPA, priority status, and list of enrolled courses. The second file is the “courses.dat” which contains the course’s code, title, credits, max capacity, and prerequisites. The third file is the “student_trackers.dat” which contains a course and its enrolled students, waitlist, and priority queue.

## Traversing between Menu and Information Screens
Each menu contains options associated with a number command that needs to be entered to access it. In addition, each menu or information screen will first clear all text on the terminal before displaying, thus you will be asked to “Press Enter to Continue...” on the terminal, allowing the user to move on to the next or previous screen depending on the menu. Please note that if you press enter and the next screen does not appear, then press enter again.

## Startup Process
If all files are present, then they will be loaded into the program. However, if the program opens and the `students.dat`, `courses.dat`, and/or `student_trackers.dat` are not located in the same directory as the application, then the program will automatically create and load the file/s that are absent into the program.

## Logging in
The Login Menu is shown after pressing enter when the program boots up. The log-in menu contains the following options:

1. **Login as Student**:  
   Allows the student to enter their ID to access the “Student Menu”. If the user enters their student ID, and a “not found error” is shown, then the student must consult an admin to create or modify their student record.

2. **Login as Admin**:  
   Allows the admin to enter their ID, which is “admin123”, to access the “Admin Menu”.

3. **Exit**:  
   This option ends the program. Please note that it is recommended to use this option to end the program rather than pressing the “X” button on the top right corner of the window. This is because the Exit button is responsible for saving all the memory (addition, deletion, and modification of students, courses, and/or student tracker records) from the application to their respective files once selected.

## Student Menu
Once logged in as a student, the user will have access to the Student Menu which contains the following options:

### Course Enrollment
The Course Enrollment menu has the number 1 command on the Student Menu. This menu allows students to choose or undo a course they want to enroll in. The options for this menu are:

1. **Enroll in a course**:  
   This option allows the student to enroll in a course by entering the course’s code from the list of available courses displayed on the screen. When enrolling, a user may be placed in the priority queue or waitlist automatically depending on the course size and the priority of the student. Users should ensure they have the appropriate prerequisites as listed by the course before enrolling, if not then an error will be shown.

2. **Undo last enrollment**:  
   This option removes the last course the student has enrolled in during the current session. Once completed, it moves on to the next latest enrollment.  
   If the student was enrolled in the course they removed, then the first person in the priority queue will be enrolled into the course. If the priority queue is empty, then the first person in the waitlist will be enrolled into the course.  
   Even though an error will be shown if the course the user was attempting to undo was dropped beforehand, the undo will still move on to the next latest enrollment.

### Course Removal
The Course Removal menu has the number 2 command on the Student Menu. This menu allows students to choose or undo a course they want to be removed from. The options for this menu are:

1. **Drop a course**:  
   This option allows the student to be removed from a course they were enrolled in or placed in its waitlist or priority queue. This is done by entering the course’s code from the list of enrolled, waitlisted, or priority-queued courses displayed on the screen.  
   If the student was enrolled in the course they removed, then the first person in the priority queue will be enrolled into the course. If the priority queue is empty, then the first person in the waitlist will be enrolled into the course.

2. **Undo last drop**:  
   This option enrolls the student into the last course they dropped during the current session. Once completed, it moves on to the next latest removal.  
   Even though an error will be shown if the course the user was attempting to undo was enrolled back into beforehand, the undo will still move on to the next latest removal.

### View Student Data
The View Student Data screen has the number 3 command on the Student Menu. This option allows students to view their details: ID, name, GPA, priority status, and the details of their enrolled courses and/or courses in the waitlist or priority queue: code, title, credits, max capacity, and prerequisites.

## Admin Menu
Once logged in as an admin, they will have access to the Admin Menu which contains the following options:

### Student Management
The Student Management menu has the number 1 command on the Admin Menu. This menu allows an admin to add, remove, or modify a student record. The options for this menu are:

1. **Add Student**:  
   This option allows an admin to create a new student record by entering the new ID, name, and GPA.

2. **Remove Student**:  
   This option allows an admin to remove a student record from the system by entering the student’s ID from the list of students displayed on the screen.

3. **Modify Student**:  
   This option allows an admin to change a student record’s ID, name, and GPA by entering the ID of the student selected to be modified from the list of students displayed on the screen. To keep certain data the same, enter the current data within their respective fields.

### Course Management
The Course Management menu has the number 2 command on the Admin Menu. This menu allows an admin to add, remove, or modify a course record. The options for this menu are:

1. **Add Course**:  
   This option allows an admin to create a new course record by entering the new code, title, credits, max capacity, and prerequisites by entering the codes of those courses. To add only one prerequisite, enter the first course code when prompted, then type and enter “None” for the second course code when prompted. To add no prerequisites, only type and enter “None” for the first course code when prompted.

2. **Remove Course**:  
   This option allows an admin to remove a course record from the system by entering the course’s code from the list of courses displayed on the screen.

3. **Modify Course**:  
   This option allows an admin to change a student course’s code, title, credits, max capacity, and prerequisites by entering the course code selected to be modified from the list of students displayed on the screen. To keep certain data the same, enter the current data within their respective fields. To change only one prerequisite, enter the current course code of the prerequisite to be kept when prompted, then type and enter “None” for the second course code when prompted. To change it so that the course has no prerequisites, only type and enter “None” for the first course code when prompted.

### Database
The Database menu has the number 3 command on the Admin Menu. This menu allows an admin to view all courses, students, and students in a specific course. The options for this menu are:

1. **View All Courses**:  
   This option allows an admin to view the total number of course records and each record’s details: code, title, credits, max capacity, and prerequisites.

2. **View All Students**:  
   This option allows an admin to view the total number of student records and each record’s details: ID, name, GPA, and priority status.

3. **View All Students in a Course**:  
   This option allows an admin to view the total number of student records and each record’s ID and name for each category: enrolled students, priority queue students, and waitlist students, in a specified course. This is done by entering the course’s code from the list of courses displayed on the screen.

## Logging Out
The user can log out by entering the number command for “Go back”, until they reach the Login Menu.

## Exiting the Program
The user can exit the program by going to the Login Menu and entering the number command for “Exit”, which is 3. It is not recommended to close the window to end the program by clicking the “X” button on the top right corner of the window. This is because the Exit button is responsible for saving all the memory (addition, deletion, and modification of students, courses, and/or student tracker records) from the application to their respective files once selected.
