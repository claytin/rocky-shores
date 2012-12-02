#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "Defaults.h"

class Loader{
public:
	Loader(void);
	~Loader(void);

	Defaults::Status loadRes(std::string path);	//load a .res file (file that lists resourses) and load each
};

