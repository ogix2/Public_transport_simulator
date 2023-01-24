#include "Graph.h"

void Graph::read_stations(const string& path)
{
	ifstream myfile(path);
	string line;

	int cnt = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			Station* station = new Station(line);

			if (code_to_station.find(station->get_station_code()) != code_to_station.end()) 
				throw new StationAllreadyExist();

			this->code_to_station[station->get_station_code()] = station;
			this->id_to_station[station->get_ID()] = station;
			this->graf.push_back(list<pair<int, Line*>>());
			cnt++;
		}
	}
	else
		throw new FileDoesntExists();

	this->number_of_stations = cnt;
}

void Graph::read_lines(const string& path)
{
	ifstream myfile(path);
	string line_file;

	if (myfile.is_open())
	{
		while (getline(myfile, line_file))
		{
			Line* line = new Line(line_file, this->code_to_station);	

			if (mark_to_line.find(line->get_name()) != mark_to_line.end())
				throw new LineAllreadyExist();

			this->mark_to_line[line->get_name()] = line;

			make_bounds(line);
		}
	}
	else
		throw new FileDoesntExists();
}

void Graph:: make_bounds(Line* line)
{
	bool inic = true;
	Station* previous_station = nullptr;
	for (Station* curr_station : line->get_stations())
		if (inic)
		{
			previous_station = curr_station;
			inic = false;
		}
		else
		{
			int previous_id = previous_station->get_ID();
			int curr_id = curr_station->get_ID();
			graf[previous_id].push_back({curr_id,line});
			graf[curr_id].push_back({ previous_id,line });

			previous_station = curr_station;
		}
}

void Graph::print_station(int code)
{
 	Station* station = code_to_station[code];

	set<Station*> important_stations;
	set<Line*> lines_through_station;
	
	for (pair<int, Line*> i : graf[station->get_ID()])
	{
		lines_through_station.insert(i.second);

		if (id_to_station[i.first]->get_importance())
			important_stations.insert(id_to_station[i.first]);
	}
	
	
	cout << station->get_station_code() << " " << station->get_name() << " [";
	for (Line* i : lines_through_station)
		cout << i->get_name() << " ";
	cout << "] {! ";
	for (Station* i : important_stations)
		cout << i->get_station_code() << " ";
	cout << "!}\n";
}

void Graph::print_line(string mark)
{
	Line* line = mark_to_line[mark];
	list<Station*> stations = line->get_stations();
	
	cout << line->get_name() << " " << stations.front()->get_name() << "->" << stations.back()->get_name() << endl;

	for (Station* i : stations)
		cout << *i;
}

void Graph::find_path(int code1, int code2)
{
	Station* start_station = code_to_station[code1];
	Station* finish_station = code_to_station[code2];

	vector<pair<int, set<Line*>>> curr_state(number_of_stations,{0,set<Line*>()});
	for (pair<int, Line*> i : graf[start_station->get_ID()])
	{
		curr_state[i.first].first = 1;
		curr_state[i.first].second.insert(i.second);
	}

	curr_state[start_station->get_ID()].first = -1;
	
	bool work = true;
	while (work)
	{
		work = false;
		for (int i = 0; i < number_of_stations; i++) // kroz sve cvorove
			if (curr_state[i].first > 0)	// ako je cvor dostizan	
				for(auto neighbor : graf[i])					//probaj da relaksiras
					if (neighbor.first != start_station->get_ID()) // i - id od cvora preko koga vrsimo relaksaciju, j - id cvora koji relaskiramo
					{
						int j = neighbor.first;
						Line* line = neighbor.second;
						int dodatak = 0;
						
						if (curr_state[i].second.count(line) == 0)
							dodatak++;
						
						if (curr_state[j].first == 0)
						{
							curr_state[j].first = curr_state[i].first + dodatak;
							curr_state[j].second.insert(line);
							
							work = true;
						}
						else if (curr_state[j].first == curr_state[i].first + dodatak)
						{
							if (curr_state[j].second.count(line) == 0)
							{
								work = true;
								curr_state[j].second.insert(line);
							}
						}
						else if (curr_state[j].first > curr_state[i].first + dodatak)
						{
							curr_state[j].first = curr_state[i].first + dodatak;
							curr_state[j].second = set<Line*>();
							curr_state[j].second.insert(line);
							work = true;
						}
					}
	}
	cout << curr_state[finish_station->get_ID()].first << endl;
	for (auto i : curr_state[finish_station->get_ID()].second)
		cout << i->get_name() << "  ";
}

void Graph::find_path_strategy_2(int code1, int code2)
{
	Station* start_station = code_to_station[code1];
	Station* finish_station = code_to_station[code2];

	vector<int> visited(number_of_stations, -1);
	visited[start_station->get_ID()] = 0;

	queue<pair<int, Line*>> stream;
		
	for (auto i : graf[start_station->get_ID()])
	{
		stream.push(i);
		cout << id_to_station[i.first]->get_station_code() << endl;
		visited[i.first] = 1;
	}

	int deepth = 1;
	bool work = true;
	while (work)
	{
		work = false;
		
		while (!stream.empty())
		{
			pair<int, Line*> curr_station = stream.front();
			int curr_station_id = curr_station.first;
			Line* curr_station_line = curr_station.second;
			stream.pop();
			cout << id_to_station[curr_station_id]->get_station_code() << endl;

			for (auto next : graf[curr_station.first])
				if (next.second == curr_station_line)
				{
					if (visited[next.first] == -1)
					{
						visited[next.first] = visited[curr_station_id];
						stream.push(next);
					}
					else if (visited[next.first] == visited[curr_station_id])
					{
						stream.push(next);
					}
				}
		}
		
		deepth++;
		
		for (int i = 0; i < number_of_stations; i++)
			if (visited[i] == deepth)
			{
				for (auto j : graf[i])
					if (visited[j.first] == -1)
					{
						work = true;
						stream.push(j);
						visited[j.first] = deepth;
					}
			}
	}

	cout << visited[finish_station->get_ID()];

}

