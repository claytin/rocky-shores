//Loader.h / Loader.cpp
//used as a universal loading system to loader every file type
//-mgc480

#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "Defaults.h"
#include <gl\glew.h>
#include <gl\glfw.h>

class Loader{
public:
	Loader(void);
	~Loader(void);

	Defaults::Status loadRes(std::string path);    //load a .res file (file that lists resourses) and load each

private:
	
	//std::vector<int> audio;    //where the audio track index is hel
};

