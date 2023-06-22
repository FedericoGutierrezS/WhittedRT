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
#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <regex>
#include <direct.h>

using namespace std;
using namespace tinyxml2;

struct camera {
	vec3 origin;
	vec3 look;
	float resW;
	float resH;
	float fov;
};

float clamp(const float& lo, const float& hi, const float& v)
{
	return std::max(lo, std::min(hi, v));
}


float remap(float n, float lowerO, float upperO, float lowerN, float upperN) {
	return lowerO + (n - lowerN) * (upperO - lowerO) / (upperN - lowerN);
}

Primitive* intersect(ray rayo,vec3 &normalO,vec3 &hitPointO) {
	vec3* norm = new vec3(100, 100, 100);
	vec3* hitPoint = new vec3(100, 100, 100);
	vec3 hitPoint_min(100, 100, 100);
	vec3 norm_min(100, 100, 100);
	Primitive* hit = NULL;
	bool intersect = false;
	bool j = false;
	ColObjetos* col = NULL;
	col = col->getInstance();
	Esfera** e = col->getColEsferas();
	for (int i = 0; i < col->getCantEsferas(); i++) {
		j = e[i]->intersectRay(rayo, norm, hitPoint);
		if (j && norma(*hitPoint - rayo.origin) < norma(hitPoint_min - rayo.origin)) {
			hitPoint_min = *hitPoint;
			norm_min = *norm;
			intersect = true;
			hit = e[i];
		}
	}
	Plano** p = col->getColPlanos();
	for (int i = 0; i < col->getCantPlanos(); i++) {
		j = p[i]->intersectRay(rayo, norm, hitPoint, 10);
		if (j && norma(*hitPoint - rayo.origin) < norma(hitPoint_min - rayo.origin)) {
			hitPoint_min = *hitPoint;
			norm_min = *norm;
			intersect = true;
			hit = p[i];
		}
	}

	Cilindro** c = col->getColCilindros();
	for (int i = 0; i < col->getCantCilindros(); i++) {
		j = c[i]->intersectRay(rayo, norm, hitPoint);
		if (j && norma(*hitPoint - rayo.origin) < norma(hitPoint_min - rayo.origin)) {
			hitPoint_min = *hitPoint;
			norm_min = *norm;
			intersect = true;
			hit = c[i];
		}
	}

	Triangulo** t = col->getColTriangulos();
	for (int i = 0; i < col->getCantTriangulos(); i++) {
		j = t[i]->intersectRay(rayo, norm, hitPoint);
		if (j && norma(*hitPoint - rayo.origin) < norma(hitPoint_min - rayo.origin)) {
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
		normalO = vec3(100, 100, 100);
		hitPointO = vec3(100, 100, 100);
		return NULL;
	}
}
vec3 traza_RR(ray&, int);

vec3 sombra_RR(Primitive* obj, ray& rayo, vec3& hitPoint, vec3& normal, int alt) {
	ray rayoSombra;
	ColObjetos* col = NULL;
	col = col->getInstance();
	vec3 color = obj->getMat().diffuse* obj->getMat().ka;
	Light** l = col->getColLuces();
	rayoSombra.origin = (rayo.dir* normal < 0) ?
		hitPoint + normal * 0.00001 :
		hitPoint - normal * 0.00001;
	Primitive* a = NULL;
	vec3 hitSombra, normalSombra,L;
	float distLuzObj, distObjSombra;
	for (int i = 0; i < col->getCantLuces(); i++) {
		rayoSombra.dir = normalize(l[i]->position - hitPoint);
		a = intersect(rayoSombra, normalSombra, hitSombra);
		L = normalize(l[i]->position - hitPoint);
		float fctr = normal * L;
		distObjSombra = norma(hitSombra - hitPoint);
		distLuzObj = norma(l[i]->position - hitPoint);
		if (a!=NULL&&a!=obj&&(distObjSombra < distLuzObj)) {
			if (a != NULL) color = color - (obj->getMat().diffuse * (obj->getMat().ka * 0.3) * (1 - a->getMat().kt));
			else color = color - (obj->getMat().diffuse * (obj->getMat().ka * 0.3));
			if (color.x < 0) color.x = 0;
			if (color.y < 0) color.y = 0;
			if (color.z < 0) color.z = 0;
		}
		else {
			vec3 V = normalize(rayo.origin - hitPoint);
			vec3 H = normalize(L + V);
			float hf = pow(H * normal, obj->getMat().specular);
			color = color + (obj->getMat().diffuse * obj->getMat().ka) + mult(obj->getMat().diffuse,l[i]->intensity) * obj->getMat().kd * remap(fctr,0,1,-1,1) + l[i]->intensity * hf * obj->getMat().kss;
			if (color.x > 255) color.x = 255;
			if (color.y > 255) color.y = 255;
			if (color.z > 255) color.z = 255;
		}
	}
	/*if (hitPoint.x < 0.1495 && hitPoint.x > 0.1491)
		if (hitPoint.y < 1.0 && hitPoint.y > 0.935)
			if (hitPoint.z < -0.2305 && hitPoint.z > -0.231) {
				cout << hitPoint.x << " " << hitPoint.y << " " << hitPoint.z << "\n";
				cout << rayo.dir.x << " " << rayo.dir.y << " " << rayo.dir.z << "\n";
				cout << rayo.origin.x << " " << rayo.origin.y << " " << rayo.origin.z << "\n";
				cout << normal.x << " " << normal.y << " " << normal.z << "\n";
			}*/
	if (alt < col->getProf()) {
		if (obj->getMat().ks > 0) {
			ray rayo_r;
			vec3 reflectionDirection;
			vec3 reflectionRayOrig;
			reflectionRayOrig = ((reflectionDirection * normal) < 0) ?
				reflectionRayOrig = hitPoint + normal * 0.0001 :
				reflectionRayOrig = hitPoint - normal * 0.0001;
			reflectionDirection = reflect(normalize(hitPoint), normal);
			rayo_r.dir = reflectionDirection;
			rayo_r.origin = reflectionRayOrig;
			color = color + traza_RR(rayo_r, alt + 1)* obj->getMat().ks;
			if (color.x > 255) color.x = 255;
			if (color.y > 255) color.y = 255;
			if (color.z > 255) color.z = 255;
		}
		if (obj->getMat().kt > 0) {
			ray rayo_re;
			vec3 refractionDirection;
			vec3 refractionRayOrig;
			float ci = ((hitPoint*(-1)) * normal);;
			float etai = 1.0003, etat = obj->getMat().IOR;
			vec3 n = normal;
			float nit = etai / etat;
			float si = sin(acos(ci));
			float k = (1 - nit*nit*si*si);
			refractionDirection = normalize(hitPoint*nit + (n*(nit*ci - sqrt(k))));
			refractionRayOrig = ((refractionDirection * normal) < 0) ?
				refractionRayOrig = hitPoint - normal * 0.0001 :
				refractionRayOrig = hitPoint + normal * 0.0001;
			rayo_re.dir = refractionDirection;
			rayo_re.origin = refractionRayOrig;
			if(nit*nit*(1-ci*ci) < 1) color = color + traza_RR(rayo_re, alt + 1) * obj->getMat().kt;
			if (color.x > 255) color.x = 255;
			if (color.y > 255) color.y = 255;
			if (color.z > 255) color.z = 255;
		}
	}
	return color;
};

vec3 traza_RR(ray& rayo, int alt) {
	vec3 norm, hitPoint;
	vec3 res;
	Primitive* inter = intersect(rayo, norm, hitPoint);
	if (inter != NULL) {
		return sombra_RR(inter, rayo, hitPoint, norm, alt);
	}
	else return vec3(0, 0, 0);
};

vec3 traza_RR(ray &rayo, int alt, vec3 &pixelRefl, vec3 &pixelRefr) {
	vec3 norm, hitPoint;
	vec3 res;
	Primitive* inter = intersect(rayo, norm, hitPoint);
	if (inter != NULL) {
		pixelRefl = vec3(255, 255, 255) * inter->getMat().ks;
		pixelRefr = vec3(255, 255, 255) * inter->getMat().kt;
		return sombra_RR(inter, rayo, hitPoint, norm, alt);
	}
	else {
		pixelRefl = vec3(0, 0, 0);
		pixelRefr = vec3(0, 0, 0);
		return vec3(0, 0, 0);
	};
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
	}
	return res;*/ //Esto sirve para ver las normales
};

