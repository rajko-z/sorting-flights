#pragma once
#include <vector>
#include <string>
#include "Flight.h"
#include "Sort.h"

// vraca listu vektora citanjem iz fajla
// napomena je da funkcija direktno ne provera validnost fajla
// sve provere se rade pre nego sto uopste dodje do poziva ove funkcije
std::vector<Flight> getDataFromFile(std::string fileName);

// cuvanje podataka o sortiranju nazad u zadati fajl
// takodje ne proverava validnost fajla jer se to radi pre samog poziva
void saveDataAfterSortToFile(std::string fileName, Criterion criterion, std::vector<Flight>& data,
	std::vector<IterationData>& iters);
