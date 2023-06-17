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

struct Light {
	vec3 position;
	vec3 dir;
	vec3 intensity;
	vec3 color;
};

Primitive* intersect(ray rayo,vec3 &normalO,vec3 &hitPointO) {
	vec3* norm = new vec3(100, 100, 100);
	vec3* hitPoint = new vec3(100, 100, 100);
	vec3 hitPoint_min(100, 100, 100);
	vec3 norm_min(100, 100, 100);
	Primitive* hit = NULL;
	bool intersect = false;
	float tnear;
	float tnearK;
	bool j = false;
	ColObjetos* col = NULL;
	col = col->getInstance();
	Esfera** e = col->getColEsferas();
	for (int i = 0; i < col->getCantEsferas(); i++) {
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
	else {
		normalO = vec3(0, 0, 0);
		hitPointO = vec3(100, 100, 100);
		return NULL;
	}
}

Primitive* intersectS(ray rayo, vec3& normalO, vec3& hitPointO) {
	vec3* norm = new vec3(100, 100, 100);
	vec3* hitPoint = new vec3(100, 100, 100);
	vec3 hitPoint_min(100, 100, 100);
	vec3 norm_min(100, 100, 100);
	Primitive* hit = NULL;
	bool intersect = false;
	float tnear;
	float tnearK;
	bool j = false;
	ColObjetos* col = NULL;
	col = col->getInstance();
	Esfera** e = col->getColEsferas();
	for (int i = 0; i < col->getCantEsferas(); i++) {
		j = e[i]->intersectRayS(rayo, norm, hitPoint);
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
	else {
		normalO = vec3(0, 0, 0);
		hitPointO = vec3(100, 100, 100);
		return NULL;
	}
}


vec3 sombra_RR(Primitive* obj, ray rayo, vec3 hitPoint, vec3 normal, int alt, Light* light) {
	ray rayoSombra;
	if(rayo.dir*normal <= 0 + 0.00001) rayoSombra.origin = hitPoint + normal*0.00001;
	else rayoSombra.origin = hitPoint - normal * 0.00001;
	rayoSombra.dir = normalize(light->position - rayoSombra.origin);
	vec3 hitSombra, normalSombra;
	Primitive* a = intersectS(rayoSombra, normalSombra, hitSombra);
	vec3 L = normalize(light->position - rayoSombra.origin);
	float fctr = normal * L;
	float ka = 0.2;
	float kd = 0.6;
	if ((a != NULL && (norma(rayoSombra.origin - hitSombra + normalSombra * 0.00001) < norma(rayoSombra.origin - light->position)) && norma(light->position - hitSombra+normalSombra*0.00001) < norma(rayoSombra.origin - light->position))|| fctr<0) {
		return obj->getMat().diffuse * ka;
	}
	else {
		vec3 V = normalize(rayo.origin - rayoSombra.origin);
		vec3 H = normalize(L + V);
		float hf = pow(H * normal, obj->getMat().specular);
		return obj->getMat().diffuse * ka + obj->getMat().diffuse * kd * fctr + vec3(1,1,1)*hf*obj->getMat().ks;
	}
};


vec3 traza_RR(ray rayo, int alt, Light* light) {
	vec3 norm, hitPoint;
	vec3 res;
	Primitive* inter = intersect(rayo, norm, hitPoint);
	if (inter != NULL) {
		return sombra_RR(inter,rayo,hitPoint,norm,alt,light);
	}
	else return vec3(20, 20, 20);
	/*if (norm.x > 0) {
		res.x = 127 * norm.x;
	} else {
		res.x = 255 * abs(norm.x);
	}
	if (norm.y > 0) {
		res.y = 127 * norm.y;
	}
	else {
		res.y = 255 * abs(norm.y);
	}
	if (norm.z > 0) {
		res.z = 127 * norm.z;
	}
	else {
		res.z = 255 * abs(norm.z);
	}*/
	return res; //Esto sirve para ver las normales
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
	cam.fov = camera->FloatAttribute("fov")*3.1415926535/180.0;
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
		mat.specular = spheres->FloatAttribute("spec");
		mat.IOR = spheres->FloatAttribute("IOR");
		mat.ks = spheres->FloatAttribute("ks");
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
		mat.specular = planes->FloatAttribute("spec");
		mat.IOR = planes->FloatAttribute("IOR");
		mat.ks = planes->FloatAttribute("ks");
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
		mat.specular = cyls->FloatAttribute("spec");
		mat.IOR = cyls->FloatAttribute("IOR");
		mat.ks = cyls->FloatAttribute("ks");
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
		mat.specular = tris->FloatAttribute("spec");
		mat.IOR = tris->FloatAttribute("IOR");
		mat.ks = tris->FloatAttribute("ks");
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

	Light* light = new Light();
	light->position.x = 0.0;
	light->position.y = 1.0;
	light->position.z = 0.10;
	light->intensity.x = 1.5;
	light->intensity.y = 1.5;
	light->intensity.z = 1.5;
	light->color.x = 1.0;
	light->color.y = 1.0;
	light->color.z = 1.0;


	for (int j = 0; j < cam.resH; j++) {
		for (int i = 0; i < cam.resW; i++) {
			vec3 cam_Z = normalize(cam.origin - cam.look);
			vec3 cam_X = normalize(cross(vec3(0.0f, 0.0f, 1.0f), cam_Z));
			vec3 cam_Y = normalize(cross(cam_Z, cam_X));

			float py = (2.0 * j - cam.resH) / cam.resH;
			float px = (2.0 * i - cam.resW) / cam.resH;
			float pz = -1.0 / tan(cam.fov / 2.0);

			rayo.origin = cam.origin;
			rayo.dir = normalize(cam_X * px + cam_Y * py + cam_Z * pz);

			pixel = traza_RR(rayo, 1, light);
			color.rgbRed = pixel.x;
			color.rgbGreen = pixel.y;
			color.rgbBlue = pixel.z;
			FreeImage_SetPixelColor(bitmap, i,j , &color);
		}
	}
	FreeImage_Save(FIF_PNG, bitmap, "test.png", 0);
	FreeImage_DeInitialise();
	return 0;
}
