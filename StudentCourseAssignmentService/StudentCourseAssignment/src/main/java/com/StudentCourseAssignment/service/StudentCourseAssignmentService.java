package com.StudentCourseAssignment.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.util.UriComponentsBuilder;

import com.StudentCourseAssignment.domain.Course;
import com.StudentCourseAssignment.domain.Student;
import com.StudentCourseAssignment.domain.StudentCourse;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;

@Service
public class StudentCourseAssignmentService {

	@Autowired
	RestTemplate restTemplate;

	@Autowired
	CommunicationService communicationService;

	private static final String POST = "Post";
	private static final String GET = "GET";
	private static final String DELETE = "DELETE";
	private static final String PUT = "PUT";
	private static final String dataServiceUrl = "http://localhost:8082/api";

	public Student createStudent(Student student) {

		ResponseEntity<Object> students = getStudentDetails(student);
		ObjectMapper objectMapper = new ObjectMapper();
		if (Objects.isNull(students) || Objects.isNull(students.getBody())) {
			String url = dataServiceUrl + "/createStudent";
			UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
			ResponseEntity<Object> response = communicationService.restTemplateExchange(builder.toUriString(), POST,
					student);
			if (response.getBody() != null) {
				return objectMapper.convertValue(response.getBody(), Student.class);

			}

		} else {
			System.out.println("Student details already present for given student id");
		}
		return null;

	}

	public Student updateStudent(Student student) {
		ResponseEntity<Object> students = getStudentDetails(student);
		ObjectMapper objectMapper = new ObjectMapper();

		if (Objects.nonNull(students) && Objects.nonNull(students.getBody())) {
			 Student studnt = objectMapper.convertValue(students.getBody(), Student.class);
			if (studnt != null) {
				student.setStudentIdentity(studnt.getStudentIdentity());
				student.setStudentId(studnt.getStudentId());
				student.setStudentName(studnt.getStudentName());
				student.setCreditCapacity(student.getCreditCapacity());
				String url = dataServiceUrl + "/updateStudent";
				UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
				ResponseEntity<Object> response = communicationService.restTemplateExchange(builder.toUriString(), PUT,
						student);
				if (response.getBody() != null) {
					return objectMapper.convertValue(response.getBody(), Student.class);

				}
			} else {
				System.out.println("Student details not found for given student id");
			}

		} else {
			System.out.println("Student details not found for given student id");
		}
		return null;
	}

	public Course createCourse(Course course) {
		ResponseEntity<Object> courses = getCourseDetails(course);
		ObjectMapper objectMapper = new ObjectMapper();
		if (Objects.isNull(courses) || Objects.isNull(courses.getBody())) {
			String url = dataServiceUrl + "/createCourse";
			UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
			ResponseEntity<Object> response = communicationService.restTemplateExchange(builder.toUriString(), POST,
					course);
			if (response.getBody() != null) {
				return objectMapper.convertValue(response.getBody(), Course.class);

			}
		} else {
			System.out.println("Course details already present for given course id");
		}
		return null;

	}

	public StudentCourse addStudentToCourse(String studentId, String courseId) {
		ObjectMapper objectMapper = new ObjectMapper();
		Student student = new Student();
		Course course = new Course();
		StudentCourse studentCourse = new StudentCourse();
		student.setStudentId(studentId);

		ResponseEntity<Object> students = getStudentDetails(student);
		if (Objects.nonNull(students) && Objects.nonNull(students.getBody())) {
			Student studentResponse = objectMapper.convertValue(students.getBody(), Student.class);
			if (studentResponse != null) {

				course.setCourseId(courseId);
				ResponseEntity<Object> courses = getCourseDetails(course);

				if (Objects.nonNull(courses) && Objects.nonNull(courses.getBody())) {
					Course courseResponse = objectMapper.convertValue(courses.getBody(), Course.class);
					if (courseResponse != null) {
						studentCourse.setStudentId(studentResponse.getStudentIdentity());
						studentCourse.setCourseId(courseResponse.getSubjectId());
						String url = dataServiceUrl + "/getStudentGrade/{studentId}/{courseId}";
						Map<String, Long> urlParams = new HashMap<>();

						urlParams.put("studentId", studentResponse.getStudentIdentity());
						urlParams.put("courseId", courseResponse.getSubjectId());
						UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
						ResponseEntity<Object> response = communicationService.restTemplateExchange(
								builder.buildAndExpand(urlParams).toUriString(), GET, studentCourse);
						if (response == null || response.getBody() == null) {

							url = dataServiceUrl + "/addStudentToCourse";
							builder = UriComponentsBuilder.fromUriString(url);
							ResponseEntity<Object> respons = communicationService
									.restTemplateExchange(builder.toUriString(), POST, studentCourse);
							if (respons != null && respons.getBody() != null) {
								return objectMapper.convertValue(respons.getBody(), StudentCourse.class);

							}

						} else {
							System.out.println("Course is already added for given student id");
						}
					}
				}

				else {
					System.out.println("Course details not found for given course id");
				}
			}
		} else {
			System.out.println("Student details not found for given student id");
		}
		return null;

	}

