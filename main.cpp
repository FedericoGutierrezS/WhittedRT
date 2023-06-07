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
	doc.LoadFile("settings.xml");
	const char* lookX = doc.FirstChildElement("camera")->FirstChildElement("lookX")->GetText();
	cout << lookX;
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
