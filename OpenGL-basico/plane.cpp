#include "plane.h"

bool  Plano::intersectRay(ray rayo, vec3* norm, vec3* hitPoint, float fMax) {
	vec3 N(this->A, this->B, this->C);
	float DrD = N * rayo.dir;
	float DrO = N * rayo.origin;
	float f = -(this->D + DrO) / DrD;
	if (f > fMax || DrD > 0) return false;
	
	else {
		*hitPoint = rayo.origin + rayo.dir * f;
		*norm = normalize(N);
		return true;
	}
}