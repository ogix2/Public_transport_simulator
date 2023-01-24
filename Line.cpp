#include "Line.h"

Line::Line(const string& row, map<int, Station*>& code_to_station)
{
	list<string> input_list = split(row);
	if (input_list.size() < 3) throw new BadFormatLineFile();

	bool inic = true;
	for (string i : input_list)
		if (inic)
		{
			line_name = i;
			inic = false;
		}
		else
		{
			stations.push_back(code_to_station[string_to_int(i)]);
		}
}

string Line::get_name()
{
	return this->line_name;
}

list<Station*> Line::get_stations()
{
	return this->stations;
}

int Line::string_to_int(const string& number)
{
	int output = 0;
	for (char i : number)
	{
		if (i < '0' || i > '9') throw new BadConversion();
		output = output * 10 + (i - '0');
	}
	return output;
}

list<string> Line::split(const string& str)
{
	if (str[str.length() - 1] == ' ') throw new BadFormatLineFile();	
	
	list<string> output;
	
	int cnt_i = 0;	// counter
	int cnt_j = 0;
	for (char i : str)
		if (i == ' ')
		{
			if (cnt_i == cnt_j) throw new BadFormatLineFile();
			output.push_back(str.substr(cnt_i, cnt_j - cnt_i));
			cnt_j++;
			cnt_i = cnt_j;
		}
		else
		{ 
			cnt_j++;
		}
	
	output.push_back(str.substr(cnt_i, cnt_j - cnt_i));
	
	return output;
}
