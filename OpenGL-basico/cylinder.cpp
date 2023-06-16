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
	if(t1 < t2)
		t= t1;
	else
		t= t2;

	float z1 = av.z + t1 * rayo.dir.z;
	float z2 = av.z + t2 * rayo.dir.z;
	float t3 = (- av.z) / rayo.dir.z;
	float t4 = (altura - av.z) / rayo.dir.z;
	if (((z1 < - EPS && z2> + EPS) || (z2 < - EPS && z1> + EPS))&&(rayo.origin.z < position.z)) t = t3;
	if (((z1 <altura - EPS && z2> altura + EPS) || (z2 < altura - EPS && z1> altura + EPS)) && (rayo.origin.z > position.z)) t = t4;
	*hitPoint = rayo.origin + (rayo.dir * t);
	if (hitPoint->z > altura + position.z + EPS || hitPoint->z < 0 + position.z - EPS) return false;
	if (t == t3) *norm = vec3(0, 0, -1);
	if (t == t4) *norm = vec3(0, 0, 1);
	if (t == t1 || t == t2) {
		*norm = (vec3(hitPoint->x, hitPoint->y, 0.0) - vec3(position.x, position.y, 0.0));
		*norm = *norm * (1 / norma(*norm));
	};
	return true;
}