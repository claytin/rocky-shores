#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <boost/program_options.hpp> //i'm so sorry
#include <stdexcept>

namespace arg = boost::program_options;

class SettingManager{

public:
	SettingManager(void);
	~SettingManager(void);

	void passCmdLineArgs(const int _argc, const char **_argv) throw(std::exception);
	void printCmdLineUsage(void);

private:

};

#endif
