#include "sphere.h"
#include <iostream>

bool  Esfera::intersectRay(ray rayo, vec3* norm, vec3* hitPoint) {
	float a = 1;
	float b = rayo.dir * 2 * (rayo.origin - position);
	float c = pow(norma(rayo.origin - position), 2) - pow(radius, 2);
	float delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0) {
		float d1 = ( - b + sqrt(delta))/2*a;
		float d2 = ( - b - sqrt(delta))/2*a;
		float d = 0;
		if (d1 > d2)
			if (d2 > 0) d = d2;
			else d = d1;
		if (d2 > d1)
			if (d1 > 0) d = d1;
			else d = d2;

		*hitPoint = rayo.origin + rayo.dir * d;
		*norm = (*hitPoint - position) * (1 / radius);
		if (norma(*hitPoint - position ) + 0.00001 < radius) *norm = *norm * -1;
		return true;
	}
	else return false;
}