	public boolean removeStudentFromCourse(String studentId, String courseId) {
		boolean isSuccess = false;
		ObjectMapper objectMapper = new ObjectMapper();
		Student student = new Student();
		Course course = new Course();
		StudentCourse studentCourse = new StudentCourse();
		student.setStudentId(studentId);

		ResponseEntity<Object> students = getStudentDetails(student);
		if (Objects.nonNull(students) && Objects.nonNull(students.getBody())) {
			Student studentList = objectMapper.convertValue(students.getBody(), Student.class);
			if (studentList != null) {

				course.setCourseId(courseId);
				ResponseEntity<Object> courses = getCourseDetails(course);

				if (Objects.nonNull(courses) && Objects.nonNull(courses.getBody())) {
					Course courseList = objectMapper.convertValue(courses.getBody(),Course.class);
					if (courseList != null) {
						studentCourse.setStudentId(studentList.getStudentIdentity());
						studentCourse.setCourseId(courseList.getSubjectId());
						String url = dataServiceUrl + "/getStudentGrade/{studentId}/{courseId}";
						Map<String, Long> urlParams = new HashMap<>();

						urlParams.put("studentId", studentCourse.getStudentId());
						urlParams.put("courseId", studentCourse.getCourseId());
						UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
						ResponseEntity<Object> response = communicationService.restTemplateExchange(
								builder.buildAndExpand(urlParams).toUriString(), GET, studentCourse);
						if (response != null && response.getBody() != null) {
							StudentCourse studentCourseResponse = objectMapper.convertValue(response.getBody(),
									StudentCourse.class);
							if (studentCourseResponse != null) {
								url = dataServiceUrl + "/removeStudentFromCourse/{id}";
								Map<String, Long> urlVariables = new HashMap<>();
								urlVariables.put("id", studentCourseResponse.getId());
								builder = UriComponentsBuilder.fromUriString(url);
								ResponseEntity<Object> result = communicationService.restTemplateExchange(
										builder.buildAndExpand(urlVariables).toUriString(), DELETE, Boolean.class);
								if (result != null) {
									return true;
								}
							}
						} else {
							System.out.println("No course found for given student id");
						}
					}

				} else {
					System.out.println("Course details not found for given course id");
				}
			}
		} else {
			System.out.println("Student details not found for given student id");
		}
		return isSuccess;

	}

	public StudentCourse setStudentGradeForCourse(String studentId, String courseId, String grade) {
		ObjectMapper objectMapper = new ObjectMapper();
		Student student = new Student();
		Course course = new Course();
		StudentCourse studentCourse = new StudentCourse();
		student.setStudentId(studentId);

		ResponseEntity<Object> students = getStudentDetails(student);
		if (Objects.nonNull(students) && Objects.nonNull(students.getBody())) {
			Student studentList = objectMapper.convertValue(students.getBody(),Student.class);
			if (studentList != null) {

				course.setCourseId(courseId);
				ResponseEntity<Object> courses = getCourseDetails(course);

				if (Objects.nonNull(courses) && Objects.nonNull(courses.getBody())) {
					Course courseResponse = objectMapper.convertValue(courses.getBody(), Course.class);
					if (courseResponse != null) {

						studentCourse.setStudentId(studentList.getStudentIdentity());
						studentCourse.setCourseId(courseResponse.getSubjectId());
						studentCourse.setGrade(grade);
						String url = dataServiceUrl + "/setStudentGradeForCourse";
						UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
						ResponseEntity<Object> response = communicationService
								.restTemplateExchange(builder.toUriString(), PUT, studentCourse);
						if (response != null && response.getBody() != null) {
							return objectMapper.convertValue(response.getBody(), StudentCourse.class);

						}

					}
				} else {
					System.out.println("Course details not found for given course id");
				}
			}

		} else {
			System.out.println("Student details not found for given student id");
		}

		return null;
	}

