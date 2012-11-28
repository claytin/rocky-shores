#include "Setup.h"

Setup::Setup(void){

}

Setup::~Setup(void){

}

void Setup::opengl(void){
	Log log;

	GLenum glewStatus = glewInit();
	if(glewStatus == GLEW_OK){    //attempt to initialize glew
		log.status("glew inited", __LINE__, __FILE__);
	}else{	//if it is unable to init glew
		log.status("glew failed to init", __LINE__, __FILE__);
	}


}
