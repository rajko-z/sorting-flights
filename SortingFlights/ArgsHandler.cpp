#include "ArgsHandler.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Criterion.h"
#include "Sort.h"

#define DESTINATION_STR "d"
#define DEPARTURE_TIME_STR "t"
#define FLIGHT_NUM_STR "fn"
#define GATE_NUM_STR "gn"
#define SELECETION_STR "s"
#define MERGE_STR "m"

using namespace std;

ArgsHandler::ArgsHandler(std::string inFileName, std::string outFileName,
	std::string sort, std::string choice, std::string reverse) :
	m_inFileName(inFileName),
	m_outFileName(outFileName),
	m_sort(sort),
	m_choice(choice),
	m_reverse(reverse){}

bool ArgsHandler::argsAreValid()
{	
	ifstream inFile(m_inFileName);
	if (!inFile) {
		return false;
	}
	else
		inFile.close();

	ofstream outFile(m_outFileName);
	if (!outFile) {
		return false;
	}
	else
		outFile.close();

	if (m_sort != SELECETION_STR && m_sort != MERGE_STR) {
		return false;
	}

	if (m_choice != DEPARTURE_TIME_STR && m_choice != DESTINATION_STR
		&& m_choice != FLIGHT_NUM_STR && m_choice != GATE_NUM_STR) {
		return false;
	}

	if (m_reverse != "0" && m_reverse != "1") {
		return false;
	}
	
	return true;
}

Criterion ArgsHandler::createCriterionFromArgs()
{
	bool reverse;
	Choice ch;

	if (m_reverse == "0")
		reverse = false;
	else
		reverse = true;

	if (m_choice == DESTINATION_STR)
		ch = Choice::DESTINATION;
	else if (m_choice == DEPARTURE_TIME_STR)
		ch = Choice::DEPARTURE_TIME;
	else if (m_choice == FLIGHT_NUM_STR)
		ch = Choice::FLIGHT_NUM;
	else if (m_choice == GATE_NUM_STR)
		ch = Choice::GATE_NUM;

	Criterion retCriterium(ch, reverse);
	return retCriterium;
}

bool ArgsHandler::isSelectionSortPassed()
{
	if (m_sort == SELECETION_STR)
		return true;
	return false;
}