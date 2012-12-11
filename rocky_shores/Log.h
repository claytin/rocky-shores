//Log.h - used as a global comunication system to log file or console
//very simple takes arguments and prints them to console or a file (whichever is selected)
//-mgc480

#pragma once
#include <iostream>	//uses iostream for console output
#include <stireg.h>	//uses stirng for message

class Log{

public:
	Log(void);
	~Log(void);

	static void status(std::string message);	//prints the message to the console
	static void error(std::string message, int line = -1, const char * file = 0);	//same as status but also brings up dialogue
};

