//Mesh.h / Mesh.cpp
//simple way to hold mesh data to be rendered or operated on
//the data is stored as an array of faces and an array of vertices
//the data can easily be converted to array of triangles, vbo, vao...
//this class is simply a fancy container for 3d / 2d mesh data

#pragma once
#include <glm\glm.hpp>

class Mesh{

public:
	Mesh(void);
	~Mesh(void);

};

