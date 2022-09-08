package com.ClientApplication.Client;

import java.sql.Timestamp;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.client.RestTemplate;

@SpringBootApplication
public class ClientApplication implements CommandLineRunner {

	@Autowired
	private ClientService clientService;

	private static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		SpringApplication.run(ClientApplication.class, args);
	}

	@Bean
	public RestTemplate getRestTemplate() {
		return new RestTemplate();
	}

	@Override
	public void run(String... args) throws Exception {

		int option = displayMenu();

		performOperations(option);

		reloadMenu();

	}

	private void performOperations(int option) throws ParseException {
		if (option == 1) {
			createStudent();
		} else if (option == 2) {
			updateStudent();
		} else if (option == 3) {
			createCourse();
		} else if (option == 4) {
			updateCourse();
		} else if (option == 5) {
			addStudentToCourse();
		} else if (option == 6) {
			removeStudentFromCourse();
		} else if (option == 7) {
			getCoursesOfStudent();
		} else if (option == 8) {
			getStudentsOfCourse();
		} else if (option == 9) {
			setStudentGradeForCourse();
		} else if (option == 10) {
			getStudentGrade();
		} else if (option == 11) {
			calculateCourseAverage();
		} else if (option == 12) {
			getStudentGradePointAverage();
		} else if (option == 13) {
			resetDataStore();
		} else if (option == 14) {
			System.out.println("Thank you");
			System.exit(-1);
		}
	}

	private void createStudent() {

		try {
			boolean isSuccess = false;
			System.out.println("Enter Student Id");
			String studentId = sc.next();
			System.out.println("Student name");
			String studentName = sc.next();
			System.out.println("Credit Capacity");
			int creditCapacity = sc.nextInt();
			isSuccess = clientService.createStudent(studentId, studentName, creditCapacity);
			if (isSuccess) {
				System.out.println("Student details are created successfully ");
			} else {
				System.out.println("Creating student details has failed ");
			}

		} catch (InputMismatchException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void createCourse() {

		try {

			System.out.println("Enter Course Id");
			String courseId = sc.next();
			System.out.println("Enter Course name");
			String courseName = sc.next();
			System.out.println("Enter Start Date of Course in yyyy-mm-dd format");
			String startDate = sc.next();
			System.out.println("Enter End date of Course in yyyy-mm-dd format");
			String endDate = sc.next();
			System.out.println("Enter start time of course in hh:mi:ss format");
			String time = sc.next();
			System.out.println("Enter day : Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday");
			String day = sc.next();
			System.out.println("Enter Semester period: Spring, Summer, Fall");
			String semester = sc.next();
			System.out.println("Enter credit");
			int credit = sc.nextInt();
			System.out.println("Enter capacity");
			int capacity = sc.nextInt();

			boolean isSuccess = clientService.createCourse(courseId, courseName, startDate, endDate, time, day,
					semester, credit, capacity);
			if (isSuccess) {
				System.out.println("Course details are created successfully ");
			} else {
				System.out.println("Creating Course details has failed ");
			}
		} catch (InputMismatchException | ParseException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void updateStudent() {

		try {
			System.out.println("Enter student id");
			String studentId = sc.next();
			System.out.println("Enter new Credit Capacity");
			int creditCapacity = sc.nextInt();
			boolean isSuccess = clientService.updateStudent(studentId, creditCapacity);
			if (isSuccess) {
				System.out.println("Student details are updated successfully ");
			} else {
				System.out.println("Updating student details has failed ");
			}

		} catch (InputMismatchException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void updateCourse() {

		try {
			System.out.println("Enter Course Id");
			String courseId = sc.next();
			System.out.println("Enter Start Date of Course in yyyy-mm-dd format");
			String startDate = sc.next();
			System.out.println("Enter End date of Course in yyyy-mm-dd format");
			String endDate = sc.next();
			System.out.println("Enter start time of course in hh:mi:ss format");
			String time = sc.next();
			System.out.println("Enter day : Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday");
			String day = sc.next();
			System.out.println("Enter Semester period: Spring, Summer, Fall");
			String semester = sc.next();
			System.out.println("Enter credit");
			int credit = sc.nextInt();
			System.out.println("Enter capacity");
			int capacity = sc.nextInt();

			boolean isSuccess = clientService.updateCourse(courseId, startDate, endDate, time, day, semester, credit,
					capacity);
			if (isSuccess) {
				System.out.println("Course details are updated successfully ");
			} else {
				System.out.println("Updating Course details has failed ");
			}
		} catch (InputMismatchException | ParseException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void addStudentToCourse() {

		try {

			System.out.println("Enter student id to add Student To Course");
			String studentId = sc.next();
			System.out.println("Enter Course id to add Student To Course");
			String courseId = sc.next();
			boolean isSuccess = clientService.addStudentToCourse(studentId, courseId);
			if (isSuccess) {
				System.out.println("Student details are added successfully to Course ");
			} else {
				System.out.println("Adding student details to Course has failed ");
			}

		} catch (InputMismatchException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void removeStudentFromCourse() {

		try {

			System.out.println("Enter student id to remove Student from a  Course");
			String studentId = sc.next();
			System.out.println("Enter Course id to remove Student from a Course");
			String courseId = sc.next();
			boolean isSuccess = clientService.removeStudentFromCourse(studentId, courseId);
			if (isSuccess) {
				System.out.println("Student details are removed successfully to Course ");
			} else {
				System.out.println("Removing student details to Course has failed ");
			}

		} catch (InputMismatchException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void getCoursesOfStudent() {

		try {
			System.out.println("Enter student id to get courses");

			String studentId = sc.next();

			List<Course> courses = clientService.getCoursesOfStudent(studentId);
			if (courses != null) {
				for (Course course : courses) {
					System.out.println(
							"Course name:" + course.getCourseName() + " and Course id:" + course.getCourseId());
				}
			} else {
				System.out.println("No courses found");
			}

		} catch (InputMismatchException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void setStudentGradeForCourse() {

		try {
			System.out.println("Enter student id to add grade for a  Course");
			String studentId = sc.next();
			System.out.println("Enter Course id to add grade for a  Course");
			String courseId = sc.next();
			System.out.println("Enter grade to add for a student in a  course");

			String grade = sc.next();
			boolean isSuccess = clientService.setStudentGradeForCourse(studentId, courseId, grade);
			if (isSuccess) {
				System.out.println("Student grade are  successfully added to Course ");
			} else {
				System.out.println("Adding Student grade to Course  has failed ");
			}

		} catch (InputMismatchException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void getStudentGrade() {

		try {
			System.out.println("Enter student id to  get Student grade in a course");
			String studentId = sc.next();
			System.out.println("Enter Course id to get Student grade in a course");
			String courseId = sc.next();
			String grade = clientService.getStudentGrade(studentId, courseId);

			System.out.println("Grade is:" + grade);

		} catch (InputMismatchException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void getStudentsOfCourse() {

		try {
			System.out.println("Enter course id to get all students details");

			String courseId = sc.next();

			List<Student> students = clientService.getStudentsOfCourse(courseId);
			if (students != null) {

				for (Student student : students) {
					System.out.println(
							"Student name:" + student.getStudentName() + " and Student id:" + student.getStudentId());
				}
			} else {
				System.out.println("No students found");
			}

		} catch (InputMismatchException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void calculateCourseAverage() {

		try {
			System.out.println("Enter course id to get Course average all students in that course");

			String courseId = sc.next();

			Double courseAverage = clientService.calculateCourseAverage(courseId);
			System.out.println("Course average is: " + courseAverage);

		} catch (InputMismatchException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void getStudentGradePointAverage() {

		try {

			System.out.println("Enter student id to get Student's grade point average for all courses");
			String studentId = sc.next();
			Double studentGradePointAverage = clientService.getStudentGradePointAverage(studentId);
			System.out.println("Student's grade point average" + studentGradePointAverage);

		} catch (InputMismatchException e)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
	}

	private void resetDataStore() {

		System.out.println("Restoring backup H2");

		System.out.println("Enter timestamp in format yyyyMMdd HH:mm:ss");

		Timestamp timeStampDate = convertStringToTimestamp();

		boolean isSuccess = clientService.resetDataStore(timeStampDate.getTime());

		if (isSuccess) {
			System.out.println("Restoring backup H2 is successfull ");
		} else {
			System.out.println("Restoring backup H2 has failed ");
		}

	}

	private Timestamp convertStringToTimestamp()  {
		String timestamp = sc.nextLine();

		DateFormat formatter=new SimpleDateFormat("yyyyMMdd HH:mm:ss");
		Date date =null;
		try {
			date = formatter.parse(timestamp);
		} catch (ParseException e) {
			System.out.println("unable to parse the given date. ");
			System.exit(-1);
		}
		Timestamp timeStampDate = new Timestamp(date.getTime());
		return timeStampDate;
	}

	private void reloadMenu() throws ParseException {
		System.out.println("Do you wish to proceed, Enter 1 for Yes or 2 for No");
		int options = 0, choice = 0;

		options = sc.nextInt();

		if (options == 1) {
			choice = displayMenu();
			performOperations(choice);
			reloadMenu();

		} else {
			System.out.println("Thank you");
			System.exit(-1);
		}
	}

	private static int displayMenu() {
		System.out.println("Please select one of the following options:");
		System.out.println("1. Create Student");
		System.out.println("2. Update Credit capacity of a Student");
		System.out.println("3. Create Course");
		System.out.println("4. Update Course");
		System.out.println("5. Add a Student to a Course");
		System.out.println("6. Remove a Student from a Course");
		System.out.println("7. Get Courses Of a Student");
		System.out.println("8. GetStudents list in a Course");
		System.out.println("9. Enter Student grade for a Course");
		System.out.println("10.Get grade of a Student in a Course");
		System.out.println("11.Calculate average of all students grade point for a Course");
		System.out.println("12 Get a Student's grade point average for all courses");
		System.out.println("13 Restore backup h2");
		System.out.println("14. Exit");
		int choice = 0;
		try {
			choice = sc.nextInt();
		} catch (InputMismatchException ne)

		{
			System.out.println("Invalid option entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);

		}
		return choice;
	}

}
