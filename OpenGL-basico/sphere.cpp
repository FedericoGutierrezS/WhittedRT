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
		float d;
		if (d1 > d2)
			if (d2 > 0) d = d2;
			else if (d1 < 0) d = d1;
			else d = d1;
		else
			if (d1 > 0) d = d1;
			else if (d2 < 0) d = d2;
			else d = d2;

		*hitPoint = rayo.origin + rayo.dir * d;
		*norm = (position - *hitPoint)*(-1);
		*norm = *norm * (1 / norma(*norm));
		return true;
	}
	else return false;
}
