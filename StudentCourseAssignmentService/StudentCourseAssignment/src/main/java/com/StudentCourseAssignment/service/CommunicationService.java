package com.StudentCourseAssignment.service;

import java.util.List;

import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;

@Service
public interface CommunicationService {

	public ResponseEntity<Object> restTemplateExchange(String uriString, String httpMEthod, Object object);

	public List<Object> restTemplateExchangeForList(String uriString, String httpMEthod, Object object);

}
