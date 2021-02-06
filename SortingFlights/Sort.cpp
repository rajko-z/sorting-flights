//============================================================================
// Name        : Sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of the sort classes
//============================================================================

#include "Sort.h"
#include "string.h"
#include "Utils.h"
#include <unordered_map>

using namespace std;


//----------------------------------------------------------
void Sort::resetNumCmps() { num_cmps = 0; }
unsigned long Sort::getNumCmps() { return num_cmps; }

//-------------------------------------------

void swap_flights(Flight& f1, Flight& f2)
{
	Flight temp = f1;
	f1 = f2;
	f2 = temp;
}

int get_num_of_swaps(unordered_map<int, int>& mapa) {
	int num_of_swaps = 0;
	for (auto& it : mapa) {
		if (it.first != it.second)
			++num_of_swaps;
	}
	return num_of_swaps;
}

void saveInitialIndexesOfFlightsBeforeIter(vector<Flight>& data)
{
	for (int i = 0; i < data.size(); i++) {
		data[i]._index = i;
	}
}

void resetMapOfIndexesBeforeIter(unordered_map<int, int>& mapa, int size)
{
	for (int i = 0; i < size; i++) {
		mapa[i] = i;
	}
}
//==================================================



IterationData::IterationData(unordered_map<int, int>& map, int num_of_swaps, int num_cmps) :
	m_map(map),
	m_num_swaps(num_of_swaps),
	m_num_cmps(num_cmps) {}


void SelectionSort::sort(vector<Flight>& data, Criterion criterion)
{	
	unordered_map<int, int>mapa;
	resetMapOfIndexesBeforeIter(mapa, data.size());

	for (int i = 0; i < data.size() - 1; i++) {
		
		saveInitialIndexesOfFlightsBeforeIter(data);
		resetMapOfIndexesBeforeIter(mapa, data.size());
		resetNumCmps();

		for (int j = i + 1; j < data.size(); j++) {
			++num_cmps;
			if (data[i].compareTo(data[j], criterion) > 0) {
				mapa[data[i]._index] = j;
				mapa[data[j]._index] = i;
				swap_flights(data[i], data[j]);
			}
		}
		m_iterations.push_back(IterationData(mapa, get_num_of_swaps(mapa), num_cmps));
	}
}

void MergeSort::sort(vector<Flight>& data, Criterion criterion)
{
	int right = data.size() - 1;
	unordered_map<int, int>mapa;
	resetMapOfIndexesBeforeIter(mapa, data.size());

	for (int i = 1; i <= right; i = 2 * i)
	{
		saveInitialIndexesOfFlightsBeforeIter(data);
		resetMapOfIndexesBeforeIter(mapa, data.size());
		resetNumCmps();

		for (int j = 0; j < right; j += 2 * i)
		{
			int mid = min(j + i - 1, right);
			int right_b = min(j + 2 * i - 1, right);
			merge(data, mapa, criterion, j, mid, right_b);
		}
		m_iterations.push_back(IterationData(mapa, get_num_of_swaps(mapa), num_cmps));
	}
}


void MergeSort::merge(vector<Flight>& data, unordered_map<int,int>& mapa,
					Criterion criterion,int left_a, int mid, int right_b)
{
	int lsize = (mid - left_a) + 1;
	int rsize = right_b - mid;

	vector<Flight>left;
	vector<Flight>right;
	vector<Flight>copyVec = data;

	for (int i = 0; i < lsize; ++i) {
		left.push_back(data[left_a + i]);
	}
	for (int i = 0; i < rsize; i++) {
		right.push_back(data[mid + 1 + i]);
	}

	int i = 0, j = 0, br = left_a;
	while (i < lsize && j < rsize) {
		if (left[i].compareTo(right[j], criterion) <= 0) {
			mapa[data[i + left_a]._index] = br;
			copyVec[br] = left[i];
			i++;
		}
		else {
			mapa[data[j + mid + 1]._index] = br;
			copyVec[br] = right[j];
			j++;
		}
		br++;
		++num_cmps;
	}

	for (int k = i; k < lsize; k++) {
		mapa[data[k + left_a]._index] = br;
		copyVec[br] = left[k];
		br++;
		++num_cmps;
	}
	for (int k = j; k < rsize; k++) {
		mapa[data[k + mid + 1]._index] = br;
		copyVec[br] = right[k];
		br++;
		++num_cmps;
	}
	for (int i = 0; i < copyVec.size(); i++) {
		data[i] = copyVec[i];
	}
}