#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include "include/tinyxml2.h"
#ifndef UTIL_H
#include "OpenGL-basico/util.h"
#endif
#include "OpenGL-basico/sphere.h"
#include "OpenGL-basico/plane.h"
#include "OpenGL-basico/ColeccionObjetos.h"

using namespace std;
using namespace tinyxml2;

struct camera {
	vec3 origin;
	vec3 look;
	float resW;
	float resH;
	float fov;
};

Primitive* intersect(ray rayo,vec3 &normalO,vec3 &hitPointO) {
	vec3* norm = new vec3(100, 100, 100);
	vec3* hitPoint = new vec3(100, 100, 100);
	vec3 hitPoint_min(100, 100, 100);
	vec3 norm_min(100, 100, 100);
	Primitive* hit;
	bool intersect = false;
	bool j = false;
	ColObjetos* col = NULL;
	col = col->getInstance();
	Esfera** e = col->getColEsferas();
	intersect = e[0]->intersectRay(rayo, norm, hitPoint);
	norm_min = *norm;
	hitPoint_min = *hitPoint;
	hit = e[0];
	for (int i = 1; i < col->getCantEsferas(); i++) {
		j = e[i]->intersectRay(rayo, norm, hitPoint);
		if (j && norma(*hitPoint) < norma(hitPoint_min)) {
			hitPoint_min = *hitPoint;
			norm_min = *norm;
			intersect = true;
			hit = e[i];
		}
	}
	Plano** p = col->getColPlanos();
	for (int i = 0; i < col->getCantPlanos(); i++) {
		j = p[i]->intersectRay(rayo, norm, hitPoint, 7);
		if (j && norma(*hitPoint) < norma(hitPoint_min)) {
			hitPoint_min = *hitPoint;
			norm_min = *norm;
			intersect = true;
			hit = p[i];
		}
	}
	if (intersect) {
		normalO = norm_min;
		hitPointO = hitPoint_min;
		return hit;
	}
	else return NULL;
}

vec3 traza_RR(ray rayo, int alt) {
	vec3 res;
	res.x = 0;
	res.y = 0;
	res.z = 0;
	vec3 norm, hitPoint;
	Primitive* inter = intersect(rayo, norm, hitPoint);
	if (inter != NULL) {//(((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
		res.x = 255*norm.x; //inter->getMat().diffuse.x;
		res.y = 255*norm.y; //inter->getMat().diffuse.y;
		res.z = 255*norm.z; //inter->getMat().diffuse.z
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

	XMLElement* planes = settings->FirstChild()->NextSibling()->NextSibling()->FirstChildElement();

	mat.reflective = planes->FloatAttribute("refl");
	mat.refractive = planes->FloatAttribute("refr");
	mat.specular = planes->FloatAttribute("specular");
	mat.IOR = planes->FloatAttribute("IOR");
	mat.diffuse.x = planes->FloatAttribute("colorR");
	mat.diffuse.y = planes->FloatAttribute("colorG");
	mat.diffuse.z = planes->FloatAttribute("colorB");
	obPos = planes->FirstChildElement();
	float a, b, c, d;
	a = obPos->FloatAttribute("A");
	b = obPos->FloatAttribute("B");
	c = obPos->FloatAttribute("C");
	d = obPos->FloatAttribute("D");
	Plano* plane1 = new Plano(a,b,c,d,mat);

	planes = planes->NextSiblingElement();

	mat.reflective = planes->FloatAttribute("refl");
	mat.refractive = planes->FloatAttribute("refr");
	mat.specular = planes->FloatAttribute("specular");
	mat.IOR = planes->FloatAttribute("IOR");
	mat.diffuse.x = planes->FloatAttribute("colorR");
	mat.diffuse.y = planes->FloatAttribute("colorG");
	mat.diffuse.z = planes->FloatAttribute("colorB");
	obPos = planes->FirstChildElement();
	a = obPos->FloatAttribute("A");
	b = obPos->FloatAttribute("B");
	c = obPos->FloatAttribute("C");
	d = obPos->FloatAttribute("D");
	Plano* plane2 = new Plano(a, b, c, d, mat);

	planes = planes->NextSiblingElement();

	mat.reflective = planes->FloatAttribute("refl");
	mat.refractive = planes->FloatAttribute("refr");
	mat.specular = planes->FloatAttribute("specular");
	mat.IOR = planes->FloatAttribute("IOR");
	mat.diffuse.x = planes->FloatAttribute("colorR");
	mat.diffuse.y = planes->FloatAttribute("colorG");
	mat.diffuse.z = planes->FloatAttribute("colorB");
	obPos = planes->FirstChildElement();
	a = obPos->FloatAttribute("A");
	b = obPos->FloatAttribute("B");
	c = obPos->FloatAttribute("C");
	d = obPos->FloatAttribute("D");
	Plano* plane3 = new Plano(a, b, c, d, mat);

	planes = planes->NextSiblingElement();

	mat.reflective = planes->FloatAttribute("refl");
	mat.refractive = planes->FloatAttribute("refr");
	mat.specular = planes->FloatAttribute("specular");
	mat.IOR = planes->FloatAttribute("IOR");
	mat.diffuse.x = planes->FloatAttribute("colorR");
	mat.diffuse.y = planes->FloatAttribute("colorG");
	mat.diffuse.z = planes->FloatAttribute("colorB");
	obPos = planes->FirstChildElement();
	a = obPos->FloatAttribute("A");
	b = obPos->FloatAttribute("B");
	c = obPos->FloatAttribute("C");
	d = obPos->FloatAttribute("D");
	Plano* plane4 = new Plano(a, b, c, d, mat);

	planes = planes->NextSiblingElement();

	mat.reflective = planes->FloatAttribute("refl");
	mat.refractive = planes->FloatAttribute("refr");
	mat.specular = planes->FloatAttribute("specular");
	mat.IOR = planes->FloatAttribute("IOR");
	mat.diffuse.x = planes->FloatAttribute("colorR");
	mat.diffuse.y = planes->FloatAttribute("colorG");
	mat.diffuse.z = planes->FloatAttribute("colorB");
	obPos = planes->FirstChildElement();
	a = obPos->FloatAttribute("A");
	b = obPos->FloatAttribute("B");
	c = obPos->FloatAttribute("C");
	d = obPos->FloatAttribute("D");
	Plano* plane5 = new Plano(a, b, c, d, mat);

	FIBITMAP* bitmap = FreeImage_Allocate(cam.resW, cam.resH, 24);
	RGBQUAD color;
	vec3 pixel;
	ray rayo;
	float camRatio = cam.resW / cam.resH;
	ColObjetos* col = NULL;
	col = col->getInstance();
	col->inicializarCol(3, 3, 3, 3);
	col->agregarEsfera(sphere1);
	col->agregarEsfera(sphere2);
	col->agregarPlano(plane1);
	col->agregarPlano(plane2);
	col->agregarPlano(plane3);
	col->agregarPlano(plane4);
	col->agregarPlano(plane5);
	for (int i = 0; i < cam.resH; i++) {
		for (int j = 0; j < cam.resW; j++) {
			rayo.origin.x = cam.origin.x;
			rayo.origin.y = cam.origin.y;
			rayo.origin.z = cam.origin.z;
			rayo.dir.x = ((rayo.origin.x + (2 / cam.resW) * j) - 1)*camRatio;
			rayo.dir.y = ((rayo.origin.y + (2 / cam.resH) * i) - 1) ;
			rayo.dir.z = -1.0 / tan(cam.fov / 2.0);
			rayo.dir = rayo.dir*(1/norma(rayo.dir));
			pixel = traza_RR(rayo, 1);
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
