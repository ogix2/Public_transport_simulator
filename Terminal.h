#pragma once

#include "Graph.h"

#include <functional>
#include <string>

class Terminal
{
public:
	void start();
	
	static void do_load_graph();
	static void do_print_station();
	static void do_print_line();
	static void do_find_path_v1();
	static void do_find_path_v2();
	static void do_find_path_v3();
};


class Option {
public:
	virtual void start() = 0;
};


class Menu : public Option {
public:
	Menu(string);
	
	void append_option(string, void (*)());
	void append_option(string, Menu*);
	bool is_working();
	
	virtual void start() override;
	
private:
	vector<pair<string, Option*>> menu;
	string begin_text;
	bool work;
};


class Command : public Option {
public:
	Command(void (*function)());
	virtual void start() override;

private:
	void (*function)();
};