	public String getStudentGrade(String studentId, String courseId) {
		Student student = new Student();
		ObjectMapper objectMapper = new ObjectMapper();
		Course course = new Course();
		StudentCourse studentCourse = new StudentCourse();
		student.setStudentId(studentId);
		ResponseEntity<Object> students = getStudentDetails(student);
		if (Objects.nonNull(students) && Objects.nonNull(students.getBody())) {
			Student studentList = objectMapper.convertValue(students.getBody(), Student.class);
			if (studentList != null) {
				course.setCourseId(courseId);
				ResponseEntity<Object> courses = getCourseDetails(course);

				if (Objects.nonNull(courses) && Objects.nonNull(courses.getBody())) {
					Course courseList = objectMapper.convertValue(courses.getBody(),Course.class);
					if (courseList != null) {
						studentCourse.setStudentId(studentList.getStudentIdentity());
						studentCourse.setCourseId(courseList.getSubjectId());
						String url = dataServiceUrl + "/getStudentGrade/{studentId}/{courseId}";
						Map<String, Long> urlParams = new HashMap<>();

						urlParams.put("studentId", studentList.getStudentIdentity());
						urlParams.put("courseId", courseList.getSubjectId());
						UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
						ResponseEntity<Object> response = communicationService.restTemplateExchange(
								builder.buildAndExpand(urlParams).toUriString(), GET, studentCourse);
						if (response != null && response.getBody() != null) {
							StudentCourse studentCourseResponse = objectMapper.convertValue(response.getBody(),
									StudentCourse.class);
							if (studentCourseResponse != null) {
								return studentCourseResponse.getGrade();
							}

						}
					}
				} else {
					System.out.println("Course details not found for given course id");
				}
			}
		} else {
			System.out.println("Student details not found for given student id");
		}

		return null;
	}

	public Double getStudentGradePointAverage(String studentId) {
		try {
			StudentCourse studentCourse = new StudentCourse();
			ObjectMapper objectMapper = new ObjectMapper();
			Student student = new Student();
			student.setStudentId(studentId);
			Double sum = 0.0;
			int count = 0;
			ResponseEntity<Object> students = getStudentDetails(student);
			if (Objects.nonNull(students) && Objects.nonNull(students.getBody())) {
				Student studentList = objectMapper.convertValue(students.getBody(),Student.class);
				if (studentList != null) {
					studentCourse.setStudentId(studentList.getStudentIdentity());
					String url = dataServiceUrl + "/getCoursesOfStudent/{urlParameter}?";
					UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
					Map<String, Long> uriVariables = new HashMap<>();

					uriVariables.put("urlParameter", studentCourse.getStudentId());
					List<Object> studentCourseResponse = communicationService.restTemplateExchangeForList(
							builder.buildAndExpand(uriVariables).toString(), GET, studentCourse);
					if (Objects.nonNull(studentCourseResponse)) {
						List<StudentCourse> studentCourseList = objectMapper.convertValue(studentCourseResponse,
								new TypeReference<List<StudentCourse>>() {
								});
						if (studentCourseList != null) {
							for (StudentCourse studentCourses : studentCourseList) {
								if (studentCourses.getGrade() != null) {
									if (studentCourses.getGrade().equals("A")) {
										sum += 5;
										count++;
									} else if (studentCourses.getGrade().equals("B")) {
										sum += 4;
										count++;
									} else if (studentCourses.getGrade().equals("C")) {
										sum += 3;
										count++;
									} else if (studentCourses.getGrade().equals("D")) {
										sum += 2;
										count++;
									} else if (studentCourses.getGrade().equals("E")) {
										sum += 1;
										count++;
									} else {
										count++;

									}
								}
							}
						}

					}
					return (double) (sum / count);
				}
			} else {
				System.out.println("Student details not found for given student id");
			}
		} catch (ArithmeticException a) {
			System.out.println("ArithmeticException :" + a.getMessage());
		}
		return null;

	}

