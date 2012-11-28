//Setup.h - initalizes opengl and sets up window
//this class acts as the temporary renderer while loading files and is used to catch
//errors / display graphic while loading primary resources
//-mgc480

#pragma once
#include <gl\glew.h>
#include <GL\glfw.h>
#include "Log.h"
#include <sstream>



class Setup{

public:
	Setup(void);
	~Setup(void);

	void opengl(void);	//this will use glew for opengl and make sure the computer meets requirments
};

