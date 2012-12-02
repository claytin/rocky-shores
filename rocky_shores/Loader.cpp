#include "Loader.h"

Loader::Loader(void){

}

Loader::~Loader(void){

}

Defaults::Status Loader::loadRes(std::string path){
	std::string line;	//the current line to read

	std::ifstream file(path);	//open the path into file

	if(!file.is_open()){    //check if file was open correctally
		return Defaults::FILE_NOT_FOUND;	//if not return file not found error
	}

	while(true){ 
		//as long as the file is readable do: puth the current line contents in string line
		//check if the line is not empty
		//if it contains a resource then load it

		skip:	//used to go to next result if the resource is null or there is an error

		if(!file.good()){    //checks if its not at the end of the file
			break;
		}

		std::getline(file, line);

		//if(line.at(0) == '#' || line.empty()){    //the character # means it is a comment
		//	goto skip;    //nothing to do, the line has nothing to compute, go to the next line
		//}

		//std::string fileType = "err";

		//int posOfPeriod = line.find_last_of('.');
		//fileType = line.substr(posOfPeriod, line.length() - posOfPeriod);

		//std::cout << "file type: " << fileType << std::endl;
	}

	return Defaults::GOOD;
}