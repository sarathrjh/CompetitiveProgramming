package com.StudentCourseAssignment.domain;

import com.fasterxml.jackson.annotation.JsonProperty;

public class Student {
	
	@JsonProperty("studentIdentity")
	private Long studentIdentity;
	
	@JsonProperty("studentId")
	private String studentId;

	@JsonProperty("studentName")
	private String studentName;

	@JsonProperty("creditCapacity")
	private int creditCapacity;
	
	public Student() {
		super();
	}


	public Student(String studentId, String studentName, int creditCapacity) {
		super();
		this.studentId = studentId;
		this.studentName = studentName;
		this.creditCapacity = creditCapacity;
	}

	public String getStudentName() {
		return studentName;
	}

	public void setStudentName(String studentName) {
		this.studentName = studentName;
	}

	public int getCreditCapacity() {
		return creditCapacity;
	}

	public void setCreditCapacity(int creditCapacity) {
		this.creditCapacity = creditCapacity;
	}


	public String getStudentId() {
		return studentId;
	}


	public void setStudentId(String studentId) {
		this.studentId = studentId;
	}


	public Long getStudentIdentity() {
		return studentIdentity;
	}


	public void setStudentIdentity(Long studentIdentity) {
		this.studentIdentity = studentIdentity;
	}


	

	

}
