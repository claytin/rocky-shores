#include "Shader.h"

Shader::Shader(std::string source, GLenum type){
	if(source == ""){
		throw Defaults::Exception(Defaults::INVALID_STRING, "the source given for the shader was invalid");
	}
}

Shader::~Shader(void){

}