//Shader.h / Shader.cpp
//holds a (posibly compiled) shader and can be linked into a shaderProgram
//-mgc480

#pragma once
#include <string>
#include <iostream>
#include <GL/glew.h>
#include "Defaults.h"
#include <sstream>
#include "Log.h"
#include <iostream>

class Shader{

public:
	Shader(std::string shaderSource, GLenum shaderType);	//will compile the shader and use shader id
	Shader(void){	//just sets compiled to false because it was never compiled
		compiled = false;
	}
	~Shader(void);	//just deletes the shader thast stored in shader id and sets compiled to false

	GLuint getShaderId(void);	//returns the shaders id if compiled otherwise it will through am error

	static void compile(std::string shaderSource, GLenum shaderType, GLuint * shaderToReturn);
	void compile(std::string shaderSource, GLenum shaderType);

private:
	GLuint shaderId;
	bool compiled;
};