#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class Loader{
public:
	enum status{GOOD, FILE_NOT_FOUND, FILE_CORRUPT, OUT_OF_MEMORY, UNKNOWN_ERROR};

	Loader(void);
	~Loader(void);

	status loadRes(std::string path);	//load a .res file (file that lists resourses) and load each
};

