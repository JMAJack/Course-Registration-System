import java.util.ArrayList;
import java.util.List;

public class Student {
    private String id;
    private String name;
    private List<String> enrolledCourses;

    public Student(String id, String name) {
        this.id = id;
        this.name = name;
        this.enrolledCourses = new ArrayList<>();
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public List<String> getEnrolledCourses() {
        return enrolledCourses;
    }

    public void enrollCourse(String courseCode) {
        enrolledCourses.add(courseCode);
    }

    public void dropCourse(String courseCode) {
        enrolledCourses.remove(courseCode);
    }

    @Override
    public String toString() {
        return "Student{" +
                "id='" + id + '\'' +
                ", name='" + name + '\'' +
                ", enrolledCourses=" + enrolledCourses +
                '}';
    }
}
