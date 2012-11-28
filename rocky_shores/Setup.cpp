#define GLEW_STATIC
#include "Setup.h"

Setup::Setup(void){

}

Setup::~Setup(void){

}

void Setup::opengl(void){
	Log log;

	if(!glfwInit()){
		log.error("cannot initialize glfw", __LINE__, __FILE__);
	}
	log.status("glfw initialized");

	if(!glfwOpenWindow(1024, 768, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)){
		log.error("cannot create glfw window", __LINE__, __FILE__);
	}
	log.status("glfw window crated");


	GLenum status = glewInit();
	if(status == GLEW_OK){    //attempt to initialize glew
		log.status("glew inited");
	}else{	//if it is unable to init glew
		std::stringstream error;	//string stream used to extract string form glewgeterrorstring
		error << glewGetErrorString(status);	//get the error
		std::string src;	//used to hold actual string of error
		error >> src;	//put error string in src

		log.error("glew failed to init: \"" + src + "\"", __LINE__, __FILE__);	//print it
	}

	while(true){}
}