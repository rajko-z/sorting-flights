#include <iostream>
#include <iomanip>
#include "Utils.h"
#include <vector>
#include <string>
#include <sstream>
#include "Flight.h"
#include "Sort.h"

using namespace std;

void printHeder(ostream& os)
{
	os << "===========================================================\n";
	os << setw(12) << "Flight No."
		<< setw(15) << "Destination"
		<< setw(12) << "Departure"
		<< setw(15) << "Gate No.\n";
	os << "===========================================================\n";
}

void printFlights(ostream& os, vector<Flight>& data)
{
	for (auto f : data) os << f << '\n';
}


vector<int> parseTime(std::string time)
{
	stringstream stream(time);
	string s;
	vector<int>tokens;
	while (getline(stream, s, ':')) {
		tokens.push_back(stoi(s));
	}
	return tokens;
}

int compareTime(std::string timeOne, std::string timeTwo)
{
	vector<int>time1 = parseTime(timeOne);
	vector<int>time2 = parseTime(timeTwo);
	if (time1[0] < time2[0])
		return -1;
	if (time1[0] > time2[0])
		return 1;
	if (time1[1] < time2[1])
		return -1;
	if (time1[1] > time2[1])
		return 1;
	return 0;
}

void printTableThroughItererations(ostream& os, vector<IterationData>iterations)
{	
	os << "===========================================================\n";
	os << setw(12) << "Iteration" << setw(20) << "Comparisons No." << setw(15) << "Swaps No." << '\n';
	os << "===========================================================\n";
	int br = 0;
	for (auto it : iterations) {
		os << setw(12) << ++br << setw(20) << it.num_cmps() << setw(15) << it.num_swaps() << '\n';
	}
}

void printFinalStatsAfterIterations(ostream& os, vector<IterationData>iterations)
{
	os << "____________________________________________________________\n";
	int num_swaps = 0;
	int num_comparasions = 0;
	for (auto it : iterations) {
		num_swaps += it.num_swaps();
		num_comparasions += it.num_cmps();
	}
	os << "Iterations No. = " << iterations.size() << "   "
		<< "Swaps No. = " << num_swaps << "   "
		<< "Comparisons No. = " << num_comparasions << "   \n";
	os << "____________________________________________________________\n";
	
}


void trimString(string& str) {
	if (!str.size())
		return;
	int beg = 0;
	while (str[beg] == ' ') {
		if ((++beg) == str.size())
			break;
	}
	int end = str.size() - 1;
	while (str[end] == ' ') {
		if ((--end) < 0)
			break;
	}
	str = str.substr(beg, end - beg + 1);
}