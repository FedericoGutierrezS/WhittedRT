#pragma once
#include "primitiva.h"

class Cilindro :public Primitive {
protected:
	float radio;
	float altura;
public:
	Cilindro(vec3 center, float radius, float alt, material mat) {
		this->position = center;
		this->radio = radius;
		this->altura = alt;
		this->mat = mat;
	};
	bool intersectRay(ray rayo, vec3* norm, vec3* hitPoint);

};