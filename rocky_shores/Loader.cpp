#include "Loader.h"

Loader::Loader(void){

}

Loader::~Loader(void){

}

Loader::status Loader::loadRes(std::string path){
	std::string line;	//the current line to read

	std::ifstream file(path);	//open the path into file

	if(!file.is_open()){    //check if file was open correctally
		return Loader::FILE_NOT_FOUND;	//if not return file not found error
	}

	while(file.good()){ 
		//as long as the file is readable do: puth the current line contents in string line
		//check if the line is not empty
		//if it contains a resource then load it
		skip:	//used to go to next result if the resource is null or there is an error
		std::getline(file, line);

		if(line.at(0) == '#' || line.empty()){    //the character # means it is a comment
			goto skip;    //nothing to do, the line has nothing to compute, go to the next line
		}else if(line.end){

		}
	}

	return Loader::status::GOOD;
}