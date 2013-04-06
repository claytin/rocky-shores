#include "Shader.h"

Shader::Shader(std::string source, GLenum type){
	shaderId = 0;	//if the shader id is 0 later on there most have been an error

	//make sure the source actually contains something
	if(source == ""){
		throw Defaults::Exception(Defaults::INVALID_STRING, "the source given for the shader was invalid (it's blank )");
	}

	//create object and check if it was created
	shaderId = glCreateShader(type);
	if(shaderId == 0){
		throw Defaults::Exception(Defaults::SHADER_ERROR, "could not create a shader object", __LINE__, __FILE__);
	}

	//set the source of the shader
	const char* code = source.c_str();
	glShaderSource(shaderId, 1, (const GLchar**)&code, NULL);

	//yeah you know what this does, i hope
	glCompileShader(shaderId);

	//check for compilation errors
	GLint status;	//holds the compilation status
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);	//put the status in status, he he

	if(status == GL_FALSE){

	}
}

Shader::~Shader(void){

}