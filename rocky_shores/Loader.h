//Loader.h / Loader.cpp
//used as a universal loading system to loader every file type
//-mgc480

#pragma once
#include <map>
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

	Defaults::Status loadTga(std::string path);    //load a tga and put it in the loader texture map
	static Defaults::Status loadTga(std::string path, GLuint * index);    //load a tga file and puts its index in the second param

	void setMipmap(GLenum min, GLenum max);    //sets the mipmap for all textures loaded

private:
	std::map<std::string, GLuint> textures;

	//static GLenum minFilter, maxFilter;

};

