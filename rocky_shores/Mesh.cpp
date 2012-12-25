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
	//at least all the vertices must have position data if not then the function  returns and the face is not added this
	//can cause graphical glitches but its better than crashing
	if(f.cords[0] != NULL && f.cords[1] != NULL && f.cords[2] != NULL){
		//well at least the face has its position data

		//so lets go though each vertex that the face has, if its already in the list then ignore it otherwise add it to the
		//list so we have a list full of every vertex ever used
		for(int i = 0; i < 3; i++){
			if(std::count(cordList.begin(), cordList.end(), *f.cords[i]) <= 0){
				//the vertex used in the face is not already in the cordList so lets add it
				cordList.push_back(*f.cords[i]);
			}
		}

		//now that the cords are squared away we can deal with uv and normal
		// the uv or normal is not required and can be null so lest check for that
		if(f.uv[0] == NULL || f.uv[1] == NULL || f.uv[2] == NULL){
			//at least one of the uvs are null so lets not deal with them
		}else{
			//if all the uvs have some value then they will be added using the same technieque as the cords
			for(int i = 0; i < 3; i++){
				if(std::count(uvList.begin(), uvList.end(), *f.uv[i]) <= 0){
					//the vertex used in the face is not already in the uvList so lets add it
					uvList.push_back(*f.uv[i]);
				}
			}
		}

		//and lastly check to see if it has normals (same process as uv)
		if(f.normal[0] == NULL || f.normal[1] == NULL || f.normal[2] == NULL){
			//one of the normals is null so lets not bother with them
		}else{
			for(int i = 0; i < 3; i++){
				if(std::count(normalList.begin(), normalList.end(), *f.normal[i]) <= 0){
					normalList.push_back(*f.normal[i]);
				}
			}
		}

	}else{
		//this should never happen, if it does then something is teribly wrong (the face will not be added and an error will be sent to the console)
		Log::error("one or more of the faces of the mesh is null, could cause rendering errors. This could be caused by corrupt file, read error...", __LINE__, __FILE__);
		return;    //causes the program never to add the face and thus causing the face to be ignored
	}


	faces.push_back(f);    //add the face to the list
}