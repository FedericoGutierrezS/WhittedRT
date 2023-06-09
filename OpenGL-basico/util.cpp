#include "util.h"

vec3 operator-(vec3 v, vec3 f) {
	vec3 res;
	res.x = v.x - f.x;
	res.y = v.y - f.y;
	res.z = v.z - f.z;
	return res;
}

vec3 operator+(vec3 v, vec3 f) {
	vec3 res;
	res.x = v.x + f.x;
	res.y = v.y + f.y;
	res.z = v.z + f.z;
	return res;
}

float operator*(vec3 v, vec3 f) {
	return v.x * f.x + v.y * f.y + v.z * f.z;
}

vec3 operator*(vec3 v, float a) {
	vec3 res;
	res.x = v.x * a;
	res.y = v.y * a;
	res.z = v.z * a;
	return res;
}

float norma(vec3 v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
};
