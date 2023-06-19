#include "sphere.h"
#include <iostream>

bool  Esfera::intersectRay(ray rayo, vec3* norm, vec3* hitPoint) {
	/*float a = 1;
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
		*norm = normalize(*hitPoint - position)
		return true;
	}
	else return false;*/
	vec3 V = rayo.origin - position;
	float a0 = (V * V) - radius * radius;
	float DdotV = rayo.dir * V;

	if (DdotV <= 0) {
		float discr = DdotV * DdotV - a0;
		if (discr >= 0) {
			float t = -DdotV - sqrt(discr);
			if(t < -0.00001) return false;
			*hitPoint = rayo.origin + (rayo.dir*t);
			*norm = normalize(*hitPoint - position);
			return true;
		}
	}
	return false;
}
