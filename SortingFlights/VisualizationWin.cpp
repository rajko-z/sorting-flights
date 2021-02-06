#include "VisualizationWin.h"
#include <iostream>
#include <string>


VisualizationWin::VisualizationWin(Point xy, int w, int h, const string& title, std::vector<Flight>& before,
	std::vector<Flight>& after, std::vector<IterationData>& iters) :
	m_before(before),
	m_after(after),
	m_iters(iters),
	m_flights_size(before.size()),
	Window(xy, w, h, title),
	full_button(Point(570, 10), 150, 40, "FULL VISUALIZATION",
		[](Address, Address pw) {reference_to<VisualizationWin>(pw).full(); }),
	next_button(Point(870, 10), 150, 40, "NEXT STEP>>",
		[](Address, Address pw) {reference_to<VisualizationWin>(pw).next(); }),
	previous_button(Point(720, 10), 150, 40, "<<PREVIOUS STEP",
		[](Address, Address pw) {reference_to<VisualizationWin>(pw).previous(); }),
	reset_button(Point(420, 10), 150, 40, "RESET",
		[](Address, Address pw) {reference_to<VisualizationWin>(pw).reset(); })
{	
	attach(full_button);
	attach(next_button);
	attach(reset_button);
	attach(previous_button);
	writeFlightsBeforeSort();
	writeSortedFlights();

	m_x_begin = 220;
	m_y_begin = 80;
	m_max_width_sort = x_max() - 2 * 200 - 40;
	m_width_sort = m_max_width_sort / (m_iters.size());

	Text* iterNum_txt = new Text(Point(10, 20), "1, 2, 3...ITERATION NO.");
	Text* desciption = new Text(Point(0, 50), "DESTINATION|FLIGHT NO.|DEPARTURE");
	Text* sorted_txt = new Text(Point(x_max() - 200, 50), "SORTED FLIGHTS");
	attach(*iterNum_txt);
	attach(*desciption);
	attach(*sorted_txt);
	(*iterNum_txt).set_color(Color::blue);
	(*iterNum_txt).set_font(Font::screen_bold);
	(*desciption).set_color(Color::blue);
	(*desciption).set_font(Font::times_bold_italic);
	(*sorted_txt).set_color(Color::blue);
	(*sorted_txt).set_font(Font::times_bold_italic);

	int xcord = m_x_begin;
	int dx = 0;
	for (int i = 0; i < m_flights_size; ++i) {
		Circle* c = new Circle(Point(xcord, 80 + dx), 10);
		attach(*c);
		dx += 50;
	}
	Text* t = new Text(Point(xcord, 80 + dx), to_string(0));
	(*t).set_color(Color::blue);
	(*t).set_font(Font::screen_bold);
	attach(*t);

}


void VisualizationWin::writeVerticalCircles(int index)
{
	int xcord = m_x_begin + index * m_width_sort;
	int dx = 0;
	for (int i = 0; i < m_flights_size; ++i) {
		Circle* c = new Circle(Point(xcord, 80 + dx), 10);
		attach(*c);
		m_circles.push_back(c);
		dx += 50;
	}
	Text* t = new Text(Point(xcord, 80 + dx), to_string(index));
	attach(*t);
	(*t).set_color(Color::blue);
	(*t).set_font(Font::screen_bold);
	m_texts.push_back(t);
}

void VisualizationWin::writeLinesAndCirclesForOneIter()
{
	if (m_curr_iter_index > m_iters.size() || m_curr_iter_index <= 0)
		return;

	writeVerticalCircles(m_curr_iter_index);
	IterationData iterData = m_iters.at(m_curr_iter_index - 1);
	for (auto& it : iterData.mapa()) {
		int xpt1 = m_x_begin + (m_curr_iter_index - 1) * m_width_sort;
		int ypt1 = 80 + 50 * it.first;
		Point* pt1 = new Point(xpt1, ypt1);
		int xpt2 = m_x_begin + m_curr_iter_index * m_width_sort;
		int ypt2 = 80 + 50 * it.second;
		Point* pt2 = new Point(xpt2, ypt2);

		Line* line = new Line(*pt1, *pt2);
		attach(*line);
		m_lines.push_back(line);
	}
	m_curr_iter_index += 1;
}


void VisualizationWin::next()
{	
	writeLinesAndCirclesForOneIter();
	redraw();
}

void VisualizationWin::full()
{
	if (m_curr_iter_index > m_iters.size())
		return;

	if (m_lines.size() > 0)
		deleteAll();

	for (int i = 0; i < m_iters.size(); ++i) {
		writeLinesAndCirclesForOneIter();
	}
	redraw();
}

void VisualizationWin::writeFlightsBeforeSort()
{
	int x = 0; int y = 60;
	for (int i = 0; i < m_flights_size; ++i) {
		Out_box* out = new Out_box(Point(x, y), 200, 45, "");
		attach(*out);
		string text = m_before[i].destination() + "|" + m_before[i].flight_num() + "|" + m_before[i].departure_time();
		(*out).put(text);
		y += 50;
	}
}
void VisualizationWin::writeSortedFlights()
{
	int x = x_max() - 200; int y = 60;
	for (int i = 0; i < m_flights_size; ++i) {
		Out_box* out = new Out_box(Point(x, y), 200, 40, "");
		attach(*out);
		string text = m_after[i].destination() + "|" + m_after[i].flight_num() + "|" + m_after[i].departure_time();
		(*out).put(text);
		y += 50;
	}
}

void VisualizationWin::deleteAll()
{
	for (int i = 0; i < m_circles.size(); ++i) { detach(*(m_circles[i])); delete m_circles[i]; }
	for (int i = 0; i < m_texts.size(); ++i) { detach(*(m_texts[i])); delete m_texts[i]; }
	for (int i = 0; i < m_lines.size(); ++i) { detach(*(m_lines[i])); delete m_lines[i]; }
	m_circles.clear();
	m_texts.clear();
	m_lines.clear();
	m_curr_iter_index = 1;
}


void VisualizationWin::reset()
{
	deleteAll();
	redraw();
}

void VisualizationWin::previous()
{	
	if (m_curr_iter_index < 2 || m_lines.size() == 0)
		return;

	if (m_texts.size() > 0) {
		detach(*(m_texts[m_texts.size() - 1]));
		m_texts.pop_back();
	}
	int br = 0;
	for (int i = m_lines.size() - 1; i >= 0; --i) {
		detach(*(m_lines[i]));
		detach(*(m_circles[i]));
		delete m_lines[i];
		delete m_circles[i];
		if ((++br) == m_flights_size)
			break;
	}

	for (int i = 0; i < m_flights_size; ++i) {
		m_lines.pop_back();
		m_circles.pop_back();
	}
	--m_curr_iter_index;
	redraw();
}
