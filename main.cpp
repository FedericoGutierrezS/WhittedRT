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

vec3 traza_RR(ray rayo, int alt, Esfera e) {
	vec3* norm;
	vec3* hitPoint;
	vec3 res;
	res.x = 0;
	res.y = 0;
	res.z = 0;
	Esfera* k = e.intersectRay(rayo, norm, &hitPoint);
	if (k != nullptr) {
		res.x = 255 / norm.x;
		res.y = 255 / norm.x;
		res.z = 255;
	}
	return res;
};



int main(int argc, char *argv[]) {
	const int WIDTH = 2280;
	const int HEIGHT = 720;
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
	for (int i = 0; i < cam.resH; i++) {
		for (int j = 0; j < cam.resW; j++) {
			ray rayo;
			rayo.origin.x = cam.origin.x;
			rayo.origin.y = cam.origin.y;
			rayo.origin.z = cam.origin.z;
			rayo.dir.x = (rayo.origin.x + (2 / cam.resH) * i) - 1;
			rayo.dir.y = (rayo.origin.y + (2 / cam.resW) * j) - 1;
			rayo.dir.z = -1.0 / tan(cam.fov / 2.0);
			float normDirRay = sqrt(rayo.dir.x * rayo.dir.x + rayo.dir.y * rayo.dir.y + rayo.dir.z * rayo.dir.z);
			rayo.dir.x = rayo.dir.x / normDirRay;
			rayo.dir.y = rayo.dir.y / normDirRay;
			rayo.dir.z = rayo.dir.z / normDirRay;

			pixel = traza_RR(rayo, 1, *sphere1);

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
