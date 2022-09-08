package com.DataService.test;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.DataService.BackupH2;
import com.DataService.service.DataStudentCourseService;

@RunWith(SpringRunner.class)
@SpringBootTest
public class DataServiceTest {

	@Autowired
	DataStudentCourseService dataStudentCourseService;


	@Test
	public void backUpH2() {
		BackupH2 backupH2 = new BackupH2("task1","test");
		backupH2.run();
	}

}
