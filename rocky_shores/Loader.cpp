#include "Loader.h"

static GLenum minFilter = GL_LINEAR_MIPMAP_NEAREST, maxFilter = GL_NEAREST;
void readPngData(png_structp pngPtr, png_bytep data, png_size_t length);	//this function is used by libpng to load data from file, this uses ifstream wich rather than lib png's defalt FILE wich is old

Loader::Loader(void){

}

Loader::~Loader(void){

}

void Loader::setMipmap(GLenum min, GLenum max){
	minFilter = min;
	maxFilter = max;
}

void Loader::loadRes(std::string _path){
	std::string directory = "null";
	std::string line = "null";    //the current line being read and proccessed

	std::ifstream file(_path);    //open the path into file

	if(!file.is_open()){    //check if file was open correctally
		throw Defaults::Exception(Defaults::FILE_NOT_FOUND, "Unable to find or open file \"" + _path + "\". File doesn't exsist or is currupt.");
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
		if(posOfPeriod == std::string::npos){     //if there is no period in the line then throw an invalid file error
			throw Defaults::Exception(Defaults::INVALID_FILE, "The file \"" + directory + line + "\" listed in the .res file \"" + _path + "\" was found invalid and could not be loaded");
		}
		fileType = line.substr(posOfPeriod + 1, line.length() - (posOfPeriod + 1));    //puts the string after the last period in var filetype

		//if a function throws an exception is saved here and thrown at the end of the loop
		Defaults::Exception exception;
		bool exceptionThrown = false;

		//check for file type (extension after the last period) and load that type of file
		if(fileType == "bmp"){
			try{
				loadBmp(directory + line);
			}catch(Defaults::Exception e){
				exception = e;
				exceptionThrown = true;
			}
		}else if(fileType == "tga"){
			try{
				loadTga(directory + line);
			}catch(Defaults::Exception e){
				exception = e;
				exceptionThrown = true;
			}
		}else if(fileType == "gif"){
			try{
				loadGif(directory + line);
			}catch(Defaults::Exception e){
				exception = e;
				exceptionThrown = true;
			}
		}else if(fileType == "png"){
			try{
				loadPng(directory + line);
			}catch(Defaults::Exception e){
				exception = e;
				exceptionThrown = true;
			}
		}else{
			//the file is of an unknown type
			throw Defaults::Exception(Defaults::INVALID_FILE, "The file \"" + directory + line + "\" listed in the .res file\"" + _path + "\" was not recognized as a valid file format.");
		}

		if(exceptionThrown){
			Defaults::Exception modifiedException = exception;
			//reformat the exception description to hopefully describe the error better
			modifiedException.description = "while loading .res file \"" + _path + "\" the resource \"" + directory + line
				+ "\" could not be loaded and threw \"" + exception.description + "\" with error code \"" + std::to_string(exception.type) + "\"";
			throw modifiedException;
		}
	}
}

void Loader::loadTga(std::string _path){
	GLuint textureId;

	try{
		Loader::loadTga(_path, &textureId);
	}catch(Defaults::Exception e){
		throw e;
	}

	textures[_path.substr(0, _path.find_last_of("."))] = textureId;    //if the load succeded then added the texture to the list

}

void Loader::loadTga(std::string _path, GLuint * _index){
	GLuint textureId;	//the index/ id of the texture in opengl

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glfwLoadTexture2D(_path.c_str(), 0);

	//setup mipmaping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glGenerateMipmap(GL_TEXTURE_2D);

	*_index = textureId;
}

void Loader::loadBmp(std::string path){
	GLuint textureId;	

	try{
		Loader::loadBmp(path, &textureId);
	}catch(Defaults::Exception e){
		throw e;
	}

	textures[path.substr(0, path.find_last_of("."))] = textureId;

}

void Loader::loadBmp(std::string path, GLuint * index){
	unsigned char * header = new unsigned char [54];	//holds the header for the bmp this contains information of the file
	unsigned int dataPos, width, height, imageSize;    //data of image that is extracted from the header
	unsigned char * data;	//the actual image data

	std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);	//open file
	if(!file.is_open()){    //if it opened successfuly then continue otherwise return that the file was not found
		throw Defaults::Exception(Defaults::FILE_NOT_FOUND, "unable to open file\"" + path + "\" it might be missing or currupt");
	}

	file.seekg(0, std::ios::beg);	//go to the begining
	file.read((char*)header, 54);	//read the first 54 bytes and put it into the header for later extraction

	
	if(header[0] != 'B' || header[1] != 'M'){    //check to make sure it is a valid bmp file (all bmp files start with BM)
		throw Defaults::Exception(Defaults::INVALID_FILE, "the file is not a valid .bmp file, the first two characters must be B M");
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
}

