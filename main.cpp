#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include "include/tinyxml2.h"
#ifndef UTIL_H
#include "OpenGL-basico/util.h"
#endif
#include "OpenGL-basico/sphere.h"

using namespace std;
using namespace tinyxml2;

struct camera {
	vec3 origin;
	vec3 look;
	float resW;
	float resH;
	float fov;
};

vec3 traza_RR(ray rayo, int alt, Esfera** e) {
	vec3* norm = new vec3;
	vec3* hitPoint = new vec3;
	vec3 res;
	res.x = 0;
	res.y = 0;
	res.z = 0;
	Esfera* k = NULL;
	for (int i = 0; i < 2; i++) {
		if (k == NULL) k = e[i]->intersectRay(rayo, norm, hitPoint);
	}
	if (k != nullptr) {
		res.x = 255 / abs(norm->x);
		res.y = 255 / abs(norm->y);
		res.z = 255 / abs(norm->z);
	}
	return res;
};



int main(int argc, char *argv[]) {
	FreeImage_Initialise();
	XMLDocument doc;
	doc.LoadFile("../settings.xml");
	XMLElement* settings = doc.FirstChildElement();
	camera cam;
	XMLElement* camera = settings->FirstChildElement();
	cam.resW = camera->FloatAttribute("resW");
	cam.resH = camera->FloatAttribute("resH");
	cam.fov = camera->FloatAttribute("fov");
	camera = camera->FirstChildElement();
	cam.look.x = camera->FloatAttribute("x");
	cam.look.y = camera->FloatAttribute("y");
	cam.look.z = camera->FloatAttribute("z");
	camera = camera->NextSiblingElement();
	cam.origin.x = camera->FloatAttribute("x");
	cam.origin.y = camera->FloatAttribute("y");
	cam.origin.z = camera->FloatAttribute("z");

	XMLElement* spheres = settings->FirstChild()->NextSibling()->FirstChildElement();
	material mat;
	mat.reflective = spheres->FloatAttribute("refl");
	mat.refractive = spheres->FloatAttribute("refr");
	float radius = spheres->FloatAttribute("radius");
	mat.specular = spheres->FloatAttribute("specular");
	mat.IOR = spheres->FloatAttribute("IOR");
	mat.diffuse.x = spheres->FloatAttribute("colorR");
	mat.diffuse.y = spheres->FloatAttribute("colorG");
	mat.diffuse.z = spheres->FloatAttribute("colorB");
	XMLElement* obPos = spheres->FirstChildElement();
	vec3 center;
	center.x = obPos->FloatAttribute("x");
	center.y = obPos->FloatAttribute("y");
	center.z = obPos->FloatAttribute("z");
	Esfera* sphere1 = new Esfera(center,radius,mat);
	
	spheres = spheres->NextSiblingElement();

	mat.reflective = spheres->FloatAttribute("refl");
	mat.refractive = spheres->FloatAttribute("refr");
	radius = spheres->FloatAttribute("radius");
	mat.specular = spheres->FloatAttribute("specular");
	mat.IOR = spheres->FloatAttribute("IOR");
	mat.diffuse.x = spheres->FloatAttribute("colorR");
	mat.diffuse.y = spheres->FloatAttribute("colorG");
	mat.diffuse.z = spheres->FloatAttribute("colorB");
	obPos = spheres->FirstChildElement();
	center;
	center.x = obPos->FloatAttribute("x");
	center.y = obPos->FloatAttribute("y");
	center.z = obPos->FloatAttribute("z");
	Esfera* sphere2 = new Esfera(center, radius, mat);

	FIBITMAP* bitmap = FreeImage_Allocate(cam.resW, cam.resH, 24);
	RGBQUAD color;
	vec3 pixel;
	Esfera** arr = new Esfera*[2];
	arr[0] = sphere1;
	arr[1] = sphere2;
	float camRatio = cam.resW / cam.resH;
	for (int i = 0; i < cam.resH; i++) {
		for (int j = 0; j < cam.resW; j++) {
			ray rayo;
			rayo.origin.x = cam.origin.x;
			rayo.origin.y = cam.origin.y;
			rayo.origin.z = cam.origin.z;
			rayo.dir.x = ((rayo.origin.x + (2 / cam.resW) * j) - 1)*camRatio;
			rayo.dir.y = ((rayo.origin.y + (2 / cam.resH) * i) - 1) ;
			rayo.dir.z = -1.0 / tan(cam.fov / 2.0);
			rayo.dir = rayo.dir*(1/norma(rayo.dir));

			pixel = traza_RR(rayo, 1, arr);

			color.rgbRed = pixel.x;
			color.rgbGreen = pixel.y;
			color.rgbBlue = pixel.z;
			FreeImage_SetPixelColor(bitmap, j,i , &color);
		}
	}
	FreeImage_Save(FIF_PNG, bitmap, "test.png", 0);
	FreeImage_DeInitialise();
	return 0;
}
