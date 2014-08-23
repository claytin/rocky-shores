//ShaderProgram.h / ShaderProgram.cpp
//holds a number of linked shaders that can be used as a program
//it also returns the intex of attribute and uniform variables
//-mgc480

#pragma once
#include "Shader.h"
#include <vector>

class ShaderProgram{

public:
	ShaderProgram(std::vector<Shader*> shaders);    //takes a vector of shaders that will be compiled into single program
	~ShaderProgram(void);	//deletes the shader program, this makes the shader program reliant on keeping this object alive (don't delete this unless you don't need the shader program)

	GLuint attrib(std::string attributeName);	//gives the attribute index for the give name
	GLuint uniform(std::string uniformName);	//gives the uniform index for the given name

	GLuint getProgramId(void);	//returns the programId if it was compiled

private:
	GLuint programId;
	bool compiled;
};