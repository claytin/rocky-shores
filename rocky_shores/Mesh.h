//Mesh.h / Mesh.cpp
//simple way to hold mesh data to be rendered or operated on
//the data is stored as an array of faces and vertecies, each face has a pointer to 3 glm vec3 variable
//the data can easily be converted to array of triangles, vbo, vao...
//this class is simply a fancy container for 3d / 2d mesh data

#pragma once
#include <glm\glm.hpp>

class Mesh{

public:
	Mesh(void);
	~Mesh(void);

	//the struct face is a simple way to keep all the face data origanized, this is not meant to be read directally and should be interpreted or converted first
	struct face{
		glm::vec3 * vertexCords[3];    //holds 3 pointers that should point to glm vec3 vertices, all faces must have the vertices defined, if they are null then... um... well.. lets hope that doesn't happen
		glm::vec2 * uvCords[3];    //array of 3d points point to 2d uv map cordinates, this is not required and can be left as null, if it is null then use a color instea of a texture
		glm::vec3 * vertexNormal[3];    //holds a pointer to the normal of each vertex
	};

private:
	
};

