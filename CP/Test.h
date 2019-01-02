// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <assert.h>
#include <map>
#include <limits>

template<class K, class V>
class interval_map {
	friend void IntervalMapTest();

private:
	std::map<K, V> m_map;

public:
	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	interval_map(V const& val) {
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	};

	// Assign value val to interval [keyBegin, keyEnd). 
	// Overwrite previous values in this interval. 
	// Do not change values outside this interval.
	// Conforming to the C++ Standard Library conventions, the interval 
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval, 
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, const V& val)
	{
		if(!(keyBegin < keyEnd))
		{
			return;
		}

		K minKey = std::numeric_limits<K>::lowest();
		K maxKey = std::numeric_limits<K>::lowest();

		V minValue = m_map[minKey];
		V maxValue = m_map[maxKey];
		std::map<K, V>::iterator it;
		for (it = m_map.begin(); (it != m_map.end() && it->first < keyEnd);)
		{
			if (minKey  < it->first && it->first < keyBegin)
			{
				minKey = it->first;
				minValue = it->second;
			}

			if (maxKey < it->first && it->first < keyEnd)
			{
				maxKey = it->first;
				maxValue = it->second;
			}

			if (!(it->first < keyBegin) && it->first < keyEnd)
			{
				m_map.erase(it++);
			}
			else
			{
				++it;
			}
		}

		if (minValue != val)
		{
			m_map.erase(keyBegin);
			m_map.insert(std::pair<K, V>(keyBegin, val));
		}

		if (it != m_map.end() && (it == m_map.find(keyEnd)) && it->second == val)
		{
			m_map.erase(it);
		}
		else if (maxValue != val)
		{
			m_map.insert(std::pair<K, V>(keyEnd, maxValue));
		}
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		return (--m_map.upper_bound(key))->second;
	}

	void initialize(V const& val) 
	{
		m_map.clear();
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	};

	void Print()
	{
		std::map<K, V>::iterator it;
		for (it = m_map.begin(); (it != m_map.end() ); ++it)
		{
			std::cout << "Key : " << it->first << " , value : " << it->second << "\n";
		}

	}
};


//void Initialize(interval_map<int, char>& myMap, char first)
//{
//	myMap.initialize('A');
//	myMap.assign(5, 10, 'B');
//	myMap.assign(10, 15, 'C');
//	myMap.assign(15, 20, 'D');
//	myMap.assign(20, 25, 'E');
//	myMap.assign(25, 30, 'F');
//	myMap.assign(30, 35, 'G');
//
//}

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.
/*int _tmain(int argc, _TCHAR* argv[])
{
	// Normal
	interval_map<int, char> myMap('A');
	// Initialize(myMap, 'A');
	
	std::cout << "Initial values : \n";
	myMap.Print();

	std::cout << "\n\nTest values  (-3, 3, 'A') : \n";
	myMap.assign(-3, 3, 'A');
	std::cout << "\n\nTest values (21, 30, 'G') : \n";
	myMap.assign(21, 30, 'G');
	myMap.Print();
	//myMap.Print();

	/*
	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (21, 30, 'G') : \n";
	myMap.assign(21, 30, 'G');
	myMap.Print();


	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (42, 47, 'S') : \n";
	myMap.assign(42, 47, 'S');
	myMap.Print();

	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (25, 34, 'F') : \n";
	myMap.assign(25, 34, 'F');
	myMap.Print();

	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (11, 15, 'D') : \n";
	myMap.assign(11, 15, 'D');
	myMap.Print();


	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (10, 10, 'T') : \n";
	myMap.assign(10, 10, 'T');
	myMap.Print();

	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (15, 10, 'T') : \n";
	myMap.assign(15, 10, 'T');
	myMap.Print();

	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (15, 10, 'T') : \n";
	myMap.assign(25, 35, 'A');
	myMap.Print();


	
	return 0;
}*/

