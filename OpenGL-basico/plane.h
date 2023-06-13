#pragma once
#include "primitiva.h"

class Plano :public Primitive {
protected:
	float A, B, C, D;
public:
	Plano(float a, float b, float c,float d, material Mat){
		this->A = a;
		this->B = b;
		this->C = c;
		this->D = d;
		this->mat = Mat;
	};
	bool intersectRay(ray rayo, vec3* norm, vec3* hitPoint, float fMax);

};