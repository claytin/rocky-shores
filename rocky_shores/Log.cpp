#include "Log.h"

Log::Log(void){

}

Log::~Log(void){

}

void Log::status(std::string message, int line, const char * file){
	std::cout << "::status: " << message.c_str();	//print out message
	if(line != -1 && file != 0){	//print out message
		std::cout << " @ " << file << ":" << line;
	}
	std::cout << std::endl;	//end line
}

void Log::error(std::string message, int line, const char * file){
	std::cout << "::status: " << message.c_str();	//print out message
	if(line != -1 && file != 0){	//print out message
		std::cout << " @ " << file << ":" << line;
	}
	std::cout << std::endl;	//end line

	//TODO coming soon: open a dialogue
}