#pragma once
#include <string>
#include "Criterion.h"
#include "Sort.h"

class ArgsHandler {
public:
	std::string m_inFileName;
	std::string m_outFileName;
	std::string m_sort;
	std::string m_choice;
	std::string m_reverse;

	ArgsHandler(){}
	ArgsHandler(std::string inFileName, std::string outFileName,
		        std::string sort, std::string choice, std::string reverse);

	bool argsAreValid();
	Criterion createCriterionFromArgs();

	bool isSelectionSortPassed();

};