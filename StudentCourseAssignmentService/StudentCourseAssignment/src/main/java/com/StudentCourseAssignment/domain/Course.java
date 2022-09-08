package com.StudentCourseAssignment.domain;

import java.util.Date;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonProperty;

@JsonIgnoreProperties(ignoreUnknown = true)
public class Course {
	
	public String getCourseId() {
		return courseId;
	}

	public void setCourseId(String courseId) {
		this.courseId = courseId;
	}

	public String getDay() {
		return day;
	}

	public void setDay(String day) {
		this.day = day;
	}

	public String getSemester() {
		return semester;
	}

	public void setSemester(String semester) {
		this.semester = semester;
	}

	@JsonProperty("subjectId")
	private Long subjectId;
	
	@JsonProperty("courseId")
	private String courseId;

	@JsonProperty("courseName")
	private String courseName;

	@JsonProperty("startDate")
	private Date startDate;

	public Course() {
		super();
	}

	@JsonProperty("endDate")
	private Date endDate;

	@JsonProperty("time")
	private String time;
	
	@JsonProperty("day")
	private String day;

	@JsonProperty("credit")
	private int credit;
	
	@JsonProperty("semester")
	private String semester;

	@JsonProperty("capacity")
	private int capacity;

	public Course(String courseId,String courseName, Date startDate, Date endDate, String time, int credit, int capacity) {
		super();
		this.courseId = courseId;
		this.courseName = courseName;
		this.startDate = startDate;
		this.endDate = endDate;
		this.time = time;
		this.credit = credit;
		this.capacity = capacity;
	}

	public String getCourseName() {
		return courseName;
	}

	public void setCourseName(String courseName) {
		this.courseName = courseName;
	}

	public Date getStartDate() {
		return startDate;
	}

	public void setStartDate(Date startDate) {
		this.startDate = startDate;
	}

	public Date getEndDate() {
		return endDate;
	}

	public void setEndDate(Date endDate) {
		this.endDate = endDate;
	}

	public int getCredit() {
		return credit;
	}

	public Long getSubjectId() {
		return subjectId;
	}

	public void setSubjectId(Long subjectId) {
		this.subjectId = subjectId;
	}

	public void setCredit(int credit) {
		this.credit = credit;
	}

	public int getCapacity() {
		return capacity;
	}

	public void setCapacity(int capacity) {
		this.capacity = capacity;
	}

}
