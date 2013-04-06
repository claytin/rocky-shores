#pragma once
#include <string>
#include <iostream>
#include <GL\glew.h>
#include "Defaults.h"
#include "Log.h"

class Shader{

public:
	Shader(std::string shaderSource, GLenum shaderType) throw (Defaults::Exception);	//will compile the shader and use shader id
	Shader(Shader &anotherShader);	//sets itself as the shader given
	Shader(void){	//just sets compiled to false because it was never compiled
		compiled = false;
	}
	~Shader(void);	//just deletes the shader thast stored in shader id and sets compiled to false

	GLuint getShaderId(void) throw (Defaults::Exception);	//returns the shaders id if compiled otherwise it will through am error

private:
	GLuint shaderId;
	bool compiled;
};