package com.ClientApplication.Client;

import java.util.Date;

import com.fasterxml.jackson.annotation.JsonProperty;


public class Course {
	
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
	private Date time;

	public Long getSubjectId() {
		return subjectId;
	}

	public void setSubjectId(Long subjectId) {
		this.subjectId = subjectId;
	}

	@JsonProperty("day")
	private String day;

	public String getCourseId() {
		return courseId;
	}

	public void setCourseId(String courseId) {
		this.courseId = courseId;
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

	public Date getTime() {
		return time;
	}

	public void setTime(Date time) {
		this.time = time;
	}

	public String getDay() {
		return day;
	}

	public void setDay(String day) {
		this.day = day;
	}

	public int getCredit() {
		return credit;
	}

	public void setCredit(int credit) {
		this.credit = credit;
	}

	public String getSemester() {
		return semester;
	}

	public void setSemester(String semester) {
		this.semester = semester;
	}

	public int getCapacity() {
		return capacity;
	}

	public void setCapacity(int capacity) {
		this.capacity = capacity;
	}

	@JsonProperty("credit")
	private int credit;

	@JsonProperty("semester")
	private String semester;

	@JsonProperty("capacity")
	private int capacity;

}