int main(int argc, char *argv[]) {
	FreeImage_Initialise();
	XMLDocument doc;
	doc.LoadFile("settings.xml");

	ColObjetos* col = NULL;
	col = col->getInstance();

	XMLElement* settings = doc.FirstChildElement();
	col->inicializarCol(settings->FloatAttribute("spheres") , settings->FloatAttribute("planes"), settings->FloatAttribute("cilinders"), settings->FloatAttribute("tris"), settings->FloatAttribute("lights"));
	col->setProf(settings->IntAttribute("prof"));
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
		radius = spheres->FloatAttribute("radius");
		mat.specular = spheres->FloatAttribute("spec");
		mat.IOR = spheres->FloatAttribute("IOR");
		mat.ks = spheres->FloatAttribute("ks");
		mat.kss = spheres->FloatAttribute("kss");
		mat.kd = spheres->FloatAttribute("kd");
		mat.ka = spheres->FloatAttribute("ka");
		mat.kt = spheres->FloatAttribute("kt");
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
		
		mat.specular = planes->FloatAttribute("spec");
		mat.IOR = planes->FloatAttribute("IOR");
		mat.ks = planes->FloatAttribute("ks");
		mat.kss = planes->FloatAttribute("kss");
		mat.kd = planes->FloatAttribute("kd");
		mat.ka = planes->FloatAttribute("ka");
		mat.kt = planes->FloatAttribute("kt");
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
		mat.specular = cyls->FloatAttribute("spec");
		mat.IOR = cyls->FloatAttribute("IOR");
		mat.ks = cyls->FloatAttribute("ks");
		mat.kss = cyls->FloatAttribute("kss");
		mat.kd = cyls->FloatAttribute("kd");
		mat.ka = cyls->FloatAttribute("ka");
		mat.kt = cyls->FloatAttribute("kt");
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
		mat.specular = tris->FloatAttribute("spec");
		mat.IOR = tris->FloatAttribute("IOR");
		mat.ks = tris->FloatAttribute("ks");
		mat.kss = tris->FloatAttribute("kss");
		mat.kd = tris->FloatAttribute("kd");
		mat.ka = tris->FloatAttribute("ka");
		mat.kt = tris->FloatAttribute("kt");
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
	
	XMLElement* lights = settings->FirstChild()->NextSibling()->NextSibling()->NextSibling()->NextSibling()->NextSibling()->FirstChildElement();

	for (int i = 0; i < col->getCantLucesTot(); i++) {
		Light* light = new Light();
		light->position.x = lights->FloatAttribute("posx");
		light->position.y = lights->FloatAttribute("posy");
		light->position.z = lights->FloatAttribute("posz");
		light->intensity.x = lights->FloatAttribute("intx");
		light->intensity.y = lights->FloatAttribute("inty");
		light->intensity.z = lights->FloatAttribute("intz");
		col->agregarLuz(light);
		lights = lights->NextSiblingElement();
	}

	FIBITMAP* bitmap = FreeImage_Allocate(cam.resW, cam.resH, 24);
	FIBITMAP* bitmapRefl = FreeImage_Allocate(cam.resW, cam.resH, 24);
	FIBITMAP* bitmapRefr = FreeImage_Allocate(cam.resW, cam.resH, 24);
	RGBQUAD color;
	vec3 pixel;
	vec3 pixelRefl;
	vec3 pixelRefr;
	ray rayo1;
	ray rayo2;
	ray rayo3;

	for (int j = 0; j < cam.resH; j++) {
		for (int i = 0; i < cam.resW; i++) {
			vec3 cam_Z = normalize(cam.origin - cam.look);
			vec3 cam_X = normalize(cross(vec3(0.0f, 0.0f, 1.0f), cam_Z));
			vec3 cam_Y = normalize(cross(cam_Z, cam_X));

			float py = (2.0*j - cam.resH) / cam.resH;
			float px = (2.0*i - cam.resW) / cam.resH;
			float pz = -1.0 / tan(cam.fov / 2.0);

			rayo1.origin = cam.origin;
			rayo1.dir = normalize(cam_X * px + cam_Y * py + cam_Z * pz);
			rayo2.origin = cam.origin;
			rayo2.dir = normalize(cam_X * px + cam_Y * py + cam_Z * pz + vec3(0.001, 0.001, 0.001));
			rayo3.origin = cam.origin;
			rayo3.dir = normalize(cam_X * px + cam_Y * py + cam_Z * pz - vec3(0.001, 0.001, 0.001));

			pixel = traza_RR(rayo1, 1, pixelRefl, pixelRefr)*0.333333 + traza_RR(rayo2, 1)*0.333333 + traza_RR(rayo3, 1) * 0.333333;
			color.rgbRed = pixel.x;
			color.rgbGreen = pixel.y;
			color.rgbBlue = pixel.z;
			FreeImage_SetPixelColor(bitmap, i,j , &color);
			color.rgbRed = pixelRefl.x;
			color.rgbGreen = pixelRefl.y;
			color.rgbBlue = pixelRefl.z;
			FreeImage_SetPixelColor(bitmapRefl, i, j, &color);
			color.rgbRed = pixelRefr.x;
			color.rgbGreen = pixelRefr.y;
			color.rgbBlue = pixelRefr.z;
			FreeImage_SetPixelColor(bitmapRefr, i, j, &color);
		}
	}
	time_t res = time(NULL);
	char str[26];
	string st;
	ctime_s(str, sizeof str, &res);
	regex r(":");
	st = regex_replace(str, r, "");
	regex nl("\n");
	st = regex_replace(st, nl, "");
	regex j(" ");
	st =regex_replace(st, j, "");
	_mkdir(st.c_str());
	st = st + '/' + st;
	string sn = st + '.' + 'p' + 'n' + 'g';
	string srl = st + 'R' + 'l' + '.' + 'p' + 'n' + 'g';
	string srr = st + 'R' + 'r' + '.' + 'p' + 'n' + 'g';
	FreeImage_Save(FIF_PNG, bitmap, sn.c_str(), 0);
	FreeImage_Save(FIF_PNG, bitmapRefl, srl.c_str(), 0);
	FreeImage_Save(FIF_PNG, bitmapRefr, srr.c_str() , 0);
	FreeImage_DeInitialise();
	return 0;
}
