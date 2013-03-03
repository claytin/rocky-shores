#include "Mesh.h"

Mesh::Mesh(void){

}

Mesh::Mesh(face faces []){
	setMesh(faces);
}

Mesh::~Mesh(void){

}

void Mesh::setMesh(face faces[]){
	int faceCount = sizeof(faces) / sizeof(face);    //gets the length of the array (the number of faces)

	//clear all the data
	resetData();

	//go through each face in the array and added it to the main mesh
	for(int i = 0; i < faceCount; i++){
		addFace(faces[i]);
	}

	//well it looks like everything is done
	return;    //absolutaly 9001% compleatly necessary or else this won't work 
}

void Mesh::addFace(face f){
	//at least all the vertices must have position data if not then the function  returns and the face is not added this
	//can cause graphical glitches but its better than crashing
	
	for(int i = 0; i < 3; i++){
		addCords(*f.cord[i]);
	}for(int i = 0; i < 3; i++){
		//addUv(*f.uv[i]);
	}for(int i = 0; i < 3; i++){
		//addNormal(*f.normal[i]);
	}

	faces.push_back(f);    //add the face to the list
}

glm::vec3* Mesh::asTriangleVertexArray(void){
	int vertexCount = 3 * faces.size();    //each face has 3 vertices so face # * 3 is the number of vertices in the entire mesh
	glm::vec3 * vertexArray = new glm::vec3[vertexCount];    //this will hold the array that is returned

	int vertexIndex = 0;    //the curent vertex that will be "added" / set in the array
	//go though all the faces and then each faces vertices witch will be "added" (there is no real adding in arrays, all it does its sets its value) to the array
	for(unsigned int face = 0; face < faces.size(); face++){
		for(int vert = 0; vert < 3; vert++){
			vertexArray[vertexIndex] = *faces.at(face).cord[vert];
			vertexIndex++;    //move onto the next vertex
		}
	}

	//now that all the vertecies have been gathered in a array lets return them
	return vertexArray;
}

float* Mesh::asTriangleFloatArray(void){
	int vertexCount = 3 * faces.size();    //the total number of vertices in the entire mesh
	float * vertexArray = new float[vertexCount * 3];    //the array that will be returned

	glm::vec3 * glmVertexArray = asTriangleVertexArray();    //the individual verteces will be extracted from this

	int currentVertex = 0;
	for(int i = 0; i < vertexCount; i++){
		vertexArray[currentVertex] = glmVertexArray[i].x;
		currentVertex++;
		vertexArray[currentVertex] = glmVertexArray[i].y;
		currentVertex++;
		vertexArray[currentVertex] = glmVertexArray[i].z;
		currentVertex++;

		
	}



	return vertexArray;
}