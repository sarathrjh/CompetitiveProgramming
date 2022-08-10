package com.DataService.domain;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Student {
	
	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	private Long studentIdentity;
	
	private String studentId;
	
	private String studentName;

	private int creditCapacity;

	public String getStudentName() {
		return studentName;
	}

	

	public Long getStudentIdentity() {
		return studentIdentity;
	}



	public void setStudentIdentity(Long studentIdentity) {
		this.studentIdentity = studentIdentity;
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

}
