#include "Log.h"

static long lineNumber;    //holds the current output line thoughout the whole application

Log::Log(void){

}

Log::~Log(void){

}

void Log::status(std::string message){
	int posOfNewLine = message.find_first_of('\n');    //search for \n new line character

	if(posOfNewLine != -1){    //check if there are any new line (\n) characters
		if(posOfNewLine == message.length() - 1){
			Log::status( message.substr(0, message.length() - 1).c_str());
		}else{

		}
	}else{
		lineNumber++;
		std::cout <<  lineNumber << ":> " << message.c_str();	//print out message
		std::cout << std::endl;	//end line
	}
}

void Log::error(std::string message, int line, const char * file){
	std::cout << ":> error: " << message.c_str();	//print out message
	if(line != -1 && file != 0){	//print out message
		std::cout << " @ " << file << ":" << line;
	}
	std::cout << std::endl;	//end line

	//TODO coming soon: open a dialogue
}