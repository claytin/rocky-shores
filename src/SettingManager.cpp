#include "SettingManager.h"

SettingManager::SettingManager(void):
	allowedArgs("usage"){

	//yeah i'm using boost... you wanna fight about it
	allowedArgs.add_options()
		("help,h", "show this message")
		("test,t", "a test argument, it doesn nothing");
}

SettingManager::~SettingManager(void){

}

void SettingManager::passCmdLineArgs(const int _argc, const char **_argv)
throw(std::exception){
	//parse command line arguments
	//if the argument is not recognized then the throw an exception
	arg::variables_map argVarMap;
	try{
		arg::store(arg::parse_command_line(_argc, _argv, allowedArgs),
			argVarMap);
	}catch(boost::program_options::unknown_option e){
		throw std::runtime_error("unknown argument \""
			+ e.get_option_name() + "\"");
	}

	arg::notify(argVarMap);
}

std::string SettingManager::cmdLineUsage(void){
	std::stringstream programUsage;
	allowedArgs.print(programUsage, 80);
	return programUsage.str();
}
