//Defaults.h
//very simple file which just contains constant data for everything
//for example error codes
//-mgc480

#pragma once

namespace Defaults{
	//a big long enum full of all the possible errors and returns that a function could return / throw
	enum Status {GOOD = 0, BAD = 1, FILE_NOT_FOUND = 2, FILE_CORRUPT = 3, OUT_OF_MEMORY = 4, UNKNOWN_ERROR = 5, INVALID_FILE = 6,
		CANNOT_LOAD_VERTEX_SHADER = 7, CANNOT_LOAD_FRAGMENT_SHADER = 8, CANNOT_LINK_SHADERS = 9, NULL_POINTER = 10,
		NULL_VERTEX_CORD};

	//used when returning errors, it contains the enum of the error along with additional information.
	//most of the information is optional and can be left blank / null.
	struct Exception{
		Status type;    //holds the actual enum eror type, this is not verry descriptive and could be better
		std::string description;    //holds a descriptive string of the problem, this is only used to output to use and for 
		//debuging and is not usefull for anything else in code 
		int line;    //usefull for debuging, not required or very necessary
		std::string file;    //the file which the error ocured in, similar to line in that its usefull for debuging

		//CONSTRUCTOR, simply sets the variables to something in case they where not set by function returning the error
		Exception(){
			type = Status::UNKNOWN_ERROR;    //if the type is never set then it will be unknown
			description = "No description of error avalible.";
			line = 0;
			file = "No file path avalible.";
		}
	};
}