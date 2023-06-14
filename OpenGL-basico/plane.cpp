#include "plane.h"

bool  Plano::intersectRay(ray rayo, vec3* norm, vec3* hitPoint, float fMax) {
	vec3 N(this->A, this->B, this->C);
	float DrD = N * rayo.dir;
	float DrO = N * rayo.origin;
	float f = (-this->D - DrO) / DrD;
	if (abs(f) > fMax || f > 0) return false;
	
	else {
		*hitPoint = rayo.origin + (rayo.dir * f);
		*norm = N*( 1/ norma(N));
		return true;
	}
}