#pragma once
#include "Shader.h"
#include <vector>

class ShaderProgram{

public:
	ShaderProgram(std::vector<Shader> shaders) throw (Defaults::Exception);    //takes a vector of shaders that will be compiled into single program
	~ShaderProgram(void);

private:
	GLuint programId;
	bool compiled;
};