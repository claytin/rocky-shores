//Main.cpp
//where it all starts
//this class simply calls setup to initialize opengl, open window, load resourses
//it doesn't do anything else, super simple stuff
//-mgc480

#include "Setup.h"	//needs setup to call functions
#define res "../res/"	//TEMPORARY JUST TO GET THINGS WORKING

//main function
int main(int argc, char ** args){
	Setup setup;
	setup.display(800, 600);	//initialize opengl, glew, and glfw, also use 800x600 as the default window size

	try{
		setup.initialLoad(res "/require.res");
	}catch(Defaults::Exception e){
		std::cout << "there was a problem initial loading required resources >" << e.description << std::endl;
	}

	//this is so in windows I can read it before the terminal window closes
	std::cout << "Press Enter To Continue..." << std::endl;
	std::getchar();

	return 0;	//yay all done here
}