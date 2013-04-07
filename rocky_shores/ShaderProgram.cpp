#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::vector<Shader> shaders){
	//there needs to be at least one shader in the shaders list/ vector
	if(shaders.size() <= 0){
		throw Defaults::Exception(Defaults::SHADER_ERROR, "the list of shaders to be compiled needs to have at least one shader", __LINE__, __FILE__);
	}

	programId = glCreateProgram();
	if(programId == GL_FALSE){
		throw Defaults::Exception(Defaults::SHADER_ERROR, "unable to create shader program", __LINE__, __FILE__);
	}

	for(unsigned int i = 0; i < shaders.size(); i++){
		try{
			glDetachShader(programId, shaders[i].getShaderId());
		}catch(Defaults::Exception e){
			throw e;
		}
	}


}

ShaderProgram::~ShaderProgram(void){

}