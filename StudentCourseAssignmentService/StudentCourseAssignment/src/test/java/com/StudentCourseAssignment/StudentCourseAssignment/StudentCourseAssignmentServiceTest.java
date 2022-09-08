package com.studentCourseAssignment;

import static org.assertj.core.api.AssertionsForClassTypes.assertThat;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Objects;

import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.MethodSorters;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.ResponseEntity;
import org.springframework.test.context.junit4.SpringRunner;

import com.StudentCourseAssignment.domain.Course;
import com.StudentCourseAssignment.domain.Student;
import com.StudentCourseAssignment.service.StudentCourseAssignmentService;
import com.fasterxml.jackson.databind.ObjectMapper;

@RunWith(SpringRunner.class)
@SpringBootTest
@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class StudentCourseAssignmentServiceTest {

	@Autowired
	StudentCourseAssignmentService studentCourseAssignmentService;

	@Test
	public void createStudent() {

		Student student = new Student("1005", "Amiyaaa", 3);
		ResponseEntity<Object> students = studentCourseAssignmentService.getStudentDetails(student);
		assertTrue("Students details were not found, hence creating new record",
				Objects.isNull(students) || Objects.isNull(students.getBody()));
		studentCourseAssignmentService.createStudent(student);

	}

	@Test
	public void createStudentFailure() {
		Student student = new Student("1005", "Amiyaaa", 3);
		ResponseEntity<Object> students = studentCourseAssignmentService.getStudentDetails(student);
		assertFalse("Students details were  found, hence not creating new record",
				Objects.isNull(students) || Objects.isNull(students.getBody()));

	}

	@Test 
	public void isStudentExistsById() {

		Student student = new Student("1007", "Amiyaaa", 3);
		studentCourseAssignmentService.createStudent(student);
		ResponseEntity<Object> students = studentCourseAssignmentService.getStudentDetails(student);
		ObjectMapper objectMapper = new ObjectMapper();
		if (Objects.nonNull(students) && Objects.nonNull(students.getBody())) {
			Student studentResponse = objectMapper.convertValue(students.getBody(), Student.class);
			assertThat(studentResponse.getStudentId()).isEqualTo(student.getStudentId());
		}
	}
	
	
	@Test
	public void createCourse() throws ParseException {

		Course course = new Course("1000","English",new SimpleDateFormat("yyyy-mm-dd").parse("2022-01-01"),
				new SimpleDateFormat("yyyy-mm-dd").parse("2022-01-01"),
				"02:00:00",3,4);
		ResponseEntity<Object> courses = studentCourseAssignmentService.getCourseDetails(course);
		assertTrue("Course details were not found, hence creating new record",
				Objects.isNull(courses) || Objects.isNull(courses.getBody()));
		studentCourseAssignmentService.createCourse(course);

	}

	@Test
	public void createCourseFailure() throws ParseException {
		Course course = new Course("1000","English",new SimpleDateFormat("yyyy-mm-dd").parse("2022-01-01"),
				new SimpleDateFormat("yyyy-mm-dd").parse("2022-01-01"),
				"02:00:00",3,4);
		ResponseEntity<Object> courses = studentCourseAssignmentService.getCourseDetails(course);
		assertFalse("Course details were  found, hence not creating new record",
				Objects.isNull(courses) || Objects.isNull(courses.getBody()));

	}

	@Test 
	public void isCourseExistsById() throws ParseException {

		Course course = new Course("1000","English",new SimpleDateFormat("yyyy-mm-dd").parse("2022-01-01"),
				new SimpleDateFormat("yyyy-mm-dd").parse("2022-01-01"),
				"02:00:00",3,4);
		studentCourseAssignmentService.createCourse(course);
		ResponseEntity<Object> courses = studentCourseAssignmentService.getCourseDetails(course);
		ObjectMapper objectMapper = new ObjectMapper();
		if (Objects.nonNull(courses) && Objects.nonNull(courses.getBody())) {
			Course courseResponse = objectMapper.convertValue(courses.getBody(), Course.class);
			assertThat(courseResponse.getCourseId()).isEqualTo(course.getCourseId());
		}
	}


}
