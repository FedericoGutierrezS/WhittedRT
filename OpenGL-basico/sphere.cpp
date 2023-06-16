#include "sphere.h"
#include <iostream>

bool  Esfera::intersectRay(ray rayo, vec3 *norm, vec3* hitPoint) {
	vec3 a = rayo.origin - position;
	float delta = pow((rayo.dir * a), 2) - (pow(norma(a), 2) - pow(radius, 2));
	if (delta >= 0) {
		float d1 = -(rayo.dir * a) + sqrt(delta);
		float d2 = -(rayo.dir * a) - sqrt(delta);
		if(d1>d2)
			*hitPoint =rayo.origin + rayo.dir * d2;
		else *hitPoint = rayo.origin + rayo.dir * d1;
		*norm = (position - *hitPoint);
		*norm = *norm * (1 / norma(*norm));
		return true;
	}
	else return false;
}