void Graph::find_path_v3(int code1, int code2)
{
	Station* start_station = code_to_station[code1];
	Station* finish_station = code_to_station[code2];

	vector<int> visited_station(number_of_stations, -1);
	visited_station[start_station->get_ID()] = 0;

	queue<int> stream_station;
	stream_station.push(start_station->get_ID());

	queue<Line*> stream_line;
	set<Line*> visited_line;

	bool work = true;
	int deepth = 0;
	while (work)
	{
		work = false;
		
		while (!stream_station.empty())
		{
			work = true;
			int curr_station = stream_station.front();
			stream_station.pop();
			
			for (pair<int,Line*> i : graf[curr_station])
				if (visited_line.find(i.second) == visited_line.end())
				{
					stream_line.push(i.second);
					visited_line.insert(i.second);
				}
		}
		deepth++;

		while(!stream_line.empty())
		{
			Line* curr_line = stream_line.front();
			stream_line.pop();

			for(Station* station : curr_line->get_stations())
				if (visited_station[station->get_ID()] == -1)
				{
					stream_station.push(station->get_ID());
					visited_station[station->get_ID()] = deepth;
				}
		}
	}
	
	for (int i = 0; i < number_of_stations; i++)
		cout << id_to_station[i]->get_station_code() << " : " << visited_station[i] << endl;

	cout << "\n\n";
	find_trace(start_station, finish_station, visited_station);
}

void Graph::find_trace(Station* start_station, Station* finish_station, const vector<int>& visited)
{
	Station* curr_station_start = finish_station;
	stack<pair<Station*, Station*>> stack_station;
	stack<Line*> stack_line;
	
	while (visited[curr_station_start->get_ID()] > 0)
	{
		pair <Station*, Line* > tmp = find_trace_single_line(curr_station_start, visited);
		Station* curr_station_finish = tmp.first;
		Line* line = tmp.second;

		stack_station.push({ curr_station_start,curr_station_finish });
		stack_line.push(line);

		curr_station_start = curr_station_finish;
	}

	print_trace(stack_station, stack_line);
}

pair<Station*,Line*> Graph::find_trace_single_line(Station* station, const vector<int>& visited)
{
	int curr_deepth = visited[station->get_ID()];

	set<Line*> lines;
	for (auto i : graf[station->get_ID()])
		lines.insert(i.second);

	for (Line* line : lines)
	{
		for (Station* station : line->get_stations())
			if (visited[station->get_ID()] == curr_deepth - 1)
			{
				return { station,line };
			}
	}
}

void Graph::print_trace(stack<pair<Station*, Station*>>& stack_station,stack<Line*>& stack_line)
{
	bool inic = true;
	Line* last_line = nullptr;

	while (!stack_station.empty())
	{
		Station* start_station = stack_station.top().second;
		Station* finish_station = stack_station.top().first;
		Line* line = stack_line.top();

		stack_station.pop();
		stack_line.pop();

		if (inic)
		{
			cout << "->" << line->get_name() << endl;
			inic = false;
			last_line = line;
		}
		else
		{
			cout << last_line->get_name() << "->" << line->get_name() << endl;
			last_line = line;
		}
		

		int mod = -1;
		for (Station* curr_station : line->get_stations())
		{
			if (curr_station->get_ID() == start_station->get_ID())
			{
				mod = 1;
				break;
			}
			if (curr_station->get_ID() == finish_station->get_ID())
			{
				mod = 2;
				break;
			}
		}

		vector<Station*> out;
		if (mod == 1)
		{
			bool flag = false;
			for (Station* curr_station : line->get_stations())
			{
				if (curr_station->get_ID() == start_station->get_ID())
					flag = true;

				if (flag == true)
					out.push_back(curr_station);

				if (curr_station->get_ID() == finish_station->get_ID())
					flag = false;
			}

			for (int i = 0; i < out.size(); i++)
				if (i != out.size() - 1)
					cout << out[i]->get_station_code() << " ";
				else
					cout << out[i]->get_station_code() << endl;
		}
		if (mod == 2)
		{
			bool flag = false;
			for (Station* curr_station : line->get_stations())
			{
				if (curr_station->get_ID() == finish_station->get_ID())
					flag = true;

				if (flag == true)
					out.push_back(curr_station);

				if (curr_station->get_ID() == start_station->get_ID())
					flag = false;
			}

			for (int i = out.size() - 1; i>= 0; i--)
				if (i != 0)
					cout << out[i]->get_station_code() << " ";
				else
					cout << out[i]->get_station_code() << endl;
		}

	}
}

list<Station*> Graph::important_stations_connected(Station* station)
{
	int start_id = station->get_ID();

	list<Station*> important_stations;
	
	vector<bool> visited(number_of_stations, false);
	visited[start_id] = true;
	queue<int> stream;
	stream.push(start_id);

	while (!stream.empty())
	{
		int curr_id = stream.front();
		cout << curr_id << endl;
		stream.pop();

		for (pair<int,Line*> i : graf[curr_id])
			if (visited[i.first] == false)
			{
				if (id_to_station[i.first]->get_importance())
					important_stations.push_back(id_to_station[i.first]);

				stream.push(i.first);
				visited[i.first] = true;
			}
	}

	return important_stations;
}

