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
	/* tst
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
	*/

	faces.push_back(f);    //add the face to the list
}

glm::vec3* Mesh::asTriangleVertexArray(void){
	int vertexCount = 3 * faces.size();    //each face has 3 vertices so face # * 3 is the number of vertices in the entire mesh
	glm::vec3 * vertexArray = new glm::vec3[vertexCount];    //this will hold the array that is returned

	int vertexIndex = 0;    //the curent vertex that will be "added" / set in the array
	//go though all the faces and then each faces vertices witch will be "added" (there is no real adding in arrays, all it does its sets its value) to the array
	for(int face = 0; face < faces.size(); face++){
		for(int vert = 0; vert < 3; vert++){
			vertexArray[vertexIndex] = *faces.at(face).cords[vert];
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
	
	for (int i = 0; i < vertexCount * 3; i++){
		std::cout << vertexArray[i] << std::endl;
	}

	return vertexArray;
}