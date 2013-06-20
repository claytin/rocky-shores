//Defaults.h
//very simple file which just contains constant data for everything
//for example error codes
//-mgc480

#pragma once
#include <iostream>

namespace Defaults{
	//a big long enum full of most of the errors errors and returns that a function could return / throw
	enum Status {GOOD, BAD, FILE_NOT_FOUND, FILE_CORRUPT, OUT_OF_MEMORY, UNKNOWN_ERROR, INVALID_FILE,
		CANNOT_LINK_SHADERS, NULL_POINTER, NULL_VERTEX_CORD, OUT_OF_BOUNDS, NOT_IMPLEMENTED,
		EXTERNAL, INVALID_STRING, SHADER_ERROR};

	//used when returning errors, it contains the enum of the error along with additional information.
	//most of the information is optional and can be left blank / null.
	struct Exception{
		Status type;    //holds the actual enum eror type, this is not verry descriptive and could be better
		std::string description;    //holds a descriptive string of the problem, this is only used to output to use and for 
		//debuging and is not usefull for anything else in code 
		int line;    //usefull for debuging, not required or very necessary
		std::string file;    //the file which the error ocured in, similar to line in that its usefull for debuging

		//CONSTRUCTOR, simply sets the variables to something in case they where not set by function returning the error
		Exception(Status _status = Status::FILE_NOT_FOUND, std::string _description = "No description of error avalible.",
			int lineNumber = 0, std::string _filePath = "No file path avalible."){
			type = _status;    //if the type is never set then it will be unknown
			description = _description;
			line = lineNumber;
			file = _filePath;
		}
	};
}