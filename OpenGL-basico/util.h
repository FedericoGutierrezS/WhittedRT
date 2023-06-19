#pragma once
#include <cmath>
#ifndef UTIL_H
#define UTIL_H

struct vec3 {
	float x;
	float y;
	float z;
	vec3(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}
	vec3() {
		x = 0;
		y = 0;
		z = 0;
	}

};

struct vec2 {
	float x;
	float y;
	vec2(float a, float b) {
		x = a;
		y = b;
	}
	vec2() {
		x = 0;
		y = 0;
	}

};

struct ray {
	vec3 origin;
	vec3 dir;
};

struct material {
	vec3 diffuse;
	float specular;
	float IOR;
	float ks;
	float kss;
	float kd;
	float ka;
	float kt;
};

struct Light {
	vec3 position;
	vec3 intensity;
};

vec3 reflect(vec3 v, vec3 n);

vec3 operator-(vec3 v, vec3 f);

vec3 operator+(vec3 v, vec3 f);

float operator*(vec3 v, vec3 f);

vec3 operator*(vec3 v, float a);

vec3 mult(vec3 v, vec3 f);

vec3 normalize(vec3 a);

float norma(vec3 v);

vec3 cross(vec3, vec3);

vec2 operator-(vec2 v, vec2 f);

vec2 operator+(vec2 v, vec2 f);

float operator*(vec2 v, vec2 f);

vec2 operator*(vec2 v, float a);

float norma(vec2 v);

#endif