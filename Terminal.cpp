#include "Terminal.h"


void Terminal::start()
{	
	Menu* menu3 = new Menu("Pronalazim put");
	menu3->append_option("Strategija_1", do_find_path_v1);
	menu3->append_option("Strategija_2", do_find_path_v2);
	menu3->append_option("Strategija_3", do_find_path_v3);
	
	Menu* menu2 = new Menu("Mreza gradskog prevoza je uspesno ucitana. Molimo Vas, odaberite opciju:");
	menu2->append_option("Prikaz informacija o stajalistu",do_print_station);
	menu2->append_option("Prikaz informacija o liniji gradskog prevoza",do_print_station);
	menu2->append_option("Pronalazak putanje izmedju dva stajalista",menu3);
	
	Menu* menu1 = new Menu("Dobrodosli u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju:");
	menu1->append_option("Ucitavanje podataka o mrezi gradskog prevoza", do_load_graph);

	bool inic = false;
	bool work = true;
	while (work)
	{
		if (!inic)
		{
			menu1->start();
			work = menu1->is_working();
			inic = true;
		}
		else
		{
			menu2->start();
			work = menu2->is_working();
		}
		cout << endl;
	}
}

void Terminal::do_load_graph()
{
	cout << "Molimo Vas, unesite putanju do fajla sa stajalištima ili kliknite ENTER za učitavanje podrazumevanog fajla(ulazi / stajalista.txt) :" << endl;
	string path;
	cin >> path;
	if (path == "")


}

void Terminal::do_print_station()
{
}

void Terminal::do_print_line()
{
}

void Terminal::do_find_path_v1()
{
}

void Terminal::do_find_path_v2()
{
}

void Terminal::do_find_path_v3()
{
}


Menu::Menu(string text) : begin_text(text), work(true) {}

void Menu::append_option(string option_text, void(* function )())
{
	Command* command = new Command(function);
	
	menu.push_back({ option_text,command });
}

void Menu::append_option(string option_text, Menu* menu)
{
	this->menu.push_back({ option_text,menu });
}

bool Menu::is_working()
{
	return this->work;
}

void Menu::start()
{
	cout << begin_text << endl;
	for (int i = 0; i < menu.size(); i++)
	{
		cout << i + 1 << ". " << menu[i].first << endl;
	}
	cout << "0. Kraj rada" << endl;

	int option;
	cin >> option;

	if (option < 0 || option > menu.size())
	{
		cout << "Nepostojeca opcija." << endl;
		return;
	}

	if (option == 0)
	{
		work = false;
		return;
	}

	menu[option - 1].second->start();
}

Command::Command(void(*function)())
{
	this->function = function;
}

void Command::start()
{
	this->function();
}
