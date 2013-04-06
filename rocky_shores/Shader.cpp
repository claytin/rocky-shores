#include "Shader.h"

Shader::Shader(std::string source, GLenum type){
	shaderId = 0;	//if the shader id is 0 later on there most have been an error
	compiled = false;	//has not yet been succesfully compiled

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

	//compile the shader and output this fact
	Log::status("compiling shader with id: " + shaderId);
	glCompileShader(shaderId);

	//check for compilation errors
	GLint status;	//holds the compilation status
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);	//put the status in status, he he

	if(status == GL_FALSE){
		std::string message = "unable to compile shader with id: " + shaderId;	//the error that will be thrown
		std::string error = "";	//holds opengl error

		//get the error message from opengl (why opengl why does it have to be this way)
		GLint infoLogLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* strInfoLog = new char[infoLogLength + 1];
		glGetShaderInfoLog(shaderId, infoLogLength, NULL, strInfoLog);
		error += strInfoLog;
		delete[] strInfoLog;

		//free the memory being used to hold the shader
		glDeleteShader(shaderId);
		shaderId = 0;

		//throw a shader error with opengl's error message
		message += " opengl returned\"" + error + "\"";
		throw Defaults::Exception(Defaults::SHADER_ERROR, message, __LINE__, __FILE__);
	}

	//if it reached hear then it was probobaly succesfull
	Log::status("shader sucessfully id: " + shaderId);
	compiled = true;
}

Shader::Shader(Shader &_shader){
	glDeleteShader(shaderId);
	shaderId = _shader.shaderId;
}

Shader::~Shader(void){
	glDeleteShader(shaderId);
	shaderId = 0;
	compiled = false;
}

GLuint Shader::getShaderId(void){
	if(compiled){
		return shaderId;
	}

	throw Defaults::Exception(Defaults::SHADER_ERROR, "the shader who's id was requested has not been compiled", __LINE__, __FILE__);
}