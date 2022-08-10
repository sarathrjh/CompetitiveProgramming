package com.ClientApplication.Client;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Component;
import org.springframework.web.util.UriComponentsBuilder;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;

@Component
public class ClientImpl implements ClientService {

	@Autowired
	CommunicationService communicationService;

	private static final SimpleDateFormat format = new SimpleDateFormat("yyyy-mm-dd");
	private static final SimpleDateFormat sdf = new SimpleDateFormat("hh:mm:ss");
	private static final String POST = "Post";
	private static final String GET = "GET";
	private static final String DELETE = "DELETE";
	private static final String PUT = "PUT";
	private static final String studentCourseApplicationurl = "http://localhost:8080/api";

	/*
	 * @Override public Student resetDataStore(Long timestamp) { // TODO
	 * Auto-generated method stub return null; }
	 */

	public boolean createStudent(String studentId, String studentName, int creditCapacity) {
		boolean isSuccess = false;
		ObjectMapper objectMapper = new ObjectMapper();
		Student student = new Student();
		student.setCreditCapacity(creditCapacity);
		student.setStudentId(studentId);
		student.setStudentName(studentName);
		String url = studentCourseApplicationurl + "/createStudent";
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
		ResponseEntity<Object> response = communicationService.restTemplateExchange(builder.toUriString(), POST,
				student);
		if (response != null && response.getBody() != null) {
			Student studentResponse = objectMapper.convertValue(response.getBody(), Student.class);
			if (studentResponse != null) {
				isSuccess = true;
			}
		}

		return isSuccess;

	}

	public boolean updateStudent(String studentId, int creditCapacity) {
		boolean isSuccess = false;
		ObjectMapper objectMapper = new ObjectMapper();
		Student student = new Student();
		student.setStudentId(studentId);
		student.setCreditCapacity(creditCapacity);
		String url = studentCourseApplicationurl + "/updateStudent";
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
		ResponseEntity<Object> response = communicationService.restTemplateExchange(builder.toUriString(), PUT,
				student);
		if (response != null && response.getBody() != null) {
			Student studentResponse = objectMapper.convertValue(response.getBody(), Student.class);
			if (studentResponse != null) {
				isSuccess = true;
			}
		}

		return isSuccess;

	}

