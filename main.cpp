#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include "include/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

struct vec3 {
	float x = 0;
	float y = 0;
	float z = 0;
};

struct ray {
	vec3 origin;
	vec3 dir;
};

struct camera {
	vec3 origin;
	vec3 look;
	float resW;
	float resH;
	float fov;
};

struct material {
	vec3 diffuse;
	float specular;
	float reflective;
	float refractive;
	float IOR;
};

struct sphere_p {
	vec3 center;
	float radius;
	material mat;
};

vec3 traza_RR(ray rayo, int alt) {
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
	sphere_p sphere1;
	sphere_p sphere2;

	sphere1.mat.reflective = spheres->FloatAttribute("refl");
	sphere1.mat.refractive = spheres->FloatAttribute("refr");
	sphere1.radius = spheres->FloatAttribute("radius");
	sphere1.mat.specular = spheres->FloatAttribute("specular");
	sphere1.mat.IOR = spheres->FloatAttribute("IOR");
	sphere1.mat.diffuse.x = spheres->FloatAttribute("colorR");
	sphere1.mat.diffuse.y = spheres->FloatAttribute("colorG");
	sphere1.mat.diffuse.z = spheres->FloatAttribute("colorB");
	XMLElement* obPos = spheres->FirstChildElement();
	sphere1.center.x = obPos->FloatAttribute("x");
	sphere1.center.y = obPos->FloatAttribute("y");
	sphere1.center.z = obPos->FloatAttribute("z");

	spheres = spheres->NextSiblingElement();

	sphere2.mat.reflective = spheres->FloatAttribute("refl");
	sphere2.mat.refractive = spheres->FloatAttribute("refr");
	sphere2.radius = spheres->FloatAttribute("radius");
	sphere2.mat.specular = spheres->FloatAttribute("specular");
	sphere2.mat.IOR = spheres->FloatAttribute("IOR");
	sphere2.mat.diffuse.x = spheres->FloatAttribute("colorR");
	sphere2.mat.diffuse.y = spheres->FloatAttribute("colorG");
	sphere2.mat.diffuse.z = spheres->FloatAttribute("colorB");
	obPos = spheres->FirstChildElement();
	sphere2.center.x = obPos->FloatAttribute("x");
	sphere2.center.y = obPos->FloatAttribute("y");
	sphere2.center.z = obPos->FloatAttribute("z");
	
	FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, 24);
	RGBQUAD color;
	vec3 pixel;
	for (int i = 0; i < cam.resH; i++) {
		for (int j = 0; j < cam.resW; j++) {
			ray rayo;
			rayo.origin.x = cam.origin.x;
			rayo.origin.y = cam.origin.y;
			rayo.origin.z = cam.origin.z;
			rayo.dir.x = rayo.origin.x + (2 / cam.resW) * j - 1;
			rayo.dir.y = rayo.origin.y + (2 / cam.resH) * i - 1;
			rayo.dir.z = -1.0 / tan(cam.fov / 2.0);
			float normDirRay = sqrt(rayo.dir.x * rayo.dir.x + rayo.dir.y * rayo.dir.y + rayo.dir.z * rayo.dir.z);
			rayo.dir.x = rayo.dir.x / normDirRay;
			rayo.dir.y = rayo.dir.y / normDirRay;
			rayo.dir.z = rayo.dir.z / normDirRay;

			pixel = traza_RR(rayo, 1);

			color.rgbRed = pixel.x;
			color.rgbGreen = pixel.y;
			color.rgbBlue = pixel.z;
			FreeImage_SetPixelColor(bitmap, j, i, &color);
		}
	}
	FreeImage_Save(FIF_PNG, bitmap, "test.png", 0);
	FreeImage_DeInitialise();
	return 0;
}
