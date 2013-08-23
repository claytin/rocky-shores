#include "Setup.h"
#define res "../res/"

Setup::Setup(void){

}

Setup::~Setup(void){

}

void Setup::initialLoad(std::string _path){
	Loader loader;

	try{
		loader.loadRes(_path);
		log.status("loaded required resources");
	}catch(Defaults::Exception e){
		//log.error( e.description + "\n ERROR CODE: \"" + std::to_string(e.type) + "\"");
		log.error( e.description + "\n ERROR CODE: \" tmp fix \"");
		glfwTerminate();
		return;
	}

	//load the base vertex and fragment shaders and put them in a program
	std::vector<Shader> shaders;
	try{
		shaders.push_back(Shader(Loader::stringFromFile(res "/shaders/base.frag"), GL_FRAGMENT_SHADER));
		shaders.push_back(Shader(Loader::stringFromFile(res "/shaders/base.vert"), GL_VERTEX_SHADER));
	}catch(Defaults::Exception e){
		//if it was unable to load the basic shaders needed (may hardcode base shaders later...)
		log.error(e.description + "\n ERROR CODE: \" ....\"");
		glfwTerminate();
		return;
	}

	ShaderProgram simpleShaderProgram(shaders);

	Render menuRender;
	menuRender.setShader(&simpleShaderProgram);

	//create a drawable for testing the display system
	Drawable testMesh;

	//create a nice triangle, because who doesn't love triangles
	//TODO yeah ill have to fix this later
	Mesh::face  tempFace;
	tempFace.cord[0] = new glm::vec3(0.0f, 1.0f, 0.0f);
	tempFace.cord[1] = new glm::vec3(1.0f, -1.0f, 0.0f);
	tempFace.cord[2] = new glm::vec3(-1.0f, -1.0f, 0.0f);
	tempFace.color = glm::vec3(20, 180, 255);
	testMesh.addFace(tempFace);

	menuRender.compileVertexBuffer(&testMesh);

	while(true){
		//check if the window should be closed
		if(!glfwGetWindowParam(GLFW_OPENED) || glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS){
			glfwTerminate();
			return;    //its over folks you can go home now
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		menuRender.render(&testMesh);    //just keep rendering

		glfwSwapBuffers();
	}
}

void Setup::display(int _width, int _height){

	if(!glfwInit()){    //try to initalize glfw
		log.error("cannot initialize glfw");	//if it fails to init send error to log
	}else{
		log.status("glfw initialized");	//if successfully initied glfw
	}


	if(!glfwOpenWindow(_width, _height, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)){   //try to crate window with glfw, coming soon customizable paramaters
		log.error("cannot create glfw window");	//if failed to crate window
	}else{
		log.status("glfw window created");	//if window is crated print success
	}



	GLenum status = glewInit();
	if(status == GLEW_OK){    //attempt to initialize glew
		log.status("glew initialized");

		// print out some info about the graphics drivers, oh and ofcouse opengl has to have its own data type so thats what the ostringstring is for
		std::ostringstream hardwareInfoStringStream;
		hardwareInfoStringStream << "OpenGL version: " << glGetString(GL_VERSION) << "\nGLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
			<< "\nHardware vendor: " << glGetString(GL_VENDOR) << "\nRenderer: " << glGetString(GL_RENDERER);
		std::string hardwareInfo;

		//put in a nice little section
		log.startBlock("Hardware Info");
		log.status(hardwareInfoStringStream.str());
		log.endBlock();

	}else{	//if it is unable to init glew
		std::stringstream error;	//string stream used to extract string form glewgeterrorstring
		error << glewGetErrorString(status);	//get the error
		std::string src;	//used to hold actual string of error
		error >> src;	//put error string in src

		log.error("glew failed to init: \"" + src + "\"", __LINE__, __FILE__);	//print it
	}

	//check to make sure system meets requirments
	if(!GLEW_VERSION_3_2){
		log.error("Opengl version 3.2 is not supported this is a problem");
	}
}