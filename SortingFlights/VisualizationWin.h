#pragma once
#include "Graph.h"
#include "Window.h"
#include "GUI.h"
#include <vector>
#include "Flight.h"
#include "Sort.h"

using namespace Graph_lib;

// klasa koja je odgovorna za glavnu simulaciju testiranja
// nasledjuje Window klasu i implentira korisnicku spregu
// ulazni parametri: vektor letova pre sortiranja
//                   vektor sortiranih letova
//                   informacije o iteracijama za vreme sortiranja isto u obliku vektora
class VisualizationWin : public Window {
public:
	VisualizationWin(Point xy, int w, int h, const string& title, std::vector<Flight>& before,
		std::vector<Flight>& after, std::vector<IterationData>& iters);

	// ispisuje vertikalne krugove za jednu iteraciju
	void writeVerticalCircles(int index);

	// ispisuje letove pre sortiranja, to ce biti na levoj strani
	void writeFlightsBeforeSort();

	// ispisuje sortirane letove na desnoj strani
	void writeSortedFlights();

	// ispisuje potrebne linije i krugove za jednu iteraciju
	void writeLinesAndCirclesForOneIter();

	// brise ceo sadrzaj ispisa linija sortiranja i krugova
	// koriste je i full i reset funkcija
	void deleteAll();

private:

	// pokazuje mi koja je iteracija na redu da se izvrsi
	int m_curr_iter_index = 1;
	
	int m_flights_size;

	// ukupna sirina prostora na koje mogu da crtam iteraciju
	int m_max_width_sort;

	// sirina jednog podeoka, razlike izmedju dve iteracije
	int m_width_sort;

	// pocetna tacka od koje dalje crtam druge tacke 
	int m_x_begin;
	int m_y_begin;

	std::vector<Flight>m_before;
	std::vector<Flight>m_after;
	std::vector<IterationData>m_iters;

	std::vector<Circle*>m_circles;
	std::vector<Text*>m_texts;
	std::vector<Line*>m_lines;

	// poziva full(), iscrtava celu simulaciju bez koraka
	Button full_button;
	
	// poziva next(), iscrtava sledecu iteraciju
	Button next_button;

	// poziva previous(), brise sadasnju iteraciju i vraca se jedan korak u nazad
	// fakticki pomocu ovoga mogu da se setam i nazad kroz iteracije
	Button previous_button;

	// poiza reset(), brise sadrzaj svih iteracija, tako da mogu ponovo
	// postupno da ih crtam ukoliko zelim
	Button reset_button;

	void full();
	void next();
	void previous();
	void reset();
};