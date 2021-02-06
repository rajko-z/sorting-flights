#pragma once
#include <vector>
#include "Flight.h"
#include "Sort.h"
#include <iostream>
#include "MyWindow.h"
#include <string>


void printHeder(std::ostream& os);
void printFlights(std::ostream& os, std::vector<Flight>& data);

int compareTime(std::string time1, std::string time2);

std::vector<int> parseTime(std::string time);

void printTableThroughItererations(std::ostream& os, std::vector<IterationData>iterations);

void printFinalStatsAfterIterations(std::ostream& os, std::vector<IterationData>iterations);

void trimString(std::string& str);
