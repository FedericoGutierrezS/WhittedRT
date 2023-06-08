#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include "include/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

int main(int argc, char *argv[]) {
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	FreeImage_Initialise();
	XMLDocument doc;
	doc.LoadFile("../settings.xml");
	XMLElement* settings = doc.FirstChildElement();
	XMLElement* camera = settings->FirstChildElement()->FirstChildElement();
	float cameraLookX = camera->FloatAttribute("x");
	float cameraLookY = camera->FloatAttribute("y");
	float cameraLookZ = camera->FloatAttribute("z");
	cout << cameraLookX << " ";
	cout << cameraLookY << " ";
	cout << cameraLookZ << " ";
	cout << "\n";
	camera = camera->NextSiblingElement();
	float cameraPosX = camera->FloatAttribute("x");
	float cameraPosY = camera->FloatAttribute("y");
	float cameraPosZ = camera->FloatAttribute("z");
	cout << cameraPosX << " ";
	cout << cameraPosY << " ";
	cout << cameraPosZ << " ";
	cout << "\n";
	XMLElement* spheres = settings->FirstChild()->NextSibling()->FirstChildElement();
	float refl1 = spheres->FloatAttribute("refl");
	float trans1 = spheres->FloatAttribute("trans");
	XMLElement* obPos = spheres->FirstChildElement();
	float posX1 = obPos->FloatAttribute("x");
	float posY1 = obPos->FloatAttribute("y");
	float posZ1 = obPos->FloatAttribute("z");
	cout << refl1 << " " << trans1 << " " << posX1 << " " << posY1 << " " << posZ1;
	cout << "\n";
	spheres = spheres->NextSiblingElement();
	float refl2 = spheres->FloatAttribute("refl");
	float trans2 = spheres->FloatAttribute("trans");
	obPos = spheres->FirstChildElement();
	float posX2 = obPos->FloatAttribute("x");
	float posY2 = obPos->FloatAttribute("y");
	float posZ2 = obPos->FloatAttribute("z");
	cout << refl1 << " " << trans2 << " " << posX2 << " " << posY2 << " " << posZ2;
	
	FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, 24);
	RGBQUAD color;
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			color.rgbRed = 255;
			color.rgbBlue = 0;
			color.rgbGreen = 0;
			FreeImage_SetPixelColor(bitmap, i, j, &color);
		}
	}
	FreeImage_Save(FIF_PNG, bitmap, "test.png", 0);
	FreeImage_DeInitialise();
	return 0;
}
