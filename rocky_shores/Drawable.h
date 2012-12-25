//Drawable.h / Drawable.cpp
//base class for any sprite or object that can be rendered
//has position, a mesh, and optionaly texture or color

#pragma once
#include <glm\glm.hpp>
#include "Mesh.h"

class Drawable{

public:
	Drawable(void);
	~Drawable(void);

private:
	glm::mat4 cords;
};

