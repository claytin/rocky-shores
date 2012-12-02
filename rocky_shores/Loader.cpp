#include "Loader.h"

Loader::Loader(void){

}

Loader::~Loader(void){

}

Defaults::Status Loader::loadRes(std::string _path){
	std::string directory = "err";
	std::string line = "err";    //the current line to read

	std::ifstream file(_path);    //open the path into file

	if(!file.is_open()){    //check if file was open correctally
		return Defaults::FILE_NOT_FOUND;    //if not return file not found error
	}

	if(_path.find_last_of('/') != std::string::npos){    //if var _path contains char / then
		//set directory to the location of the file being loaded aka the _path without the .res file
		directory = _path.substr(0, _path.find_last_of('/') + 1);
	}else{
		directory = "";
	}

	while(true){ 
		//as long as the file is readable do: puth the current line contents in variable line
		//check if the line is not empty
		//if it contains a resource then load it

		skip:	//used to go to next result if the resource is null or there is an error

		if(!file.good()){    //checks if its not at the end of the file
			break;
		}

		std::getline(file, line);

		if(line.length() <= 0){    //if the number of characters in the line is less then 0 then skip the line
			goto skip;    //nothing to do, the line has nothing to compute, go to the next line

		}else if(line.at(0) == '#'){    //if the line starts with # then is a comment
			goto skip;
		}

		std::string fileType = "err";	//this will the type of file ex: png, ogg, exe

		int posOfPeriod = line.find_last_of('.');	//the position of the last period on the current line after that is the file type
		if(posOfPeriod == std::string::npos){     //if there is no period in the line then return an invalid file error
			return Defaults::INVALID_FILE;
		}
		fileType = line.substr(posOfPeriod + 1, line.length() - (posOfPeriod + 1));    //puts the string after the last period in var filetype

		//if(){
//
		//}
	}

	return Defaults::GOOD;
}