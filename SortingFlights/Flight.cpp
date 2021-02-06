//============================================================================
// Name        : Flight.cpp
// Author      : Rajko Zagorac
// Date        :
// Copyright   : 
// Description : Implementation of the Flight class
//============================================================================

#include "Flight.h"

#include <iostream>
#include <string>
#include <iomanip>
#include "Utils.h"

Flight::Flight(std::string flight_num, std::string destination, std::string deparute_time, std::string gate_num) :
	m_flight_num(flight_num),
	m_destination(destination),
	m_departure_time(deparute_time),
	m_gate_num(gate_num) {}

std::ostream& operator<<(std::ostream& os, const Flight& flight)
{
	os << std::setw(12) << flight.m_flight_num 
	    << std::setw(15) << flight.m_destination
		<< std::setw(12) << flight.m_departure_time
		<< std::setw(8) << flight.m_gate_num;
	return os;
}
std::istream& operator>>(std::istream& is, Flight& flight)
{	
	std::string end_of_line;
	std::getline(is, flight.m_destination, ';');
	std::getline(is, flight.m_departure_time, ';');
	std::getline(is, flight.m_flight_num, ';');
	std::getline(is, flight.m_gate_num, ';');
	std::getline(is, end_of_line);

	trimString(flight.m_destination);
	trimString(flight.m_departure_time);
	trimString(flight.m_flight_num);
	trimString(flight.m_gate_num);

	return is;
}

int Flight::compareTo(const Flight& other, Criterion criterion)
{
	int retVal;
	if (criterion.choice() == Choice::DESTINATION)
		retVal = m_destination.compare(other.destination());
	else if (criterion.choice() == Choice::FLIGHT_NUM)
		retVal = m_flight_num.compare(other.flight_num());
	else if (criterion.choice() == Choice::GATE_NUM)
		retVal = m_gate_num.compare(other.gate_num());
	else
		retVal = compareTime(m_departure_time, other.departure_time());

	if (criterion.reverse())
		return -1 * retVal;
	return retVal;
}