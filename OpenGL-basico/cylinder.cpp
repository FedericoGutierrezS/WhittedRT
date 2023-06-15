#include "cylinder.h"
#include <algorithm>

using namespace std;

bool  Cilindro::intersectRay(ray rayo, vec3* norm, vec3* hitPoint) {
	vec3 av = rayo.origin - position;
	float eps = 0.0001;
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

	float y1 = av.y + t1 * rayo.dir.y;
	float y2 = av.y + t2 * rayo.dir.y;
	float t3 = (0 - av.y) / rayo.dir.y;
	if (((y1<0+eps && y2> 0-eps) || (y2<0+eps && y1> 0-eps)) && av.y < rayo.origin.y) t = t3;
	float t4 = (altura - av.y) / rayo.dir.y;
	if (((y1 < altura + eps && y2> altura - eps) || (y2 < altura + eps && y1> altura - eps)) && av.y >rayo.origin.y) t = t4;
	*hitPoint = rayo.origin + (rayo.dir * t);
	if (hitPoint->y > this->altura - av.y + eps || hitPoint->y < 0 - av.y - eps) return false;
	return true;
}