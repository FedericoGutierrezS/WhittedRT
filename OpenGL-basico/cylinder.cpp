#include "cylinder.h"
#include <algorithm>

using namespace std;

bool  Cilindro::intersectRay(ray rayo, vec3* norm, vec3* hitPoint) {
	vec3 av = rayo.origin - position;
	float a = pow(rayo.dir.x, 2) + pow(rayo.dir.y, 2);
	float b = 2* av.x*rayo.dir.x + 2 * av.y * rayo.dir.y;
	float c = pow(av.x, 2) + pow(av.y, 2) - pow(radio,2);
	float t1 = 1000, t2 = 1000;
	if ((pow(b, 2) - 4 * a * c) > 0) {
		t1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		t2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	}
	else return false;
	float t;
	if (t1 > t2)
		if (t2 > 0) t = t2;
		else t = t1;
	if (t2 > t1)
		if (t1 > 0) t = t1;
		else t = t2;


	float z1 = av.z + t1 * rayo.dir.z;
	float z2 = av.z + t2 * rayo.dir.z;
	float t3 = (- av.z) / rayo.dir.z;
	float t4 = (altura - av.z) / rayo.dir.z;
	if (((z1 < - 0.00001 && z2> + 0.00001) || (z2 < - 0.00001 && z1> + 0.00001)) && (rayo.origin.z < position.z)) t = t3;
	if (((z1 <altura - 0.00001 && z2> altura + 0.00001) || (z2 < altura - 0.00001 && z1> altura + 0.00001)) && (rayo.origin.z > altura + position.z)) t = t4;
	*hitPoint = rayo.origin + (rayo.dir * t);
	if (hitPoint->z > altura + position.z + 0.00001 || hitPoint->z < 0 + position.z - 0.00001) return false;
	if (t == t3) *norm = vec3(0, 0, -1);
	if (t == t4) *norm = vec3(0, 0, 1);
	if (t == t1 || t == t2) {
		*norm = (vec3(hitPoint->x, hitPoint->y, 0.0) - vec3(position.x, position.y, 0.0));
		*norm = *norm * (1 / norma(*norm));
	};
	if (t < 0) return false;
	return true;
}