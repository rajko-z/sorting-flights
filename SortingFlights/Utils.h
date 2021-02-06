// modul sadrzi prvenstevno pomocne funkcije za icrtavanje
// kako u konzolu tako i u fajl

#pragma once
#include <vector>
#include "Flight.h"
#include "Sort.h"
#include <iostream>
#include "MyWindow.h"
#include <string>


void printHeder(std::ostream& os);
void printFlights(std::ostream& os, std::vector<Flight>& data);

 // return -1 ako je prvi raniji, i 1 ako je drugi, 0 ako su jednaki
int compareTime(std::string time1, std::string time2);

// vraca tokene koje dalje korist compareTime funkcija
std::vector<int> parseTime(std::string time);

// ispisuje podatke u formi tabele kroz sve iteracije
void printTableThroughItererations(std::ostream& os, std::vector<IterationData>iterations);

// ispisuje podatke ukupno za sve iteracije, bez postupnosti
void printFinalStatsAfterIterations(std::ostream& os, std::vector<IterationData>iterations);

// trim i sa pocetka i sa kraja, koristim je ako se ucitaju razmaci iz fajla
void trimString(std::string& str);