	public boolean createCourse(String courseId, String courseName, String startDate, String endDate, String time,
			String day, String semester, int credit, int capacity) {
		ObjectMapper objectMapper = new ObjectMapper();
		Course course = new Course();
		boolean isSuccess = false;
		try {

			course.setCourseId(courseId);
			course.setCourseName(courseName);
			course.setDay(day);
			course.setCapacity(capacity);
			course.setSemester(semester);
			course.setStartDate(format.parse(startDate));
			course.setEndDate(format.parse(endDate));
			course.setTime(sdf.parse(time));
			course.setCredit(credit);
			String url = studentCourseApplicationurl + "/createCourse";
			UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
			ResponseEntity<Object> response = communicationService.restTemplateExchange(builder.toUriString(), POST,
					course);
			if (response != null && response.getBody() != null) {
				Course courseResponse = objectMapper.convertValue(response.getBody(), Course.class);
				if (courseResponse != null) {
					isSuccess = true;
				}
			}

		} catch (ParseException e) {
			System.out.println(
					"Invalid date format entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);
		}
		return isSuccess;

	}

	public boolean updateCourse(String courseId, String startDate, String endDate, String time, String day,
			String semester, int credit, int capacity) throws ParseException {
		ObjectMapper objectMapper = new ObjectMapper();
		Course course = new Course();
		boolean isSuccess = false;
		try {
			course.setCourseId(courseId);
			course.setDay(day);
			course.setCapacity(capacity);
			course.setSemester(semester);
			course.setStartDate(format.parse(startDate));
			course.setEndDate(format.parse(endDate));
			course.setTime(sdf.parse(time));
			String url = studentCourseApplicationurl + "/updateCourse";
			UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
			ResponseEntity<Object> response = communicationService.restTemplateExchange(builder.toUriString(), PUT,
					course);
			if (response != null && response.getBody() != null) {
				Course courseResponse = objectMapper.convertValue(response.getBody(), Course.class);
				if (courseResponse != null) {
					isSuccess = true;
				}
			}

		} catch (ParseException e) {
			System.out.println(
					"Invalid date format entered. Input Mismatch Exception occurred. Exiting the application. ");

			System.exit(-1);
		}
		return isSuccess;

	}

	public boolean addStudentToCourse(String studentId, String courseId) {
		ObjectMapper objectMapper = new ObjectMapper();
		StudentCourse studentCourse = new StudentCourse();
		boolean isSuccess = false;
		String url = studentCourseApplicationurl + "/addStudentToCourse/{studentId}/{courseId}";
		Map<String, String> urlParams = new HashMap<>();

		urlParams.put("studentId", studentId);
		urlParams.put("courseId", courseId);
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
		ResponseEntity<Object> response = communicationService
				.restTemplateExchange(builder.buildAndExpand(urlParams).toUriString(), POST, studentCourse);
		if (response != null && response.getBody() != null) {
			StudentCourse studentCourseResponse = objectMapper.convertValue(response.getBody(), StudentCourse.class);
			if (studentCourseResponse != null) {
				isSuccess = true;
			}
		}
		return isSuccess;
	}

	public boolean setStudentGradeForCourse(String studentId, String courseId, String grade) {
		ObjectMapper objectMapper = new ObjectMapper();
		StudentCourse studentCourse = new StudentCourse();
		boolean isSuccess = false;
		String url = studentCourseApplicationurl + "/setStudentGradeForCourse/{studentId}/{courseId}/{grade}";
		Map<String, String> urlParams = new HashMap<>();
		urlParams.put("studentId", studentId);
		urlParams.put("courseId", courseId);
		urlParams.put("grade", grade);
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
		ResponseEntity<Object> response = communicationService
				.restTemplateExchange(builder.buildAndExpand(urlParams).toUriString(), POST, studentCourse);
		if (response != null && response.getBody() != null) {
			StudentCourse studentCourseResponse = objectMapper.convertValue(response.getBody(), StudentCourse.class);
			if (studentCourseResponse != null) {
				isSuccess = true;
			}
		}
		return isSuccess;
	}

	public Double calculateCourseAverage(String courseId) {
		Course course = new Course();
		ObjectMapper objectMapper = new ObjectMapper();
		course.setCourseId(courseId);
		String url = studentCourseApplicationurl + "/calculateCourseAverage/{courseId}";
		Map<String, String> urlParams = new HashMap<>();
		urlParams.put("courseId", courseId);
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
		ResponseEntity<Object> response = communicationService
				.restTemplateExchange(builder.buildAndExpand(urlParams).toUriString(), GET, course);
		if (response != null && response.getBody() != null) {
			Double courseAverage = objectMapper.convertValue(response.getBody(), Double.class);

			return courseAverage;

		} else {
			System.out.println("response from calculateCourseAverage is null");

		}
		return null;
	}

	public Double getStudentGradePointAverage(String studentId) {
		Student student = new Student();
		ObjectMapper objectMapper = new ObjectMapper();
		student.setStudentId(studentId);
		String url = studentCourseApplicationurl + "/getStudentGradePointAverage/{studentId}";
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
		Map<String, String> urlParams = new HashMap<>();
		urlParams.put("studentId", studentId);
		ResponseEntity<Object> response = communicationService
				.restTemplateExchange(builder.buildAndExpand(urlParams).toUriString(), GET, student);
		if (response != null && response.getBody() != null) {
			return objectMapper.convertValue(response.getBody(), Double.class);

		} else {
			System.out.println("response from getStudentGradePointAverage is null");
		}
		return null;
	}

	public String getStudentGrade(String studentId, String courseId) {
		ObjectMapper objectMapper = new ObjectMapper();
		// StudentCourse studentCourse = new StudentCourse();
		String url = studentCourseApplicationurl + "/getStudentGrade/{studentId}/{courseId}";
		Map<String, String> urlParams = new HashMap<>();
		urlParams.put("studentId", studentId);
		urlParams.put("courseId", courseId);
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
		ResponseEntity<Object> response = communicationService
				.restTemplateExchange(builder.buildAndExpand(urlParams).toUriString(), GET, String.class);
		if (response != null && response.getBody() != null) {
			StudentCourse studentCourseResponse = objectMapper.convertValue(response.getBody(), StudentCourse.class);
			if (studentCourseResponse != null) {
				return studentCourseResponse.getGrade();
			}
		}

		else {
			System.out.println("response from getStudentGrade is null");

		}
		return null;
	}

	public boolean removeStudentFromCourse(String studentId, String courseId) {
		boolean isSuccess = false;
		StudentCourse studentCourse = new StudentCourse();

		String url = studentCourseApplicationurl + "/removeStudentFromCourse/{studentId}/{courseId}";
		Map<String, String> urlParams = new HashMap<>();
		urlParams.put("studentId", studentId);
		urlParams.put("courseId", courseId);
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
		ResponseEntity<Object> response = communicationService
				.restTemplateExchange(builder.buildAndExpand(urlParams).toUriString(), DELETE, studentCourse);
		if (response != null && response.getBody() != null) {
			isSuccess = true;
		}

		return isSuccess;

	}

	@Override
	public List<Course> getCoursesOfStudent(String studentId) {
		Course course = new Course();
		ObjectMapper objectMapper = new ObjectMapper();
		String url = studentCourseApplicationurl + "/getCoursesOfStudent/{studentId}";
		Map<String, String> urlParams = new HashMap<>();
		urlParams.put("studentId", studentId);
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
		List<Object> courseList = communicationService
				.restTemplateExchangeForList(builder.buildAndExpand(urlParams).toUriString(), GET, course);

		if (Objects.nonNull(courseList)) {
			return objectMapper.convertValue(courseList, new TypeReference<List<Course>>() {
			});

		} else {
			System.out.println("response from getCoursesOfStudent is null");

		}
		return null;
	}

	public List<Student> getStudentsOfCourse(String courseId) {
		Student student = new Student();
		ObjectMapper objectMapper = new ObjectMapper();

		String url = studentCourseApplicationurl + "/getStudentsOfCourse/{courseId}";
		Map<String, String> urlParams = new HashMap<>();
		urlParams.put("courseId", courseId);
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
		List<Object> studentList = communicationService
				.restTemplateExchangeForList(builder.buildAndExpand(urlParams).toUriString(), GET, student);
		if (Objects.nonNull(studentList) && !studentList.isEmpty()) {
			return objectMapper.convertValue(studentList, new TypeReference<List<Student>>() {
			});

		} else {
			System.out.println("response from getStudentsOfCourse is null");

		}
		return null;
	}
}
