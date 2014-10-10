#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <boost/program_options.hpp> //i'm so sorry
#include <stdexcept>

namespace arg = boost::program_options;

class SettingManager{

public:
	SettingManager(void);
	~SettingManager(void);

	//takes arguments in the c style and parses them
	void passCmdLineArgs(const int _argc, const char **_argv)
		throw(std::exception);


	//returns a string holding the usage that can then be printed to the
	//terminal as a help message
	std::string cmdLineUsage(void);

private:
	//holds all the command line arguments allowed
	arg::options_description allowedArgs; //sorry bout the boost
};

#endif
