#pragma once
#ifndef UTIL_H
#include "util.h"
#endif
#include <cmath>

class Primitive {
protected:
	vec3 position;
	material mat;
public:
	Primitive() {
	};
	vec3 getPos() { return position; };
	material getMat() { return mat; };
	void setMat(material mate) { mat = mate; };
	void setPos(vec3 pos) { position = pos; };
};