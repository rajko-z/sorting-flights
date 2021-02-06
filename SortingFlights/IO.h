#pragma once
#include <vector>
#include <string>
#include "Flight.h"
#include "Sort.h"

std::vector<Flight> getDataFromFile(std::string fileName);

void saveDataAfterSortToFile(std::string fileName, Criterion criterion, std::vector<Flight>& data,
	std::vector<IterationData>& iters);
