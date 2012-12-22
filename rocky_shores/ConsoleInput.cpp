#include "ConsoleInput.h"

ConsoleInput::ConsoleInput(void){

}

ConsoleInput::~ConsoleInput(void){
	
}

void ConsoleInput::start(){
	std::string input;

	while(true){
		std::cin >> input;
	}
}