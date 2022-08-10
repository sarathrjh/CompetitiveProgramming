package com.StudentCourseAssignment.domain;

import com.fasterxml.jackson.annotation.JsonProperty;

public class StudentCourse {

	@JsonProperty("id")
	private Long id;

	@JsonProperty("studentId")
	private Long studentId;

	@JsonProperty("courseId")
	private Long courseId;

	@JsonProperty("grade")
	private String grade;

	public Long getId() {
		return id;
	}

	public StudentCourse() {
		super();
	}

	public void setId(Long id) {
		this.id = id;
	}

	public Long getCourseId() {
		return courseId;
	}

	public void setCourseId(Long courseId) {
		this.courseId = courseId;
	}

	public Long getStudentId() {
		return studentId;
	}

	public void setStudentId(Long studentId) {
		this.studentId = studentId;
	}

	

	public String getGrade() {
		return grade;
	}

	public void setGrade(String grade) {
		this.grade = grade;
	}
}
