//============================================================================
// Name        : main.cpp
// Author      :
// Date        :
// Copyright   :
// Description :
//============================================================================

#include "Flight.h"
#include "Sort.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Utils.h"
#include "ArgsHandler.h"
#include "IO.h"
#include "MyWindow.h"
#include "VisualizationWin.h"

/*
* args: 1. inputFileName
*       2. outputFileName
*       3. algorithm (s-selectionSort, m-mergeSort)
*       4. criterium (d - destination, t -departure, fn - flight number, gn - gate number)
*       5. reverse (0 or 1)
*/
#define ARGS_NUM 5

using namespace std;


void startSortingProcedure(ArgsHandler arh);

int main(int argc, char* argv[])
{
// cmd argumetns procesing
//=================================================
	// plus one for program name
	if (argc > 1) {
		if (argc != (ARGS_NUM+1)) {
			cout << "GRESKA! pogresan broj komandnih argumenata\n";
			return -1;
		}
		ArgsHandler arh((string)argv[1], (string)argv[2], (string)argv[3],
					(string)argv[4], (string)argv[5]);
		if (!arh.argsAreValid()) {
			cout << "GRESKA! Argumenti nisu validni.\n";
			return -1;
		}
		startSortingProcedure(arh);
		return 0;
	}
//==============================================================================

	MyWindow win             (Point(100, 200), 1000, 400, "SORTING FLIGHTS");
	In_box in_bx_inFileName  (Point(500, 100), 200, 20, "Input file name:");
	In_box in_bx_outFileName (Point(500, 140), 200, 20, "Output file name:");
	In_box in_bx_sort        (Point(500, 180), 200, 20, "Input s for selectionSort or m for mergeSort:");
	In_box in_bx_criterium   (Point(500, 220), 200, 20, "Criterium[destination=d, departure=t, flight no.=fn, gate no.=gn]:");
	In_box in_bx_reverse     (Point(500, 260), 200, 20, "Input 1 for reverse sort and 0 for regular:");
	
	Text error_text          (Point(500, 300), "Error.Check your inputs again and check if files exists.");
	error_text.set_font(Font::times_bold);
	error_text.set_font_size(14);
	error_text.set_color(Color::red);


	win.attach(in_bx_inFileName);
	win.attach(in_bx_outFileName);
	win.attach(in_bx_sort);
	win.attach(in_bx_criterium);
	win.attach(in_bx_reverse);

	string inFileName, outFileName, sortName, criterium, reverse;

	ArgsHandler arh;
	while (true) {
		win.wait_for_button();
		inFileName = in_bx_inFileName.get_string();
		outFileName = in_bx_outFileName.get_string();
		sortName = in_bx_sort.get_string();
		criterium = in_bx_criterium.get_string();
		reverse = in_bx_reverse.get_string();
		arh = ArgsHandler(inFileName, outFileName, sortName, criterium, reverse);
		if (arh.argsAreValid()) {
			break;
		}
		else {
			win.attach(error_text);
		}
	}

	startSortingProcedure(arh);
	
	return 0;
}


void startSortingProcedure(ArgsHandler arh)
{
	Criterion criterion = arh.createCriterionFromArgs();
	vector<Flight>data = getDataFromFile(arh.m_inFileName);
	vector<Flight>copyData = data;

	if (arh.isSelectionSortPassed()) {
		SelectionSort s;
		s.sort(data, criterion);
		cout << criterion << '\n';
		printHeder(cout);
		printFlights(cout, data);
		printTableThroughItererations(cout, s.iterations());
		printFinalStatsAfterIterations(cout, s.iterations());
		saveDataAfterSortToFile(arh.m_outFileName, criterion, data, s.iterations());
		ostringstream ss;
		ss << "Visualization " << criterion;
		VisualizationWin win(Point(100, 200), 1400, 700, ss.str(), copyData, data, s.iterations());
		gui_main();
	}
	else {
		MergeSort s;
		s.sort(data, criterion);
		cout << criterion << '\n';
		printHeder(cout);
		printFlights(cout, data);
		printTableThroughItererations(cout, s.iterations());
		printFinalStatsAfterIterations(cout, s.iterations());
		saveDataAfterSortToFile(arh.m_outFileName, criterion, data, s.iterations());
		ostringstream ss;
		ss << "Visualization " << criterion;
		VisualizationWin win(Point(100, 200), 1400, 700, ss.str(), copyData, data, s.iterations());
		gui_main();
	}
}
