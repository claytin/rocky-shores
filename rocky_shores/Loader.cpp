#define SEPARATOR "----------------------------------------------------"	//TODO FIX THIS LATER
#include "Loader.h"

Loader::Loader(void){
	setMipmap(GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST);
}

Loader::~Loader(void){

}

void Loader::setMipmap(GLenum min, GLenum max){
	//minFilter = min;
	//maxFilter = max;
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

		Defaults::Status statusOfLoad;

		//check for file type (extension after the last period) and load that type of file
		if(fileType == "bmp"){
			statusOfLoad = loadBmp(directory + line);
			if(statusOfLoad != Defaults::GOOD){
				return statusOfLoad;
			}

		}else if(fileType == "tga"){
			statusOfLoad = loadTga(directory + line);
			if(statusOfLoad != Defaults::GOOD){
				return statusOfLoad;
			}
		}else if(fileType == "gif"){
			GLuint stf;
			statusOfLoad = Loader::loadGif(directory + line, &stf);
			if(statusOfLoad != Defaults::GOOD){
				return statusOfLoad;
			}
		}else{
			//the file type cannot be loaded
			return Defaults::INVALID_FILE;
		}
	}

	return Defaults::GOOD;
}

Defaults::Status Loader::loadTga(std::string _path){
	GLuint textureId;

	if(Loader::loadTga(_path, &textureId) != Defaults::GOOD){    //if the load didn't return good then return its error
		return Defaults::INVALID_FILE;
	}

	textures[_path.substr(0, _path.find_last_of("."))] = textureId;    //if the load succeded then added the texture to the list

	return Defaults::GOOD;
}

Defaults::Status Loader::loadTga(std::string _path, GLuint * _index){
	GLuint textureId;	//the index/ id of the texture in opengl

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glfwLoadTexture2D(_path.c_str(), 0);

	//setup mipmaping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

	*_index = textureId;

	return Defaults::GOOD;	//if the file was loaded then return success
}

Defaults::Status Loader::loadBmp(std::string path){
	GLuint textureId;	
	
	Defaults::Status status = Loader::loadBmp(path, &textureId);
	if(status != Defaults::GOOD){
		return status;
	}

	textures[path.substr(0, path.find_last_of("."))] = textureId;

	return Defaults::GOOD;
}

Defaults::Status Loader::loadBmp(std::string path, GLuint * index){
	unsigned char * header = new unsigned char [54];	//holds the header for the bmp this contains information of the file
	unsigned int dataPos, width, height, imageSize;    //data of image that is extracted from the header
	unsigned char * data;	//the actual image data

	std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);	//open file
	if(!file.is_open()){    //if it opened successfuly then continue otherwise return that the file was not found
		return Defaults::FILE_NOT_FOUND;
	}

	file.seekg(0, std::ios::beg);	//go to the begining
	file.read((char*)header, 54);	//read the first 54 bytes and put it into the header for later extraction

	
	if(header[0] != 'B' || header[1] != 'M'){    //check to make sure it is a valid bmp file (all bmp files start with BM)
		return Defaults::FILE_CORRUPT;
	}

	//get the information from specific places in the header
	dataPos = header[0x0A];
	imageSize = header[0x22];
	width = header[0x12];
	height = header[0x16];


	if(dataPos == 0){
		dataPos = 54;
	}
	if(imageSize == 0){    //if the image size is not included in the bitmap file then
		imageSize = width * height * 3;
	}

	data = new unsigned char[imageSize];	//now that we know the size of the image create an array for the data with the size of the image

	file.read((char*)data, imageSize);	//read the rest of the image into data
	file.close();	//now that everything is done close the steam

	GLuint textureId;	//used to store the index of the texture created in opengl

	//the rest is pretty self explanatory
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	//give data to opengl
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	//setup mipmaping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

	//finaly set dat pointer
	*index = textureId;

	return Defaults::GOOD;
}

Defaults::Status Loader::loadGif(std::string path, GLuint * index){    //load a GIF file (under construction)
	//this is not done and undocumented. it doesn't work. 
	//IN OTHER WORDS DON'T USE IT.
	unsigned char * data;
	unsigned int width, height, size;

	std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
	
	if(!file.is_open()){
		return::Defaults::FILE_NOT_FOUND;
	}

	size = file.tellg();
	data = new unsigned char[size];

	file.seekg(0, std::ios::beg);
	file.read((char*)data, size);
	file.close();

	if(data[0] == 'G' && data[1] == 'I' && data[2] == 'F'){
		
	}else{
		return Defaults::INVALID_FILE;
	}

	return Defaults::GOOD;
}

Defaults::Status Loader::loadVertexShader(std::string path, GLuint * index){
	GLuint shaderId = glCreateShader(GL_VERTEX_SHADER);    //holds the index of the loaded shader
	std::string shaderData;    //holds the data from the loaded shader program

	std::ifstream file(path, std::ios::in);

	if(!file.is_open()){
		return Defaults::FILE_NOT_FOUND;
	}

	Log::status("Loading Vertex Shader: " + path);
	Log::status("----------------------------------------------------");

	while(file.good()){    //while the file is not at the end put its contents in var line then add line to shader data
		std::string line;
		std::getline(file, line);
		shaderData += "\n" + line;
		Log::status(":: " + line);
	}

	file.close();    //all is well now the file can be closed

	Log::status(SEPARATOR);
	Log::status("Finished loading, Now compiling...");

	//compile dat shader
	char const * sourcePointer = shaderData.c_str();
	glShaderSource(shaderId, 1, &sourcePointer , NULL);    //give the data to opengl
	glCompileShader(shaderId);    //compile dat shit

	//check the status of the shader (see how the compiling went)
	GLint status = GL_FALSE;	//the status of the compile
	int length = 0;    //the length of the string of the status

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);	//get the status and put it in status
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);	//get the length of the status and put it in length

	std::vector<char> shaderStatus(length);	//this is where the actual status is held
	glGetShaderInfoLog(shaderId, length, NULL, &shaderStatus[0]);	//put the shader status in var shaderStatus

	Log::status("Compile Status:");
	Log::status(SEPARATOR);
	Log::status("-- BEGIN --");
	Log::status(&shaderStatus[0]);
	Log::status("-- END --");

	return Defaults::GOOD;
}

Defaults::Status Loader::loadFragmentShader(std::string path, GLuint * index){
	return Defaults::GOOD;
}