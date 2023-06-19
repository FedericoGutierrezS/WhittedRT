#include "plane.h"

bool  Plano::intersectRay(ray rayo, vec3* norm, vec3* hitPoint, float fMax) {
	vec3 Pn = vec3(A, B, C);
	float vd = Pn * rayo.dir;
	if (vd > 0) return false;
	float v0 = -((Pn * rayo.origin) + D);
	float t = v0 / vd;
	if (t < 0) return false;
	*hitPoint = vec3(rayo.origin + rayo.dir * t);
	*norm = Pn;
	return true;
}