void Loader::loadGif(std::string path, GLuint * index){    //load a GIF file (under construction)
	//this is not done and undocumented. it doesn't work. 
	//IN OTHER WORDS DON'T USE IT.

	throw Defaults::Exception(Defaults::NOT_IMPLEMENTED, "the load gif function is currentaly not finished");
}

void Loader::loadGif(std::string path){
	//currently no gif loader
	throw Defaults::Exception(Defaults::NOT_IMPLEMENTED, "the load gif function is currentaly not finished");
}

void Loader::loadPng(std::string path){
	GLuint textureId;

	try{
		Loader::loadPng(path, &textureId);
	}catch(Defaults::Exception e){
		throw e;
	}

	textures[path.substr(0, path.find_last_of("."))] = textureId;
}

void Loader::loadPng(std::string path, GLuint * index){    //this function relies compleatly on libpng to load pngs
	const int pngSignatureSize = 8;

	//open file
	std::ifstream file(path, std::ios::in | std::ios::binary);

	if(!file.is_open()){
		throw Defaults::Exception(Defaults::FILE_NOT_FOUND, "unable to open file, it might be missing or unreadable");
	}

	//check to make sure it is a valid png file
	png_byte pngSignature[pngSignatureSize];
	file.read((char*)pngSignature, pngSignatureSize);

	if(png_sig_cmp(pngSignature, 0, pngSignatureSize) != 0){
		throw Defaults::Exception(Defaults::INVALID_FILE, "the file is invalid because it does not have a valid png header, the file could be corrupt or incorectally formated");
	}

	//create the png data structors from lib png and then check for errors
	png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!pngPtr) {
		throw Defaults::Exception(Defaults::EXTERNAL, "libpng could not create a \"png_structp\" using \"png_create_read_struct\"");
	}

	png_infop infoPtr = png_create_info_struct(pngPtr);
	if(!infoPtr){
		throw Defaults::Exception(Defaults::EXTERNAL, "libpng could not create a \"png_infop\" using \"png_create_info_struct\"");
	}

	//now lets read the data form the png now that the required structs have been created
	png_bytep* rowPtrs = NULL;
	char* data = NULL;

	if(setjmp(png_jmpbuf(pngPtr))){
		png_destroy_read_struct(&pngPtr, &infoPtr,(png_infopp)0);
		if(rowPtrs != NULL) delete [] rowPtrs;
		if(data != NULL) delete [] data;

		throw Defaults::Exception(Defaults::EXTERNAL, "libpng could not read the image for an unknown reason...");
	}

	//give libpng our read function with a function pointer
	void (*readPngFunc)(png_structp, png_bytep, png_size_t) = readPngData;
	png_set_read_fn(pngPtr, (png_voidp)&file, readPngFunc);

	png_set_sig_bytes(pngPtr, pngSignatureSize);	//tell libpng that we alread have already read the signature

	png_read_info(pngPtr, infoPtr);	//get info from png before loading into memory so we can alocat nessasary amount of memory

	unsigned int width =  png_get_image_width(pngPtr, infoPtr);
	unsigned int height = png_get_image_height(pngPtr, infoPtr);
	unsigned int bitdepth   = png_get_bit_depth(pngPtr, infoPtr);
	unsigned int channels   = png_get_channels(pngPtr, infoPtr);
	unsigned int colorType = png_get_color_type(pngPtr, infoPtr);

	//variables to hold data
	data = new char[width * height * bitdepth * channels / 8];
	rowPtrs = new png_bytep[height];

	const unsigned int rowSize = width * bitdepth * channels / 8;

	//set all the data t
	for (unsigned int i = 0; i < height; i++) {
		png_uint_32 q = (height- i - 1) * rowSize;
		rowPtrs[i] = (png_bytep)data + q;
	}

	//load that image!!!
	png_read_image(pngPtr, rowPtrs);

	//clean stuff up
	delete[] (png_bytep)rowPtrs;
	png_destroy_read_struct(&pngPtr, &infoPtr,(png_infopp)0);
}

