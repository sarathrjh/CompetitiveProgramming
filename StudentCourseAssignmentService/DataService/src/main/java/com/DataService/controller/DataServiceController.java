package com.DataService.controller;

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

import com.DataService.domain.Course;
import com.DataService.domain.Student;
import com.DataService.domain.StudentCourse;
import com.DataService.service.DataStudentCourseService;

@RestController
@RequestMapping("/api")
public class DataServiceController {

	@Autowired
	private DataStudentCourseService dataStudentCourseService;

	@PostMapping("/createStudent")
	public Student createStudent(@RequestBody Student student) {
		return dataStudentCourseService.createStudent(student);
	}

	@GetMapping("/getStudentByStudentId/{studentId}")
	public List<Student> getStudentByStudentId(@PathVariable("studentId") String studentId) {
		return dataStudentCourseService.getStudentByStudentId(studentId);
	}

	@GetMapping("/getStudentById/{id}")
	public Student getStudentById(@PathVariable("id") Long id) {
		return dataStudentCourseService.getStudentById(id);
	}

	@GetMapping("/getStudentByStudentName/{studentName}")
	public Student getStudentByStudentName(@PathVariable("studentName") String studentName) {
		return dataStudentCourseService.getStudentByStudentName(studentName);
	}

	@GetMapping("/getCourseByCourseName/{courseName}")
	public Course getCourseByCourseName(@PathVariable("courseName") String courseName) {
		return dataStudentCourseService.getCourseByCourseName(courseName);
	}

	@GetMapping("/getCourseByCourseId/{courseId}")
	public List<Course> getCourseByCourseId(@PathVariable("courseId") String courseId) {
		return dataStudentCourseService.getCourseByCourseId(courseId);
	}

	@GetMapping("/getCourseById/{id}")
	public Course getCourseById(@PathVariable("id") Long id) {
		return dataStudentCourseService.getCourseById(id);
	}

	@PutMapping("/updateStudent")
	public Student updateStudent(@RequestBody Student student) {
		return dataStudentCourseService.updateStudent(student);
	}

	@PostMapping("/createCourse")
	public Course createCourse(@RequestBody Course course) {
		return dataStudentCourseService.createCourse(course);
	}

	@PutMapping("/updateCourse")
	public Course updateCourse(@RequestBody Course course) {
		return dataStudentCourseService.updateCourse(course);
	}

	@PostMapping("/addStudentToCourse")
	public StudentCourse addStudentToCourse(@RequestBody StudentCourse studentCourse) {
		return dataStudentCourseService.addStudentToCourse(studentCourse);
	}

	@GetMapping("/getCoursesOfStudent/{studentId}")
	public List<StudentCourse> getCoursesOfStudent(@PathVariable("studentId") Long studentId) {
		return dataStudentCourseService.getCoursesOfStudent(studentId);
	}

	@GetMapping("/getStudentsOfCourse/{courseId}")
	public List<StudentCourse> getStudentsOfCourse(@PathVariable("courseId") Long courseId) {
		return dataStudentCourseService.getStudentsOfCourse(courseId);
	}

	@PutMapping("/setStudentGradeForCourse")
	public StudentCourse setStudentGradeForCourse(@RequestBody StudentCourse studentCourse) {
		return dataStudentCourseService.setStudentGradeForCourse(studentCourse);
	}

	@GetMapping("/getStudentGrade/{studentId}/{courseId}")
	public StudentCourse getStudentGrade(@PathVariable("studentId") Long studentId,
			@PathVariable("courseId") Long courseId) {
		return dataStudentCourseService.getStudentGrade(studentId, courseId);
	}

	@DeleteMapping("/removeStudentToCourse/{id}")
	public boolean removeStudentToCourse(@PathVariable("id") Long id) {
		return dataStudentCourseService.removeStudentToCourse(id);
	}

}
