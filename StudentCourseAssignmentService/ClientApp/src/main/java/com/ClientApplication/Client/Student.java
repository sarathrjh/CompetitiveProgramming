package com.ClientApplication.Client;

public class Student {
	
	private Long studentIdentity;

	private String studentId;

	private String studentName;

	private int creditCapacity;

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

	public Long getStudentIdentity() {
		return studentIdentity;
	}

	public void setStudentIdentity(Long studentIdentity) {
		this.studentIdentity = studentIdentity;
	}

	public String getStudentId() {
		return studentId;
	}

	public void setStudentId(String studentId) {
		this.studentId = studentId;
	}

}
