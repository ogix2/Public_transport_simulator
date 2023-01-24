#pragma once

#include <map>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <queue>
#include <set>
#include <stack>

#include "Exceptions.h"
#include "Station.h"
#include "Line.h"

using namespace std;

class Graph
{
public:
	void read_stations(const string& path);
	void read_lines(const string& path);
	void make_bounds(Line* line);

	void print_station(int code);
	void print_line(string mark);

	void find_path(int code1, int code2);
	void find_path_strategy_2(int code1, int code2);
	
	void find_path_v3(int code1, int code2);
	
	void find_trace(Station* start_station, Station* finish_station, const vector<int>& visited);
	pair<Station*,Line*> find_trace_single_line(Station* station, const vector<int>& visited);
	void print_trace(stack<pair<Station*, Station*>>& stack_station, stack<Line*>& stack_line);

	list<Station*> important_stations_connected(Station* station);


private:
	int number_of_stations;

	map<int, Station*> id_to_station;
	map<int, Station*> code_to_station;
	
	map<string, Line*> mark_to_line;
	
	vector <list<pair<int, Line*>> > graf;
};

