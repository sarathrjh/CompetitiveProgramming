package com.StudentCourseAssignment.impl;

import java.util.Arrays;
import java.util.List;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.ParameterizedTypeReference;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpMethod;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Component;
import org.springframework.web.client.HttpClientErrorException;
import org.springframework.web.client.HttpServerErrorException;
import org.springframework.web.client.RestTemplate;

import com.StudentCourseAssignment.service.CommunicationService;

@Component
public class CommunicationLayerImpl implements CommunicationService {
	@Autowired
	RestTemplate restTemplate;

	public List<Object> restTemplateExchangeForList(String uriString, String httpMethod, Object object) {
		HttpHeaders headers = getHeaders();
		HttpEntity<Object> entity = new HttpEntity<Object>(object, headers);
		HttpMethod httpmethod = null;
		httpmethod = getHttpMethod(httpMethod, httpmethod);
		try {
			return restTemplate.exchange(uriString, httpmethod, entity, new ParameterizedTypeReference<List<Object>>() {
			}).getBody();

		} catch (HttpClientErrorException | HttpServerErrorException e) {
			System.out.println("Rest call failed for createStudent :" + e.getMessage());
		} catch (Exception e) {
			System.out.println("Rest call failed for createStudent :" + e.getMessage());
		}
		return null;
	}

	public ResponseEntity<Object> restTemplateExchange(String uriString, String httpMethod, Object object) {
		HttpHeaders headers = getHeaders();
		HttpEntity<Object> entity = new HttpEntity<Object>(object, headers);
		HttpMethod httpmethod = null;
		httpmethod = getHttpMethod(httpMethod, httpmethod);
		try {
			ResponseEntity<Object> response = restTemplate.exchange(uriString, httpmethod, entity, Object.class);

			if (response != null) {

				return response;

			}

		} catch (HttpClientErrorException | HttpServerErrorException e) {
			System.out.println("Rest call failed for createStudent :" + e.getMessage());
		} catch (Exception e) {
			System.out.println("Rest call failed for createStudent :" + e.getMessage());
		}
		return null;
	}

	private HttpMethod getHttpMethod(String httpMethod, HttpMethod httpmethod) {
		if (httpMethod != null && httpMethod.equalsIgnoreCase("POST")) {

			httpmethod = HttpMethod.POST;

		} else if (httpMethod != null && httpMethod.equalsIgnoreCase("PUT")) {

			httpmethod = HttpMethod.PUT;

		} else if (httpMethod != null && httpMethod.equalsIgnoreCase("GET")) {

			httpmethod = HttpMethod.GET;

		} else if (httpMethod != null && httpMethod.equalsIgnoreCase("DELETE")) {

			httpmethod = HttpMethod.DELETE;

		}
		return httpmethod;
	}

	private HttpHeaders getHeaders() {
		HttpHeaders headers = new HttpHeaders();
		headers.setAccept(Arrays.asList(MediaType.APPLICATION_JSON));
		return headers;

	}

}
