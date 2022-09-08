package com.DataService;

import java.time.LocalDateTime;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cache.annotation.EnableCaching;

@SpringBootApplication
@EnableCaching
public class DataServiceApplication implements CommandLineRunner {

	public static void main(String[] args) {
		SpringApplication.run(DataServiceApplication.class, args);
	}

	@Override
	public void run(String... args) throws Exception {

		ScheduledThreadPoolExecutor threadPool = new ScheduledThreadPoolExecutor(1);

		Runnable backupH2 = new BackupH2("task1","test");
		threadPool.scheduleAtFixedRate(backupH2, 0, 60, TimeUnit.MINUTES);

		System.out.println("Shutdown and await requested at : " + LocalDateTime.now().toString());
		threadPool.shutdown();
	}

}
	

	

