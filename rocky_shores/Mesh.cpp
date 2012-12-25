#include "Mesh.h"
#include <array>

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
	faces.push_back(f);    //add the face to the list, prettys simple

	
}