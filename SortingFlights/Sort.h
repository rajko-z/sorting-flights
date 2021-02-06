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


void swap_flights(Flight& f1, Flight& f2);

int get_num_of_swaps(std::unordered_map<int, int>& mapa);

void resetMapOfIndexesBeforeIter(std::unordered_map<int, int>& mapa, int size);

void saveInitialIndexesOfFlightsBeforeIter(std::vector<Flight>& data);



class IterationData {
	std::unordered_map<int, int> m_map;
	int m_num_swaps;
	int m_num_cmps;
public:
	IterationData(std::unordered_map<int, int>& map, int num_of_switches, int num_cmps);
	inline std::unordered_map<int, int> mapa() const { return m_map; }
	inline int num_swaps() const { return m_num_swaps; }
	inline int num_cmps() const { return m_num_cmps; }
};


class Sort
{
protected:
	unsigned long num_cmps;

	std::vector<IterationData>m_iterations;
public:
	virtual void sort(std::vector<Flight>& data, Criterion criterion) = 0;
	unsigned long getNumCmps();
	void resetNumCmps();
	inline std::vector<IterationData> iterations() const { return m_iterations; }
};


class SelectionSort : public Sort
{
public:
	void sort(std::vector<Flight>& data, Criterion criterion);
};


class MergeSort : public Sort
{
public:
	void merge(std::vector<Flight>& data, std::unordered_map<int, int>& mapa,
				Criterion criterion, int left_a, int mid, int right_b);
	void sort(std::vector<Flight>& data, Criterion criterion);
};
