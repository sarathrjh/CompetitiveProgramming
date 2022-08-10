package com.DataService.service;

import java.util.List;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import com.DataService.domain.Course;
import com.DataService.domain.Student;
import com.DataService.domain.StudentCourse;
import com.DataService.repository.DataServiceCourseRepository;
import com.DataService.repository.DataServiceStudentRepository;
import com.DataService.repository.DataStudentCourseRepository;

@Service
public class DataStudentCourseService {

	@Autowired
	private DataServiceStudentRepository dataServiceStudentRepository;
	
	@Autowired
	private DataServiceCourseRepository dataServiceCourseRepository ;
	
	@Autowired
	private DataStudentCourseRepository dataStudentCourseRepository ;
	
	public Student createStudent(Student student) {

		return dataServiceStudentRepository.save(student);
	}

	public Student getStudentById(Long id) {
		return dataServiceStudentRepository.findByStudentIdentity(id);
	}

	public Student getStudentByStudentName(String studentName) {
		return dataServiceStudentRepository.getStudentByStudentName(studentName);
	}

	public Student updateStudent(Student student) {
		 return dataServiceStudentRepository.save(student);
	}

	public Course createCourse(Course course) {
		return dataServiceCourseRepository.save(course);
	}

	public Course updateCourse(Course course) {
		 return dataServiceCourseRepository.save(course);
	}

	public Course getCourseByCourseName(String courseName) {
		return dataServiceCourseRepository.getCourseByCourseName(courseName);
	}

	public StudentCourse addStudentToCourse(StudentCourse studentCourse) {
		 return dataStudentCourseRepository.save(studentCourse);
	}

	public void removeStudentToCourse(StudentCourse studentCourse) {
		 dataStudentCourseRepository.delete(studentCourse);
	}

	public List<StudentCourse> getCoursesOfStudent(Long studentId) {
		return  dataStudentCourseRepository.findByStudentId(studentId);
		
	}

	public List<Course> getCourseByCourseId(String id) {
		return dataServiceCourseRepository.findByCourseId(id);
	}

	public List<StudentCourse> getStudentsOfCourse(Long courseId) {
		return  dataStudentCourseRepository.findByCourseId(courseId);
	}

	public StudentCourse setStudentGradeForCourse(StudentCourse studentCourse) {
		return dataStudentCourseRepository.save(studentCourse);
	}

	public StudentCourse getStudentGrade(Long studentId,Long courseId) {
		return dataStudentCourseRepository.findByStudentIdAndCourseId(studentId,courseId);
	}
	

	public boolean removeStudentToCourse(Long id) {
		dataStudentCourseRepository.deleteById(id);
		return true;
	}

	public Course getCourseById(Long id) {
		return dataServiceCourseRepository.findBySubjectId(id);
	}

	public List<Student> getStudentByStudentId(String studentId) {
		
		 return dataServiceStudentRepository.findByStudentId(studentId);
	}

}
