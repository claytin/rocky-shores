//Setup.h / Setup.cpp
//initalizes opengl and sets up window
//this class acts as the temporary renderer while loading files and is used to catch
//errors / display graphic while loading primary resources
//-mgc480

#pragma once
#include <gl\glew.h>
#include <GL\glfw.h>
#include "Log.h"
#include <sstream>
#include "Loader.h"

class Setup{

public:
	Setup(void);
	~Setup(void);

	//takes width and height of window to be crated
	void display(int widht, int height);	//this will use glew for opengl and make sure the computer meets requirments
	void initialLoad(std::string resfilePath);	//used to display first loading screen and load important

private:
	Log log;
};

