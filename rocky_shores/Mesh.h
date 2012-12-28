//Mesh.h / Mesh.cpp
//simple way to hold mesh data to be rendered or operated on
//the data is stored as an array of faces and vertecies, each face has a pointer to 3 glm vec3 variable
//the data can easily be converted to array of triangles, vbo, vao...
//this class is simply a fancy container for 3d / 2d mesh data

#pragma once
#include <glm\glm.hpp>
#include <vector>
#include "Log.h"

class Mesh{

public:
	//the struct face is a simple way to keep all the face data origanized, this is not meant to be read directally and should be interpreted or converted first
	struct face{
		glm::vec3 * cords[3];    //holds 3 pointers that should point to glm vec3 vertices, all faces must have the vertices defined, if they are null then... um... well.. lets hope that doesn't happen
		glm::vec2 * uv[3];    //array of 3d points point to 2d uv map cordinates, this is not required and can be left as null, if it is null then use a color instea of a texture
		glm::vec3 * normal[3];    //holds a pointer to the normal of each vertex
	};

	Mesh(void);    //this consturctor does nothing, not recomended
	Mesh(face f[]);    //takes an array of faces and uses them for the mesh
	~Mesh(void);

	void setMesh(face faces[]);    //removes all existing data and sets it to the given data
	void addFace(face f);    //adds the given face to the list and adds the vertex data to its list if it is not already given
	glm::vec3* asTriangleVertexArray(void);    //usefull for compiling vao and simple rendering, it returns all the vertices that are needed to draw every face in the mesh

	void resetData(void){    //reset all data in the vectors cord, uv, normal, and face
		cordList.clear();
		uvList.clear();
		normalList.clear();
		faces.clear();
	}
	
	//all simple one line functions are put in the header for simplicity
	//they just do operations on the list
	void addVertex(glm::vec3 vertexPosition){    //add vertex position to list
		cordList.push_back(vertexPosition);
	}
	void addUv(glm::vec2 uv){    //add vertex uv to list
		uvList.push_back(uv);
	}
	void addNormal(glm::vec3 normal){    //add vertex normal to list
		normalList.push_back(normal);
	}

private:
	//these lists hold all the data for the mesh (vertex, uv, normals)
	std::vector<glm::vec3> cordList;
	std::vector<glm::vec2> uvList;
	std::vector<glm::vec3> normalList;

	//holds all the faces in no order (the faces hold no data on their own, just pointers)
	std::vector<face> faces;
};