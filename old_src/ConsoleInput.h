//ConsoleInput.h / ConsoleInput.cpp
//this class simply takes input or commands from the console
//it should be run in a seprate thread so it doesn't interfear with the game
//THIS IS NOT DONE, DO NOT USE.

#pragma once
#include <iostream>
#include <string>

class ConsoleInput{

public:
	ConsoleInput(void);    //CONSTRUCTOR does nothing at the moment
	~ConsoleInput(void);

private:
	void start();
};

