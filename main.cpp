#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include "include/tinyxml2.h"
#ifndef UTIL_H
#include "OpenGL-basico/util.h"
#endif
#include "OpenGL-basico/sphere.h"
#include "OpenGL-basico/plane.h"
#include "OpenGL-basico/cylinder.h"
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

	Cilindro** c = col->getColCilindros();
	for (int i = 0; i < col->getCantCilindros(); i++) {
		j = c[i]->intersectRay(rayo, norm, hitPoint);
		if (j && norma(*hitPoint) < norma(hitPoint_min)) {
			hitPoint_min = *hitPoint;
			norm_min = *norm;
			intersect = true;
			hit = c[i];
		}
	}

	Triangulo** t = col->getColTriangulos();
	for (int i = 0; i < col->getCantTriangulos(); i++) {
		j = t[i]->intersectRay(rayo, norm, hitPoint);
		if (j && norma(*hitPoint) < norma(hitPoint_min)) {
			hitPoint_min = *hitPoint;
			norm_min = *norm;
			intersect = true;
			hit = t[i];
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
	if (inter != NULL) {
		res.x = norm.x*255;
		res.y = norm.y * 255;
		res.z = norm.z * 255;
	}
	return res;
};



int main(int argc, char *argv[]) {
	FreeImage_Initialise();
	XMLDocument doc;
	doc.LoadFile("../settings.xml");

	ColObjetos* col = NULL;
	col = col->getInstance();

	XMLElement* settings = doc.FirstChildElement();
	col->inicializarCol(settings->FloatAttribute("spheres") , settings->FloatAttribute("planes"), settings->FloatAttribute("cilinders"), settings->FloatAttribute("tris"));
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

	material mat;

	XMLElement* spheres = settings->FirstChild()->NextSibling()->FirstChildElement();

	vec3 center;
	float radius;
	XMLElement* obPos = spheres->FirstChildElement();

	for (int i = 0; i < col->getCantEsferasTot(); i++) {
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
		col->agregarEsfera(new Esfera(center, radius, mat));
		spheres = spheres->NextSiblingElement();
	}

	XMLElement* planes = settings->FirstChild()->NextSibling()->NextSibling()->FirstChildElement();
	float a, b, c, d;

	for(int i = 0; i < col->getCantPlanosTot(); i++) {
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
		col->agregarPlano(new Plano(a, b, c, d, mat));
		planes = planes->NextSiblingElement();
	}
	
	XMLElement* cyls = settings->FirstChild()->NextSibling()->NextSibling()->NextSibling()->FirstChildElement();
	vec3 vpos;
	float altura;

	for (int i = 0; i < col->getCantCilindrosTot(); i++) {
		mat.reflective = cyls->FloatAttribute("refl");
		mat.refractive = cyls->FloatAttribute("refr");
		mat.specular = cyls->FloatAttribute("specular");
		mat.IOR = cyls->FloatAttribute("IOR");
		mat.diffuse.x = cyls->FloatAttribute("colorR");
		mat.diffuse.y = cyls->FloatAttribute("colorG");
		mat.diffuse.z = cyls->FloatAttribute("colorB");
		obPos = cyls->FirstChildElement();
		vpos.x = obPos->FloatAttribute("posx");
		vpos.y = obPos->FloatAttribute("posy");
		vpos.z = obPos->FloatAttribute("posz");
		radius = obPos->FloatAttribute("radius");
		altura = obPos->FloatAttribute("alt");
		col->agregarCilindro(new Cilindro(vpos, radius, altura, mat));
		cyls = cyls->NextSiblingElement();
	}
	XMLElement* tris = settings->FirstChild()->NextSibling()->NextSibling()->NextSibling()->NextSibling()->FirstChildElement();
	vec3 v1, v2, v3;

	for (int i = 0; i < col->getCantTriangulosTot(); i++) {
		mat.reflective = tris->FloatAttribute("refl");
		mat.refractive = tris->FloatAttribute("refr");
		mat.specular = tris->FloatAttribute("specular");
		mat.IOR = tris->FloatAttribute("IOR");
		mat.diffuse.x = tris->FloatAttribute("colorR");
		mat.diffuse.y = tris->FloatAttribute("colorG");
		mat.diffuse.z = tris->FloatAttribute("colorB");
		obPos = tris->FirstChildElement();
		v1.x = obPos->FloatAttribute("v1x");
		v1.y = obPos->FloatAttribute("v1y");
		v1.z = obPos->FloatAttribute("v1z");
		v2.x = obPos->FloatAttribute("v2x");
		v2.y = obPos->FloatAttribute("v2y");
		v2.z = obPos->FloatAttribute("v2z");
		v3.x = obPos->FloatAttribute("v3x");
		v3.y = obPos->FloatAttribute("v3y");
		v3.z = obPos->FloatAttribute("v3z");
		col->agregarTriangulo(new Triangulo(v1,v2,v3, mat));
		tris = tris->NextSiblingElement();
	}
	mat.diffuse.z = 255;
	FIBITMAP* bitmap = FreeImage_Allocate(cam.resW, cam.resH, 24);
	RGBQUAD color;
	vec3 pixel;
	ray rayo;
	float camRatio = cam.resW / cam.resH;
	
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
