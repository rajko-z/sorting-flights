#pragma once
#include "Graph.h"
#include "Window.h"
#include "GUI.h"
#include <vector>
#include "Flight.h"
#include "Sort.h"

using namespace Graph_lib;

class VisualizationWin : public Window {
public:
	VisualizationWin(Point xy, int w, int h, const string& title, std::vector<Flight>& before,
		std::vector<Flight>& after, std::vector<IterationData>& iters);

	void writeVerticalCircles(int index);
	void writeFlightsBeforeSort();
	void writeSortedFlights();
	void writeLinesAndCirclesForOneIter();
	void deleteAll();

private:

	int m_curr_iter_index = 1;
	int m_flights_size;
	int m_max_width_sort;
	int m_width_sort;
	int m_x_begin;
	int m_y_begin;

	std::vector<Flight>m_before;
	std::vector<Flight>m_after;
	std::vector<IterationData>m_iters;

	std::vector<Circle*>m_circles;
	std::vector<Text*>m_texts;
	std::vector<Line*>m_lines;

	Button full_button;
	Button next_button;
	Button previous_button;
	Button reset_button;

	void full();
	void next();
	void previous();
	void reset();
};