package com.DataService.service;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;

import org.h2.tools.Restore;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.CacheEvict;
import org.springframework.cache.annotation.CachePut;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.cache.annotation.Caching;
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
	
	@CachePut(cacheNames = "Students", key ="#student.studentId")
	public Student createStudent(Student student) {

		return dataServiceStudentRepository.save(student);
	}

	@Cacheable(cacheNames = "Students", key ="#p0")
	public Student getStudentById(String studentId) {
		return dataServiceStudentRepository.findByStudentId(studentId);
	}

	@Cacheable(cacheNames = "Students", key ="#studentName")
	public Student getStudentByStudentName(String studentName) {
		return dataServiceStudentRepository.getStudentByStudentName(studentName);
	}

	@CachePut(cacheNames = "Students", key ="#student.studentId")
	public Student updateStudent(Student student) {
		 return dataServiceStudentRepository.save(student);
	}

	@CachePut(cacheNames = "Courses", key ="#course.courseId")
	public Course createCourse(Course course) {
		return dataServiceCourseRepository.save(course);
	}

	@CachePut(cacheNames = "Courses", key ="#course.courseId")
	public Course updateCourse(Course course) {
		 return dataServiceCourseRepository.save(course);
	}

	@Cacheable(cacheNames = "Courses", key ="#courseName")
	public Course getCourseByCourseName(String courseName) {
		return dataServiceCourseRepository.getCourseByCourseName(courseName);
	}

	//@CachePut(cacheNames = "StudentCourses", key = "#result.studentId+#result.courseId")
	@Caching(put= {@CachePut(key="#result.studentId.concat(#result.courseId)")})
	public StudentCourse addStudentToCourse(StudentCourse studentCourse) {
		 return dataStudentCourseRepository.save(studentCourse);
	}

	@CacheEvict(cacheNames = "StudentCourses", key ="#p0")
	public void removeStudentToCourse(StudentCourse studentCourse) {
		 dataStudentCourseRepository.delete(studentCourse);
	}

	@Cacheable(cacheNames = "StudentCourses", key ="#result.p0")
	public List<StudentCourse> getCoursesOfStudent(Long studentId) {
		return  dataStudentCourseRepository.findByStudentId(studentId);
		
	}

	@Cacheable(cacheNames = "Courses", key ="#p0")
	public Course getCourseByCourseId(Long subjectId) {
		return dataServiceCourseRepository.findBySubjectId(subjectId);
	}
	 

	@Cacheable(cacheNames = "StudentCourses", key ="#result.p0")
	public List<StudentCourse> getStudentsOfCourse(Long courseId) {
		return  dataStudentCourseRepository.findByCourseId(courseId);
	}

	@CachePut(cacheNames = "StudentCourses", key ="#studentCourse.id")
	public StudentCourse setStudentGradeForCourse(StudentCourse studentCourse) {
		return dataStudentCourseRepository.save(studentCourse);
	}
	
	@Cacheable(cacheNames = "StudentCourses", key = "#result.p0.concat(#result.p1)")
	public StudentCourse getStudentGrade(Long studentId,Long courseId) {
		return dataStudentCourseRepository.findByStudentIdAndCourseId(studentId,courseId);
	}
	
	@CacheEvict(cacheNames = "StudentCourses", key ="#p0")
	public boolean removeStudentToCourse(Long id) {
		dataStudentCourseRepository.deleteById(id);
		return true;
	}

	@Cacheable(cacheNames = "Courses", key ="#p0")
	public Course getCourseById(String courseId) {
		return dataServiceCourseRepository.findByCourseId(courseId);
	}

	@Cacheable(cacheNames = "Student", key ="#p0")
	public Student getStudentByStudentId(Long studentIdentity) {

		return dataServiceStudentRepository.findByStudentIdentity(studentIdentity);
	}

	public boolean resetDataStore(Long timestamp) throws FileNotFoundException {

		System.out.println("Restoring test");
		long tmstmp = findMatchingRestoreFileTimestamp(timestamp);

		Restore.execute("C:\\h2\\db\\" + tmstmp + ".zip", "memFS:test;DB_CLOSE_DELAY=-1;DB_CLOSE_ON_EXIT=FALSE",
				"test");
		return true;
	}

	private long findMatchingRestoreFileTimestamp(Long timestamp) {
		long tmstmp = 0;
		boolean isFirst = true;
		long min = 0;

		List<String> results = new ArrayList<String>();

		File[] files = new File("C:\\h2\\db\\").listFiles();

		for (File file : files) {
			if (file.isFile()) {
				results.add(file.getName().split("\\.")[0]);
			}
		}

		for (int i = 0; i < results.size(); i++) {

			long diff = Math.abs(Long.valueOf(results.get(i)) - (timestamp));

			if (isFirst) {
				min = diff;
				tmstmp = Long.valueOf(results.get(i));
				isFirst = false;
			} else {
				if (diff < min) {
					min = diff;
					tmstmp = Long.valueOf(results.get(i));
				}
			}

		}
		return tmstmp;
	}

}
