package com.DataService;

import java.sql.SQLException;
import java.time.Instant;

import org.h2.tools.Backup;

public class BackupH2 implements Runnable {
	String taskName;
	
	String dbName;

	public BackupH2(String taskName, String dbName) {
		this.taskName = taskName;
		this.dbName = dbName;
		
	}

	public void run() {
		try {

			System.out.println("Backing up test");
			Backup.execute("C:\\h2\\db\\" + Instant.now().toEpochMilli() + ".zip", "memFS:", dbName, true);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

}
