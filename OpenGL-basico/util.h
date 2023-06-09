#pragma once
#include <cmath>
#ifndef UTIL_H
#define UTIL_H

struct vec3 {
	float x = 0;
	float y = 0;
	float z = 0;
};

struct ray {
	vec3 origin;
	vec3 dir;
};

struct material {
	vec3 diffuse;
	float specular;
	float reflective;
	float refractive;
	float IOR;
};

vec3 operator-(vec3 v, vec3 f);

vec3 operator+(vec3 v, vec3 f);

float operator*(vec3 v, vec3 f);

vec3 operator*(vec3 v, float a);

float norma(vec3 v);

#endif