	public Double calculateCourseAverage(String courseId) {

		try {
			StudentCourse studentCourse = new StudentCourse();
			ObjectMapper objectMapper = new ObjectMapper();
			Course course = new Course();
			course.setCourseId(courseId);
			Double sum = 0.0;
			int count = 0;
			ResponseEntity<Object> courses = getCourseDetails(course);
			if (Objects.nonNull(courses) && Objects.nonNull(courses.getBody())) {
				Course courseList = objectMapper.convertValue(courses.getBody(), Course.class);
				if (courseList != null) {
					studentCourse.setCourseId(courseList.getSubjectId());
					String url = dataServiceUrl + "/getStudentsOfCourse/{urlParameter}?";
					UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
					Map<String, Long> uriVariables = new HashMap<>();

					uriVariables.put("urlParameter", studentCourse.getCourseId());
					List<Object> studentCourseList = communicationService.restTemplateExchangeForList(
							builder.buildAndExpand(uriVariables).toString(), GET, studentCourse);
					if (Objects.nonNull(studentCourseList)) {
						List<StudentCourse> studentCourseResponse = objectMapper.convertValue(studentCourseList,
								new TypeReference<List<StudentCourse>>() {
								});
						if (studentCourseResponse != null) {
							for (StudentCourse studentCourses : studentCourseResponse) {
								if (studentCourses.getGrade() != null) {
									if (studentCourses.getGrade().equals("A")) {
										sum += 5;
										count++;
									} else if (studentCourses.getGrade().equals("B")) {
										sum += 4;
										count++;
									} else if (studentCourses.getGrade().equals("C")) {
										sum += 3;
										count++;
									} else if (studentCourses.getGrade().equals("D")) {
										sum += 2;
										count++;
									} else if (studentCourses.getGrade().equals("E")) {
										sum += 1;
										count++;
									} else {
										count++;

									}
								}
							}
						}

					}
					return (double) (sum / count);
				}
			} else {
				System.out.println("Course details not found for given course id");
			}
		} catch (ArithmeticException a) {
			System.out.println("ArithmeticException :" + a.getMessage());
		}
		return null;

	}

	public Course updateCourse(Course course) {
		ResponseEntity<Object> courses = getCourseDetails(course);
		ObjectMapper objectMapper = new ObjectMapper();
		if (Objects.nonNull(courses) && Objects.nonNull(courses.getBody())) {
			Course courseList = objectMapper.convertValue(courses.getBody(), Course.class);
			if (courseList != null) {
				course.setSubjectId(courseList.getSubjectId());
				course.setCourseId(courseList.getCourseId());
				course.setCourseName(courseList.getCourseName());
				String url = dataServiceUrl + "/updateCourse";
				UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
				ResponseEntity<Object> response = communicationService.restTemplateExchange(builder.toUriString(), PUT,
						course);
				if (response != null && response.getBody() != null) {
					return objectMapper.convertValue(response.getBody(), Course.class);

				}
			} else {
				System.out.println("Course details not found for given course id");
			}
		}
		return null;
	}

	public ResponseEntity<Object> getCourseDetails(Course course) {
		String url = dataServiceUrl + "/getCourseById/{urlParameter}?";
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);

		Map<String, String> uriVariables = new HashMap<>();

		uriVariables.put("urlParameter", course.getCourseId());

