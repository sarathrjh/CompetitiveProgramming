package com.DataService.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import com.DataService.domain.StudentCourse;

@Repository
public interface DataStudentCourseRepository extends JpaRepository<StudentCourse, Long>{

	List<StudentCourse> findByStudentId(Long studentId);

	List<StudentCourse> findByCourseId(Long studentId);

	StudentCourse findByStudentIdAndCourseId(Long studentId, Long courseId);


}
