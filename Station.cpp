#include "Station.h"

int Station::counter = 0;

Station::Station(int i, string s, bool b) : station_code(i), station_name(s), importance(b) 
{
	this->ID = counter;
	counter++;
}

Station::Station(const string& row)
{
	string first_half, second_half;

	bool mod_first = true;
	for (char i : row)
		if (mod_first)
		{
			if (i == ' ')
				mod_first = false;
			else
				first_half.push_back(i);
		}
		else
		{
			second_half.push_back(i);
		}
	if (mod_first) throw new BadFormatNodeFile();
	int station_code = string_to_int(first_half);


	bool importance = false;
	string end_of_line;
	if (second_half.length() > 4)
		end_of_line = second_half.substr(second_half.length() - 3, 3);
	if (end_of_line == "[!]")
	{
		importance = true;
		second_half = second_half.substr(0, second_half.length() - 4);
	}

	this->importance = importance;
	this->station_code = station_code;
	this->station_name = second_half;

	this->ID = counter;
	counter++;
}

int Station::get_station_code()
{
	return this->station_code;
}

int Station::get_ID()
{
	return this->ID;
}

string Station::get_name()
{
	return this->station_name;
}

bool Station::get_importance()
{
	return this->importance;
}

ostream& operator<<(ostream& os, const Station& station)
{
	os << station.station_code << " " << station.station_name;
	if (station.importance)
		os << " [!]";
	os << endl;
	return os;
}

int Station::string_to_int(const string& number)
{
	int output = 0;
	for (char i : number)
	{
		if (i < '0' || i > '9') throw new BadConversion();
		output = output * 10 + (i - '0');
	}
	return output;
}

