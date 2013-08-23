//Log.h - used as a global comunication system to log file or console
//very simple takes arguments and prints them to console or a file (whichever is selected)
//-mgc480

#pragma once
#include <iostream>	//uses iostream for console output
#include <string.h>	//uses string for message

class Log{

public:
	Log(void);
	~Log(void);

	static void status(std::string message);	//prints the message to the console
	//used to break the output into blocks, each block has a start then prints either status or errors then ends the block
	static void startBlock(std::string blockName);
	static void endBlock();
	static void error(std::string message, int line = -1, const char * file = 0);	//same as status but also brings up dialogue
};

