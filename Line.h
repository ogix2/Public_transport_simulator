#pragma once

#include <string>
#include <map>
#include <list>

#include "Exceptions.h"
#include "Station.h"

using namespace std;

/*
	Pretpostavka da je sifra linija jedan rec;
	Pretpostavljeni format reda:
	string int int
	moze vise intova ali dva je minimum
*/

class Line
{
public:
	Line(const string& row, map<int, Station*>& code_to_station);	// fali provera ciklicnosti i da li postoji u mapi

	string get_name();
	list<Station*> get_stations();

private:
	string line_name;
	list<Station*> stations;

	static int string_to_int(const string& number);
	static list<string> split(const string& str);
};