void Loader::loadVertexShader(std::string path, GLuint * index){
	GLuint shaderId = glCreateShader(GL_VERTEX_SHADER);    //holds the index of the loaded shader
	std::string shaderData;    //holds the data from the loaded shader program

	std::ifstream file(path, std::ios::in);

	if(!file.is_open()){
		throw Defaults::Exception(Defaults::FILE_NOT_FOUND, "unable to open file, it might be missing or currupt");
	}

	Log::status("Loading Vertex Shader: " + path);

	while(file.good()){    //while the file is not at the end put its contents in var line then add line to shader data
		std::string line;
		std::getline(file, line);
		shaderData += "\n" + line;
	}

	file.close();    //all is well now the file can be closed

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
	Log::status("-- BEGIN --");
	Log::status(&shaderStatus[0]);
	Log::status("-- END --");

	*index = shaderId;
}

void Loader::loadFragmentShader(std::string path, GLuint * index){
	GLuint shaderId = glCreateShader(GL_FRAGMENT_SHADER);    //holds the index of the loaded shader
	std::string shaderData;    //holds the data from the loaded shader program

	std::ifstream file(path, std::ios::in);

	if(!file.is_open()){
		throw Defaults::Exception(Defaults::FILE_NOT_FOUND, "unable to open file\"" + path + "\" it might be missing or currupt");
	}

	Log::status("Loading Fragment Shader: " + path);

	while(file.good()){    //while the file is not at the end put its contents in var line then add line to shader data
		std::string line;
		std::getline(file, line);
		shaderData += "\n" + line;
	}

	file.close();    //all is well now the file can be closed

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

	//fancy printing
	Log::status("Compile Status:");
	Log::status("-- BEGIN --");
	Log::status(&shaderStatus[0]);
	Log::status("-- END --");

	*index = shaderId;
}

void Loader::loadShader(std::string vertex, std::string fragment, GLuint * programId){
	GLuint fragmentShaderId = 0, vertexShaderId = 0;	//holds the indevidual shaders

	//load dem shaders
	try{
		Loader::loadVertexShader(vertex, &vertexShaderId);
		Log::status("");
	}catch(Defaults::Exception e){
		throw Defaults::Exception(Defaults::CANNOT_LOAD_VERTEX_SHADER, e.description);
	}
	try{
		Loader::loadFragmentShader(fragment, &fragmentShaderId);
		Log::status("");
	}catch(Defaults::Exception e){
		throw Defaults::Exception(Defaults::CANNOT_LOAD_FRAGMENT_SHADER, e.description);
	}

	//git dem shaders and link em
	try{
		Loader::linkShader(vertexShaderId, fragmentShaderId, programId);
	}catch(Defaults::Exception e){
		throw Defaults::Exception(Defaults::CANNOT_LINK_SHADERS, e.description);
	}

	//now that the program has been compiled and linked the individual shaders can be deleted. SO LETS DELETE THEM!
	glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

void Loader::linkShader(GLuint vert, GLuint frag, GLuint * programId){
	Log::status("Linking Shaders");

	GLint result = GL_FALSE;
	int logLength;

	//create and link new program
	*programId = glCreateProgram();
	glAttachShader(*programId, vert);
	glAttachShader(*programId, frag);
	glLinkProgram(*programId);

	//check to make sure it linked correctaly
	glGetProgramiv(*programId, GL_LINK_STATUS, &result);
	glGetProgramiv(*programId, GL_INFO_LOG_LENGTH, &logLength);

	//print message
	Log::status("Link Status:");
	if (logLength > 0){
		std::vector<char> shaderStatusMessage(logLength + 1);
		glGetProgramInfoLog(*programId, logLength, NULL, &shaderStatusMessage[0]);
		Log::status("-- BEGIN --");
		Log::status(&shaderStatusMessage[0]);
		Log::status("-- END --");
	}else{
		Log::status("NO STATUS FOR SHADER");
	}
}

void readPngData(png_structp pngPtr, png_bytep data, png_size_t length){
	//function called by libpng to load data

	png_voidp steam = png_get_io_ptr(pngPtr);	//get ifsteam back from libpng
	((std::istream*)steam)->read((char*)data, length);	//read the data using ifsteam
}