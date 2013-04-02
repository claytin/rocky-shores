#pragma once
#include <string>
#include <iostream>
#include <GL\glew.h>
#include "Defaults.h"

class Shader{

public:
	Shader(std::string shaderSource, GLenum shaderType) throw (Defaults::Exception);
	~Shader(void);

private:
	GLuint shaderId;
};