		return communicationService.restTemplateExchange(builder.buildAndExpand(uriVariables).toString(), GET,
				course);

	}

	public ResponseEntity<Object> getStudentDetails(Student student) {
		Map<String, String> uriVariables = new HashMap<>();
		String url = dataServiceUrl + "/getStudentById/{urlParameter}?";
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);

		uriVariables.put("urlParameter", student.getStudentId());
		return communicationService.restTemplateExchange(builder.buildAndExpand(uriVariables).toString(), GET,
				student);
	}

	public List<Course> getCoursesOfStudent(String studentId) {
		StudentCourse studentCourse = new StudentCourse();
		Student student = new Student();
		student.setStudentId(studentId);
		ResponseEntity<Object> students = getStudentDetails(student);
		List<Course> courses = new ArrayList<>();
		Course course = new Course();
		ObjectMapper objectMapper = new ObjectMapper();

		if (Objects.nonNull(students) && Objects.nonNull(students.getBody())) {
			Student studentList = objectMapper.convertValue(students.getBody(), Student.class);
			if (studentList != null) {
				studentCourse.setStudentId(studentList.getStudentIdentity());
				String url = dataServiceUrl + "/getCoursesOfStudent/{urlParameter}?";
				UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
				Map<String, Long> uriVariables = new HashMap<>();

				uriVariables.put("urlParameter", studentCourse.getStudentId());
				List<Object> studentCourseList = communicationService.restTemplateExchangeForList(
						builder.buildAndExpand(uriVariables).toString(), GET, studentCourse);
				if (Objects.nonNull(studentCourseList)) {
					List<StudentCourse> studentCourseResponse = objectMapper.convertValue(studentCourseList,
							new TypeReference<List<StudentCourse>>() {
							});
					if (studentCourseResponse != null) {
						url = dataServiceUrl + "/getCourseByCourseId/{urlParameter}?";
						builder = UriComponentsBuilder.fromUriString(url);
						Map<String, Long> uriVariable = new HashMap<>();

						for (StudentCourse studentCourses : studentCourseResponse) {

							uriVariable.put("urlParameter", studentCourses.getCourseId());
							ResponseEntity<Object> response = communicationService
									.restTemplateExchange(builder.buildAndExpand(uriVariable).toString(), GET, course);
							if (response != null && response.getBody() != null) {
								Course subject = objectMapper.convertValue(response.getBody(), Course.class);
								if (subject != null) {
									courses.add(subject);
								}

							}
						}

					}

				}
				return courses;
			}
		} else {
			System.out.println("Student details not found for given student id");
		}

		return null;

	}

	public List<Student> getStudentsOfCourse(String courseId) {
		Course course = new Course();
		Student student = new Student();
		StudentCourse studentCourse = new StudentCourse();
		course.setCourseId(courseId);
		ResponseEntity<Object> courses = getCourseDetails(course);
		List<Student> studentList = new ArrayList<Student>();
		ObjectMapper objectMapper = new ObjectMapper();
		if (Objects.nonNull(courses) && Objects.nonNull(courses.getBody())) {
			Course courseList = objectMapper.convertValue(courses.getBody(), Course.class);
			if (courseList != null) {
				studentCourse.setStudentId(courseList.getSubjectId());
				String url = dataServiceUrl + "/getStudentsOfCourse/{urlParameter}?";
				UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
				Map<String, Long> uriVariables = new HashMap<>();

				uriVariables.put("urlParameter", studentCourse.getStudentId());

				List<Object> studentCourseList = communicationService.restTemplateExchangeForList(
						builder.buildAndExpand(uriVariables).toString(), GET, studentCourse);
				if (Objects.nonNull(studentCourseList)) {
					List<StudentCourse> studentCourseResponse = objectMapper.convertValue(studentCourseList,
							new TypeReference<List<StudentCourse>>() {
							});
					if (studentCourseResponse != null) {
						url = dataServiceUrl + "/getStudentByStudentId/{urlParameter}?";
						builder = UriComponentsBuilder.fromUriString(url);
						Map<String, Long> uriVariable = new HashMap<>();

						for (StudentCourse studentCourses : studentCourseResponse) {
							uriVariable.put("urlParameter", studentCourses.getStudentId());
							ResponseEntity<Object> response = communicationService.restTemplateExchange(
									builder.buildAndExpand(uriVariables).toString(), GET, student);
							if (Objects.nonNull(response) && Objects.nonNull(response.getBody())) {
								Student studentResponse = objectMapper.convertValue(response.getBody(), Student.class);
								if (studentResponse != null) {
									studentList.add(studentResponse);
								}

							}
						}

					}
					return studentList;
				}

			}
		} else {
			System.out.println("Course details not found for given course id");
		}

		return null;

	}

	public boolean resetDataStore(Long timestamp) {

		String url = dataServiceUrl + "/resetDataStore/{timestamp}";
		Map<String, Long> urlParams = new HashMap<>();
		urlParams.put("timestamp", timestamp);
		UriComponentsBuilder builder = UriComponentsBuilder.fromUriString(url);
		ResponseEntity<Object> response = communicationService.restTemplateExchange(builder.buildAndExpand(urlParams).toUriString(), POST,
				Boolean.class);
		if (Objects.nonNull(response) && Objects.nonNull(response.getBody())) {
			return true;
		}
		return false;
	}

}
