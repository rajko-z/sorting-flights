//============================================================================
// Name        : Flight.h
// Author      : Rajko Zagorac
// Date        :
// Copyright   :
// Description :
//============================================================================
#pragma once

#include <string>
#include <iostream>
#include "Criterion.h"


class Flight
{
	std::string m_flight_num;
	std::string m_destination;
	std::string m_departure_time;
	std::string m_gate_num;

public:
	Flight() {}
	Flight(std::string flight_num, std::string destination, std::string deparute_time, std::string gate_num);

	inline std::string flight_num() const  { return m_flight_num; }
	inline std::string destination() const { return m_destination; }
	inline std::string departure_time() const { return m_departure_time; }
	inline std::string gate_num() const { return m_gate_num; }
	
	int compareTo(const Flight& other, Criterion criterion);


	int _index = 0;

	friend std::ostream& operator<<(std::ostream& os, const Flight& flight);
	friend std::istream& operator>>(std::istream& is, Flight& flight);
};
