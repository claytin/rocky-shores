#include "SettingManager.h"

SettingManager::SettingManager(void){

}

SettingManager::~SettingManager(void){

}

void SettingManager::passCmdLineArgs(const int _argc, const char **_argv)
throw(std::exception){
	//yeah i'm using boost... you wanna fight about it
	arg::options_description argDesc("usage");
	argDesc.add_options()
		("help,h", "show this message")
		("test,t", "a test argument, it doesn nothing");

	//parse command line arguments
	//if the argument is not recognized then the throw an exception
	arg::variables_map argVarMap;
	try{
		arg::store(arg::parse_command_line(_argc, _argv, argDesc), argVarMap);
	}catch(boost::program_options::unknown_option e){
		throw std::runtime_error("unknown argument \""
			+ e.get_option_name() + "\"");
	}

	arg::notify(argVarMap);
}

void SettingManager::printCmdLineUsage(void){

}
