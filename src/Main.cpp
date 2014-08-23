//Main.cpp Main.h
//parse the arguments then start the application
//with the given arguments also holds help message
//and stuff

#include "Main.h"

namespace arg = boost::program_options;

Main::Main(void){

}

Main::~Main(void){

}

//yep
int main(int _argc, char **_argv){
	//use boost for command line arguments
	arg::options_description argDesc("usage");
	argDesc.add_options()
		("help,h", "show this message");

	//parse command line arguments
	//if the argument is not recognized then the
	//usage will be printed and 1 will be returned
	arg::variables_map argVarMap;
	try{
		arg::store(arg::parse_command_line(_argc, _argv, argDesc), argVarMap);
	}catch(boost::program_options::unknown_option e){
		std::cout << "unknown argument: \'" << e.get_option_name() << '\''
			<<  std::endl << argDesc;
		return 1;
	}
	arg::notify(argVarMap);

	//if help, print usage and exit
	if(argVarMap.count("help")){
		std::cout << argDesc;
		return 0;
	}

	Application app;
	app.start();

	return 0;
}
