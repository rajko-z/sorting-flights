#pragma once
#include <string>
#include "Criterion.h"
#include "Sort.h"

// klasa zaduzena za obradu argumenata komandne linije ali
// i vrednosti dobijenih pomocnu korisnicke sprege
// glavna uloga je provera validnosti argumenata i pravljenje kriterijuma
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

	// funkcija prolazi redom kroz prosledjene argumente i proverava da li su validni
	bool argsAreValid();
	// ako su argumetni validni, onda se pravi kriterijum sortiranja koji koristi algoritam sortiranja
	Criterion createCriterionFromArgs();

	bool isSelectionSortPassed();

};