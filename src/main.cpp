//Main.cpp Main.h
//parse the arguments then start the application
//with the given arguments also holds help message
//and stuff
#include <iostream>

#include "Application.h"
#include "SettingManager.h"

//yep
int main(int _argc, char **_argv){

	////if help, print usage and exit
	//if(argVarMap.count("help")){
		//std::cout << argDesc;
		//return 0;
	//}

	//SettingManager *settings = new SettingManager();
	//SettingManager *settings;
	//settings->passCmdLineArgs(_argc, _argv);

	//try{
		//settings.passCmdLineArgs(_argc, _argv);
	//}catch(std::exception e){
		//std::cout << e.what() << std::endl;
		//settings.printCmdLineUsage();
	//}

	Application app;
	app.start();

	return 0;
}
