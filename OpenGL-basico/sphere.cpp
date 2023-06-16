#include "sphere.h"
#include <iostream>

bool  Esfera::intersectRay(ray rayo, vec3 *norm, vec3* hitPoint) {
	float a = rayo.dir * rayo.dir;
	float b = rayo.dir * (rayo.origin - position) * 2;
	float c = pow(norma(rayo.origin - position), 2) - pow(radius, 2);
	float delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0) {
		float d1 = -b + sqrt(delta);
		float d2 = -b - sqrt(delta);
		float d;
		if (d1 > d2 && d2 < 0) d = d1;
		if (d1 > d2 && d2 > 0) d = d2;
		if (d1 < d2 && d2 > 0) d = d1;
		if (d1 < d2 && d2 < 0) d = d2;
		*hitPoint = rayo.origin + rayo.dir * d;
		*norm = (position - *hitPoint)*(-1);
		*norm = *norm * (1 / norma(*norm));
		return true;
	}
	else return false;
}