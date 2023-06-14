#include "triangle.h"
#include <iostream>

bool  Triangulo::intersectRay(ray rayo, vec3* norm, vec3* hitPoint) {
	vec3 e1 = this->B - this->A;
	vec3 e2 = this->C - this->A;
	vec3 q = cross(rayo.dir, e2);
	float a = q * e1;
	if (a > -0.001 && a < 0.001) return false;
	float f = 1 / a;
	vec3 s = rayo.origin - this->A;
	float u = (s * q) * f;
	if (u < 0.0) return false;
	vec3 r = cross(s, e1);
	float v = (rayo.dir * r) * f;
	if (v < 0.0 || u + v > 1.0) return false;
	float t = (e2 * r) * f;
	*hitPoint = rayo.origin + (rayo.dir * t);
	return true;
}
