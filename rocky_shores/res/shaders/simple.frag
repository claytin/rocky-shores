#version 330 core

//recieve color from vertex shader
in vec3 fragmentColor;

// Ouput data
out vec3 color;

void main(){

	color = fragmentColor;

}