#pragma once
#include "primitiva.h"

class Triangulo :public Primitive {
protected:
	vec3 A, B, C, normal;
public:
	Triangulo(vec3 a, vec3 b, vec3 c, material Mat) {
		this->A = a;
		this->B = b;
		this->C = c;
		this->mat = Mat;
		vec3 edge1, edge2;
		edge1 = this->A - this->B;
		edge2 = this->C - this->B;
		normal = cross(edge1, edge2);
		normal = normal * (1 / norma(normal));
	};
	bool intersectRay(ray &rayo, vec3* norm, vec3* hitPoint);

};
