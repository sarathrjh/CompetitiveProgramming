package com.ClientApplication.Client;

import java.text.ParseException;
import java.util.List;

import org.springframework.stereotype.Service;

@Service
public interface ClientService {

	// public Student resetDataStore(Long timestamp);

	public boolean createStudent(String studentId, String studentName, int creditCapacity);

	public boolean updateStudent(String studentId, int creditCapacity);

	public boolean createCourse(String courseId, String courseName, String startDate, String endDate, String time,
			String day, String semester, int credit, int capacity) throws ParseException;

	public boolean updateCourse(String courseId, String startDate, String endDate, String time, String day,
			String semester, int credit, int capacity) throws ParseException;

	public boolean addStudentToCourse(String studentId, String courseId);

	public boolean removeStudentFromCourse(String studentId, String courseId);

	public List<Course> getCoursesOfStudent(String studentId);

	public List<Student> getStudentsOfCourse(String courseId);

	public boolean setStudentGradeForCourse(String studentId, String courseId, String grade);

	public String getStudentGrade(String studentId, String courseId);

	public Double calculateCourseAverage(String courseId);

	public Double getStudentGradePointAverage(String studentId);

}
