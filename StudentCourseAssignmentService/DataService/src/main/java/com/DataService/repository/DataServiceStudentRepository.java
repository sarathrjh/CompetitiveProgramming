package com.DataService.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import com.DataService.domain.Student;

@Repository
public interface DataServiceStudentRepository extends JpaRepository<Student, Long>{

	Student getStudentByStudentName(String studentName);

	Student findByStudentId(String studentId);

	Student findByStudentIdentity(Long id);

}
