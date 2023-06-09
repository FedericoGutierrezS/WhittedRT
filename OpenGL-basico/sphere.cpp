#include "sphere.h"
#include <iostream>

Esfera*  Esfera::intersectRay(ray rayo, vec3 *norm, vec3* hitPoint) {
	vec3 a = rayo.origin - position;
	float delta = pow((rayo.dir * a), 2) - (pow(norma(a), 2) - pow(radius, 2));
	if (delta > 0) {
		float d1 = -(rayo.dir * a) + sqrt(delta);
		float d2 = -(rayo.dir * a) - sqrt(delta);
		hitPoint = rayo.origin + rayo.dir * fminf(d1, d2);
		*norm = (position - hitPoint) * (-1);
		*norm = *norm * (1 / norma(norm));
		return this;
	}
	else return nullptr;
}