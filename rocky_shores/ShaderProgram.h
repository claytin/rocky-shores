#pragma once
#include "Shader.h"
#include <vector>

class ShaderProgram{

public:
	ShaderProgram(std::vector<Shader> shaders);    //takes a vector of shaders that will be compiled into single program
	~ShaderProgram(void);
};