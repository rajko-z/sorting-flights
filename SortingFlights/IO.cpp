#include "IO.h"
#include <iostream>
#include <fstream>
#include "Sort.h"
#include "Utils.h"

using namespace std;

vector<Flight> getDataFromFile(string fileName)
{
	vector<Flight>flights;
	ifstream inFile(fileName);
	Flight fl;
	inFile.ignore(1024, '\n');
	while (inFile >> fl) {
		flights.push_back(fl);
	}
	return flights;
}

void saveDataAfterSortToFile(string fileName, Criterion criterion, vector<Flight>& data,
							vector<IterationData>& iters)
{
	ofstream os(fileName);
	os << criterion << '\n';
	os << "_______________________\n";
	os << "RESULTS AFTER SORTING\n";
	os << "-----------------------\n";
	printHeder(os);
	printFlights(os, data);
	printTableThroughItererations(os, iters);
	printFinalStatsAfterIterations(os, iters);
	os.close();
}