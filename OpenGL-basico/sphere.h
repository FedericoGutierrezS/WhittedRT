#pragma once
#include "primitiva.h"

class Esfera:public Primitive{
protected:
	float radius;
public:
	Esfera(vec3 center, float radius, material mat){
		this->position = center;
		this->radius = radius;
		this->mat = mat;
	};
	bool intersectRay(ray rayo, vec3 *norm, vec3 *hitPoint);

};