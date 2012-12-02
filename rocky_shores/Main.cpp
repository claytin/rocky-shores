//Main.cpp
//where it all starts
//this class simply calls setup to initialize opengl, open window, load resourses
//it doesn't do anything else, super simple stuff
//-mgc480

#include "Setup.h"	//needs setup to call functions

//main function
int main(int argc, char * args){

	Setup setup;
	setup.display(800, 600);	//get opengl ready for action
	setup.initialLoad("res/require.res");

	return 0;	//yay all done here
}