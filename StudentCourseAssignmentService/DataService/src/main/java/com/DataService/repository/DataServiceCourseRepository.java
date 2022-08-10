package com.DataService.repository;


import java.util.List;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import com.DataService.domain.Course;

@Repository
public interface DataServiceCourseRepository extends JpaRepository<Course, Long>{

	Course getCourseByCourseName(String courseName);

	List<Course> findByCourseId(String id);

	Course findBySubjectId(Long id);

}
