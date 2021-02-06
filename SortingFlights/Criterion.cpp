#include "Criterion.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ostream& operator<<(std::ostream& os, const Criterion& criterion)
{	
	string choice;
	if (criterion.choice() == Choice::DEPARTURE_TIME)
		choice = "DEPARTURE TIME";
	else if (criterion.choice() == Choice::DESTINATION)
		choice = "DESTINATION";
	else if (criterion.choice() == Choice::FLIGHT_NUM)
		choice = "FLIGHT NO.";
	else if (criterion.choice() == Choice::GATE_NUM)
		choice = "GATE NO.";

	string reverse;
	if (criterion.reverse())
		reverse = "TRUE";
	else
		reverse = "FALSE";

	os << "[ Criterium of sorting = " << choice << " , reverse = " << reverse << " ]";
	return os;
}