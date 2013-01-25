#define GLEW_STATIC
#include "Setup.h"

Setup::Setup(void){

}

Setup::~Setup(void){

}

void Setup::initialLoad(std::string _path){
	Loader loader;

	Defaults::Status loadStatus = loader.loadRes(_path);
	if(loadStatus == Defaults::GOOD){
		log.status("loaded required resources");
	}else{
		log.error("unable to load required resources. cannot continue, will now exit. \n ERROR CODE: \"" + std::to_string(loadStatus) + "\"");
		glfwTerminate();
	}

	GLuint simpleShader;
	Loader::loadShader("res/shaders/simple.vert", "res/shaders/simple.frag", &simpleShader);	//err umm well...

	SimpleRender renderer;
	renderer.setShader(simpleShader);

	ConsoleInput consoleInput(void);    //allow console input (this is only for developing)


	//create a drawable for testing the display system
	Drawable testMesh;

	//create a nice triangle, because who doesn't love triangles
	Mesh::face tempFace;
	tempFace.cord[0] = &glm::vec3(0.0f, 1.0f, 0.0f);
	tempFace.cord[1] = &glm::vec3(1.0f, -1.0f, 0.0f);
	tempFace.cord[2] = &glm::vec3(-1.0f, -1.0f, 0.0f);
	testMesh.addFace(tempFace);

	testMesh.compileVao();	//and the object is ready for rendering

	while(true){
		//check if the window should be closed
		if(!glfwGetWindowParam(GLFW_OPENED) || glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS){
			glfwTerminate();
			return;    //its over folks you can go home now
		}

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.render(&testMesh);    //just keep sendering it to the renderer for the rendering to hapener

		glfwSwapBuffers();
	}
}

void Setup::display(int _width, int _height){

	if(!glfwInit()){    //try to initalize glfw
		log.error("cannot initialize glfw", __LINE__, __FILE__);	//if it fails to init send error to log
	}else{
		log.status("glfw initialized");	//if successfully initied glfw
	}
	

	if(!glfwOpenWindow(_width, _height, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)){   //try to crate window with glfw, coming soon customizable paramaters
		log.error("cannot create glfw window", __LINE__, __FILE__);	//if failed to crate window
	}else{
		log.status("glfw window crated");	//if window is crated print success
	}
	


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

	//check to make sure system meets requirments
	if(!GLEW_VERSION_3_0){
		log.error("Opengl version 3.0 is not supported this could cause problems");
	}
}