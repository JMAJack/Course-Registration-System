import java.util.Scanner;

public class CourseRegistrationSystem {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("\n--- Course Registration System ---");
            System.out.println("\t1. Student Login");
            System.out.println("\t2. Admin Login");
            System.out.println("\t3. Exit");

            System.out.print("Choose an option: ");
            String choice = scanner.nextLine();

            switch (choice) {
                case "1":
                    studentLogin(scanner);
                    break;
                case "2":
                    adminLogin(scanner);
                    break;
                case "3":
                    System.out.println("\n\t***Exiting the system. Goodbye!***\n");
                    scanner.close();
                    System.exit(0);
                default:
                    System.out.println("\nInvalid choice. Please enter 1, 2, or 3.");
            }
        }
    }

    private static void studentLogin(Scanner scanner) {
        System.out.print("Enter Student ID: ");
        String studentId = scanner.nextLine();
        // For debugging
        System.out.println("\n\t[DEBUG] Student ID entered: " + studentId);

        // Implement further student login logic here
        // For now, let's simulate a simple validation
        if (studentId.equals("12345")) {
            System.out.println("\tWelcome, Student " + studentId);
            studentMenu(scanner);
        } else {
            System.out.println("\tInvalid Student ID. Please try again.");
        }
    }

    private static void adminLogin(Scanner scanner) {
        System.out.print("Enter Admin ID: ");
        String adminId = scanner.nextLine();
        // For debugging
        System.out.println("\n\t[DEBUG] Admin ID entered: " + adminId);

        // Implement further admin login logic here
        // For now, let's simulate a simple validation
        if (adminId.equals("admin")) {
            System.out.printf("\n\t*Welcome, Admin %s!\n", adminId);
            adminMenu(scanner);
        } else {
            System.out.println("\n\tInvalid Admin ID. Please try again.");
        }
    }

    private static void studentMenu(Scanner scanner) {
        while (true) {
            System.out.println("\n--- Student Menu ---");
            System.out.println("\t1. View Available Courses");
            System.out.println("\t2. Register for a Course");
            System.out.println("\t3. View Enrolled Courses");
            System.out.println("\t4. Undo Last Registration");
            System.out.println("\t5. Logout");

            System.out.print("Choose an option: ");
            String choice = scanner.nextLine();

            switch (choice) {
                case "1":
                    viewAvailableCourses();
                    break;
                case "2":
                    registerForCourse(scanner);
                    break;
                case "3":
                    viewEnrolledCourses();
                    break;
                case "4":
                    undoLastRegistration();
                    break;
                case "5":
                    System.out.println("Logging out...");
                    return;  // Exit to main menu
                default:
                    System.out.println("Invalid choice. Please enter a number between 1 and 5.");
            }
        }
    }

    private static void adminMenu(Scanner scanner) {
        while (true) {
            System.out.println("\n--- Admin Menu ---");
            System.out.println("\t1. Manage Students");
            System.out.println("\t2. Manage Courses");
            System.out.println("\t3. Generate Reports");
            System.out.println("\t4. Update Course Capacities");
            System.out.println("\t5. Logout");

            System.out.print("Choose an option: ");
            String choice = scanner.nextLine();

            switch (choice) {
                case "1":
                    manageStudents(scanner);
                    break;
                case "2":
                    manageCourses(scanner);
                    break;
                case "3":
                    generateReports();
                    break;
                case "4":
                    updateCourseCapacities(scanner);
                    break;
                case "5":
                    System.out.println("Logging out...");
                    return;  // Exit to main menu
                default:
                    System.out.println("Invalid choice. Please enter a number between 1 and 5.");
            }
        }
    }

    // Placeholder methods for student functionalities
    private static void viewAvailableCourses() {
        System.out.println("[DEBUG] Displaying available courses...");
        // Add logic to display available courses
    }

    private static void registerForCourse(Scanner scanner) {
        System.out.print("Enter Course Code to register: ");
        String courseCode = scanner.nextLine();
        System.out.println("\n\t[DEBUG] Registering for course: " + courseCode);
        // Add logic to register for a course
    }

    private static void viewEnrolledCourses() {
        System.out.println("[DEBUG] Displaying enrolled courses...");
        // Add logic to display enrolled courses
    }

    private static void undoLastRegistration() {
        System.out.println("[DEBUG] Undoing last registration...");
        // Add logic to undo last registration
    }

    // Placeholder methods for admin functionalities
    private static void manageStudents(Scanner scanner) {
        System.out.println("[DEBUG] Managing students...");
        // Add logic to manage students
    }

    private static void manageCourses(Scanner scanner) {
        System.out.println("[DEBUG] Managing courses...");
        // Add logic to manage courses
    }

    private static void generateReports() {
        System.out.println("[DEBUG] Generating reports...");
        // Add logic to generate reports
    }

    private static void updateCourseCapacities(Scanner scanner) {
        System.out.print("\n\tEnter Course Code to update capacity: ");
        String courseCode = scanner.nextLine();
        System.out.print("\tEnter new maximum capacity: ");
        int maxCapacity = scanner.nextInt();
        scanner.nextLine();  // Consume newline
        System.out.println("\n\t[DEBUG] Updating capacity for course: " + courseCode + " to " + maxCapacity);
        // Add logic to update course capacities
    }
}
