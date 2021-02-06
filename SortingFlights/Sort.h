//============================================================================
// Name        : Sort.h
// Author      : Rajko Zagorac
// Date        :
// Copyright   : 
// Description : Sort interface class and various sorting algorithms in C++
//============================================================================
#pragma once

#include "Flight.h"
#include <vector>
#include "Criterion.h"
#include <unordered_map>



// zamenjuje dva elementa
void swap_flights(Flight& f1, Flight& f2);

// broji broj inverzija na kraju odredjene iteracije
// kao ulazan parametar je primljenja mapa pozicija nakon iteracije
int get_num_of_swaps(std::unordered_map<int, int>& mapa);

// resetuj mapu pozicija da bi bila spremna za sledecu iteraciju
void resetMapOfIndexesBeforeIter(std::unordered_map<int, int>& mapa, int size);

// sacuvaj pocetne indekse letova pre iteracije tako da se ne izgube prilikom sortiranja
void saveInitialIndexesOfFlightsBeforeIter(std::vector<Flight>& data);



// klasa koja cuva podatke za vreme iteracije
// najvazniji atribut je mapa indeksa oblika:
//     a : b
// gde je a indeks elementa pre sortiranja a b posle
// ovo posle koristim da bi znao kako da crtam vizualizaciju i pratim elemente
class IterationData {
	std::unordered_map<int, int> m_map;
	// ukupan broj inverzija na kraju iteracije
	int m_num_swaps;
	// ukupan broj poredjenja za vreme iteracije;
	int m_num_cmps;
public:
	IterationData(std::unordered_map<int, int>& map, int num_of_switches, int num_cmps);
	inline std::unordered_map<int, int> mapa() const { return m_map; }
	inline int num_swaps() const { return m_num_swaps; }
	inline int num_cmps() const { return m_num_cmps; }
};



// Sort class
class Sort
{
protected:
	// number of comparisons performed in sort function
	unsigned long num_cmps;

	// vektor podataka o svim iteracijama popunjavam ga za vreme sortiranja
	std::vector<IterationData>m_iterations;
public:
	// main entry point
	virtual void sort(std::vector<Flight>& data, Criterion criterion) = 0;
	// returns number of comparisons
	unsigned long getNumCmps();
	// resets the number of comparisons
	void resetNumCmps();
	inline std::vector<IterationData> iterations() const { return m_iterations; }
};


// SelectionSort class
class SelectionSort : public Sort
{
public:
	// sortiran podatke po zadatom kriterijumu
	void sort(std::vector<Flight>& data, Criterion criterion);
};


class MergeSort : public Sort
{
public:
	// funkcija merge sorta
	// pravi novi sortirani niz od dva podniza koja cupa pomocu left, min, right indeksa
	// prilikom spajanja azurira se mapa trenutne iteracije, tako da se posle zna ko je promenio mesto i gde
	void merge(std::vector<Flight>& data, std::unordered_map<int, int>& mapa,
				Criterion criterion, int left_a, int mid, int right_b);
	// sortiran podatke po zadatom kriterijumu
	void sort(std::vector<Flight>& data, Criterion criterion);
};
