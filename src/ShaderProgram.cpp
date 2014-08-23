#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::vector<Shader*> _shaders){
	//there needs to be at least one shader in the shaders list/ vector
	if(_shaders.size() <= 0){	//but what if there where -1 shaders...
		throw Defaults::Exception(Defaults::SHADER_ERROR, "the list of shaders to be compiled needs to have at least one shader", __LINE__, __FILE__);
	}

	//create the program and make sure it was created
	programId = glCreateProgram();
	if(programId == GL_FALSE){
		throw Defaults::Exception(Defaults::SHADER_ERROR, "unable to create shader program", __LINE__, __FILE__);
	}

	Log::startBlock("creating shader program ");

	//add the the shaders to this program
	for(unsigned int i = 0; i < _shaders.size(); i++){
		std::ostringstream oss;
		oss << _shaders[i]->getShaderId();
		Log::status("adding shader with id: " + oss.str());

		glAttachShader(programId, _shaders[i]->getShaderId());
	}

	//link all the individual shaders together
	Log::status("linking program");
	glLinkProgram(programId);

	//now that they have been linked you can remove the shaders
	for(unsigned int i = 0; i < _shaders.size(); i++){
		glDetachShader(programId, _shaders[i]->getShaderId());
	}

	//check to make sure all went well
	GLint status;
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	if(status == GL_FALSE){
		std::ostringstream oss;
		oss << programId;
		std::string message = "unable to link shaders and create a program with id: " + oss.str();	//the error that will be thrown
		std::ostringstream error;;	//holds opengl error

		//get the error message from opengl (why opengl why does it have to be this way)
		GLint infoLogLength;
		glGetShaderiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* strInfoLog = new char[infoLogLength + 1];
		glGetShaderInfoLog(programId, infoLogLength, NULL, strInfoLog);
		error << strInfoLog;
		delete[] strInfoLog;

		//free the memory being used to hold the shader
		glDeleteShader(programId);
		programId = 0;
		//throw a shader error with opengl's error message
		message += " opengl returned \"" + error.str() + "\" ";
		std::cout << "tst " + message + "\n";
		throw Defaults::Exception(Defaults::SHADER_ERROR, message, __LINE__, __FILE__);
	}

	//if it reached here it must have been succesful
	compiled = true;
}

ShaderProgram::~ShaderProgram(void){
	glDeleteProgram(programId);	//if this object is deleted then the shader  is deleted as well
}

GLuint ShaderProgram::getProgramId(void){
	if(compiled){
		return programId;
	}

	throw Defaults::Exception(Defaults::SHADER_ERROR, "the requested program was not compiled", __LINE__, __FILE__);
}

GLuint ShaderProgram::attrib(std::string _attrib){
	GLint attrib = 0;
	const GLchar * attribAsChar = _attrib.c_str();

	attrib = glGetAttribLocation(programId, attribAsChar);

	if(attrib == -1){
		throw Defaults::Exception(Defaults::SHADER_ERROR, "the requested attribute was not found \"" + _attrib + "\"");
	}

	return attrib;
}

GLuint ShaderProgram::uniform(std::string _uniform){
	GLint uniform = 0;
	const GLchar * uniformAsChar = _uniform.c_str();

	uniform = glGetUniformLocation(programId, uniformAsChar);

	if(uniform == -1){
		throw Defaults::Exception(Defaults::SHADER_ERROR, "the requested unifrom was not found \"" + _uniform + "\"");
	}

	return uniform;
}
