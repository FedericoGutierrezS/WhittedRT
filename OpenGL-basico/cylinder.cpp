#include "cylinder.h"
#include <algorithm>

using namespace std;

bool  Cilindro::intersectRay(ray rayo, vec3* norm, vec3* hitPoint) {
	vec3 av = rayo.origin - position;
	float a = pow(rayo.dir.x, 2) + pow(rayo.dir.z, 2);
	float b = 2* av.x*rayo.dir.x + 2 * av.z * rayo.dir.z;
	float c = pow(av.x, 2) + pow(av.z, 2) - pow(radio,2);
	float t1 = 1000, t2 = 1000;
	if ((pow(b, 2) - 4 * a * c) > 0) {
		t1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		t2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	}
	else return false;
	float t;
	if(abs(t1) < abs(t2))
		t= t1;
	else
		t= t2;
	*hitPoint = rayo.origin - (rayo.dir * t);
	if (hitPoint->y > this->altura - av.y || hitPoint->y < 0 - av.y) return false;
	return true;
}