#pragma once
#include <iostream>
#include <fstream>

enum class Choice { FLIGHT_NUM = 1, DESTINATION, DEPARTURE_TIME, GATE_NUM};


class Criterion {
	Choice m_choice;
	bool m_reverse;
public:
	Criterion(Choice choice, bool reverse): m_choice(choice), m_reverse(reverse){}
	inline Choice choice() const { return m_choice; }
	inline bool reverse() const { return m_reverse; }
	friend std::ostream& operator<<(std::ostream& os, const Criterion& criterion);
};