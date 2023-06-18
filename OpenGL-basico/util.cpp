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

vec3 mult(vec3 v, vec3 f) {
	vec3 res;
	res.x = v.x * f.x;
	res.y = v.y * f.y;
	res.z = v.z * f.z;
	return res;
}

vec3 reflect(vec3 v, vec3 n) {
	return n*(v * n)*2 - v;
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
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
};

vec3 cross(vec3 a, vec3 b) {
	return vec3(a.y * b.z - a.z * b.y, -1*(a.x * b.z - a.z * b.x), a.x * b.y - a.y * b.x);
}

vec3 normalize(vec3 a) {
	return a * (1 / norma(a));
}


vec2 operator-(vec2 v, vec2 f) {
	vec2 res;
	res.x = v.x - f.x;
	res.y = v.y - f.y;
	return res;
}

vec2 operator+(vec2 v, vec2 f) {
	vec2 res;
	res.x = v.x + f.x;
	res.y = v.y + f.y;
	return res;
}

float operator*(vec2 v, vec2 f) {
	return v.x * f.x + v.y * f.y;
}

vec2 operator*(vec2 v, float a) {
	vec2 res;
	res.x = v.x * a;
	res.y = v.y * a;
	return res;
}

float norma(vec2 v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
};
