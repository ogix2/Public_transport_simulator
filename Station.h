#pragma once

#include <string>
#include <iostream>

#include "Exceptions.h"

using namespace std;

class Station
{
public:
	Station(int station_code,string station_name,bool importance);
	Station(const string& row);

	friend ostream& operator<<(ostream& os,const Station& station);

	int get_station_code();
	int get_ID();
	string get_name();
	bool get_importance();

private:
	int station_code, ID;
	string station_name;
	bool importance;

	static int counter;

	static int string_to_int(const string& number);
};

