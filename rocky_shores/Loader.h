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
#include <iostream>
#include "Defaults.h"
#include <gl\glew.h>
#include <gl\glfw.h>
#include "Log.h"
#include <png.h>

class Loader{
public:
	Loader(void);
	~Loader(void);

	void loadRes(std::string path) throw (Defaults::Exception);    //load a .res file (file that lists resourses) and load each

	void loadTga(std::string path) throw (Defaults::Exception);    //load a tga and put it in the loader texture map
	static void loadTga(std::string path, GLuint * index) throw (Defaults::Exception);    //load a tga file and puts its index in the second param

	void loadBmp(std::string path) throw (Defaults::Exception);    //load a bmp image file into opengl and add its index to the texture list
	static void loadBmp(std::string path, GLuint * index) throw (Defaults::Exception);	//load a bmp image into opengl and set var index to its index

	void loadGif(std::string path) throw (Defaults::Exception);    //load gif put it in textures list
	static void loadGif(std::string path, GLuint * index) throw (Defaults::Exception);    //load gif

	void loadPng(std::string path) throw (Defaults::Exception);    //load png texture and put it in textures
	static void loadPng(std::string path, GLuint * index) throw (Defaults::Exception);    //load png

	static void loadVertexShader(std::string path, GLuint * index) throw (Defaults::Exception);    //load a vertex shader and compile it put its index/id in var index
	static void loadFragmentShader(std::string path, GLuint * index) throw (Defaults::Exception);	//load a fragment shader and compile it
	static void loadShader(std::string vertexShader, std::string fragmentShader, GLuint * programId) throw (Defaults::Exception);    //load and link both shaders and return id of the program
	static void linkShader(GLuint vertexShaderProgramId, GLuint fragmentShaderProgramId, GLuint * linkedProgramId) throw (Defaults::Exception);    //link a vertex and fragment opengl compile shader
	static std::string stringFromFile(std::string path);    //load any file into a std::string container

	void setMipmap(GLenum min, GLenum max);    //sets the mipmap for all textures loaded

private:
	std::map<std::string, GLuint> textures;
};

