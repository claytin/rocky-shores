#version 150

in vec3 vert;
//in vec3 vertexColor;

out vec4 fragmentColor;    //outputs color to fragment shader
//uniform mat4 MVP;

void main(){

    gl_Position = vec4(vert, 1);

    fragmentColor = vec4(1, 0, 1, 1);
}