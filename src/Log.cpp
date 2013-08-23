#include "Log.h"

#define DIVIDER "-"
#define DIVIDER_WIDTH 50

static long lineNumber;    //holds the current output line thoughout the whole application
static unsigned int blockNumber = 0;	//how many blocks your are currently in

Log::Log(void){

}

Log::~Log(void){

}

void Log::status(std::string message){
	int posOfNewLine = message.find_first_of('\n');    //search for \n new line character

	if(posOfNewLine != -1){    //check if there are any new line (\n) characters
		status(message.substr(0, posOfNewLine).c_str());
		status(message.substr(posOfNewLine + 1, message.length() - 1));
	}else{
		lineNumber++;
		std::cout << lineNumber << ":> ";	//print out message
		for(unsigned int i = 0; i < blockNumber; i++){
			std::cout << "\t|";
		}
		std::cout << message.c_str() << std::endl;	//end line
	}
}

void Log::startBlock(std::string blockName){
	std::string output = DIVIDER "-" + blockName + "-";

	for(int i = 0; i < DIVIDER_WIDTH - signed(blockName.length()) - 4; i++){
		output += DIVIDER;
	}
	output += DIVIDER;

	status(output);

	blockNumber++;
}

void Log::endBlock(){
	blockNumber--;
}

void Log::error(std::string message, int line, const char * file){
	std::cout << ":> error: " << message.c_str();	//print out message
	if(line != -1 && file != 0){	//print out message
		std::cout << " @ " << file << ":" << line;
	}
	std::cout << std::endl;	//end line

	//TODO coming soon: open a dialogue
}