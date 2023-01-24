#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

using namespace std;

class FileDoesntExists : public exception {
public:
	FileDoesntExists() : exception("File doesnt exists.\n") {};
};

class BadConversion : public exception {
public:
	BadConversion() : exception("Can not convert string with letters to int.\n") {};
};

class BadFormatNodeFile : public exception {
public:
	BadFormatNodeFile() : exception("Bad format of station input file.\n") {};
};

class BadFormatLineFile : public exception {
public:
	BadFormatLineFile() : exception("Bad format of line input file.\n") {};
};

class StationAllreadyExist : public exception {
public:
	StationAllreadyExist() : exception("Station allready exist.\n") {};
};

class LineAllreadyExist : public exception {
public:
	LineAllreadyExist() : exception("Line allready exist.\n") {};
};

#endif