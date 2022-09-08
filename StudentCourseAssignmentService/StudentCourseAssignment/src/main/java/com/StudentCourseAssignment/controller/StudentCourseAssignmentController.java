package com.StudentCourseAssignment.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.StudentCourseAssignment.domain.Course;
import com.StudentCourseAssignment.domain.Student;
import com.StudentCourseAssignment.domain.StudentCourse;
import com.StudentCourseAssignment.service.StudentCourseAssignmentService;

@RestController
@RequestMapping("/api")
public class StudentCourseAssignmentController {

	@Autowired
	private StudentCourseAssignmentService studentCourseAssignmentService;

	@PostMapping("/createStudent")
	public Student createStudent(@RequestBody Student student) {
		return studentCourseAssignmentService.createStudent(student);
	}

	@PutMapping("/updateStudent")
	public Student updateStudent(@RequestBody Student student) {
		return studentCourseAssignmentService.updateStudent(student);
	}

	@PostMapping("/createCourse")
	public Course createCourse(@RequestBody Course course) {
		return studentCourseAssignmentService.createCourse(course);
	}

	@PutMapping("/updateCourse")
	public Course updateCourse(@RequestBody Course course) {
		return studentCourseAssignmentService.updateCourse(course);
	}

	@PostMapping("/addStudentToCourse/{studentId}/{courseId}")
	public StudentCourse addStudentToCourse(@PathVariable("studentId") String studentId,
			@PathVariable("courseId") String courseId) {
		return studentCourseAssignmentService.addStudentToCourse(studentId, courseId);
	}

	@GetMapping("/getStudentGrade/{studentId}/{courseId}")
	public String getStudentGrade(@PathVariable("studentId") String studentId,
			@PathVariable("courseId") String courseId) {
		return studentCourseAssignmentService.getStudentGrade(studentId, courseId);
	}

	@DeleteMapping("/removeStudentFromCourse/{studentId}/{courseId}")
	public boolean removeStudentFromCourse(@PathVariable("studentId") String studentId,
			@PathVariable("courseId") String courseId) {
		return studentCourseAssignmentService.removeStudentFromCourse(studentId, courseId);
	}

	@PostMapping("/setStudentGradeForCourse/{studentId}/{courseId}/{grade}")
	public StudentCourse setStudentGradeForCourse(@PathVariable("studentId") String studentId,
			@PathVariable("courseId") String courseId,

			@PathVariable("grade") String grade) {
		return studentCourseAssignmentService.setStudentGradeForCourse(studentId, courseId, grade);
	}

	@GetMapping("/getCoursesOfStudent/{studentId}")
	public List<Course> getCoursesOfStudent(@PathVariable("studentId") String studentId) {
		return studentCourseAssignmentService.getCoursesOfStudent(studentId);
	}

	@GetMapping("/calculateCourseAverage/{courseId}")
	public Double calculateCourseAverage(@PathVariable("courseId") String courseId) {
		return studentCourseAssignmentService.calculateCourseAverage(courseId);
	}

	@GetMapping("/getStudentsOfCourse/{courseId}")
	public List<Student> getStudentsOfCourse(@PathVariable("courseId") String courseId) {
		return studentCourseAssignmentService.getStudentsOfCourse(courseId);
	}

	@GetMapping("/getStudentGradePointAverage/{studentId}")
	public Double getStudentGradePointAverage(@PathVariable("studentId") String studentId) {
		return studentCourseAssignmentService.getStudentGradePointAverage(studentId);
	}

	@PostMapping("/resetDataStore/{timestamp}")
	public boolean resetDataStore(@PathVariable("timestamp") Long timestamp) {
		return studentCourseAssignmentService.resetDataStore(timestamp);
	}

}
