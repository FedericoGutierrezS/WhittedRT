#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>

using namespace std;

int main(int argc, char *argv[]) {
	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);

	glMatrixMode(GL_PROJECTION);

	glClearColor(0, 0, 0, 1);

	gluPerspective(45, 640 / 480.f, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	bool fin = false;
	bool rotate = false;

	SDL_Event evento;

	float x, y, z;

	x = 0;
	y = 0;
	z = 5;
	float degrees = 0;
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	FreeImage_Initialise();
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

	//do {
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glLoadIdentity();
	//	gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);

	//	if (rotate) {
	//		degrees = degrees + 0.1f;
	//	}
	//	glRotatef(degrees, 0.0, 1.0, 0.0);

	//	glBegin(GL_TRIANGLES);
	//	glColor3f(1.0, 1.0, 1.0);
	//	glVertex3f(1., -1., 0.);
	//	glColor3f(1.0, 0.0, 0.0);
	//	glVertex3f(-1., -1., 0.);
	//	glColor3f(0.0, 0.0, 1.0);
	//	glVertex3f(0., 1., 0.);
	//	glEnd();
	//	//FIN DIBUJAR OBJETOS

	//	//MANEJO DE EVENTOS
	//	while (SDL_PollEvent(&evento)){
	//		switch (evento.type) {
	//		case SDL_MOUSEBUTTONDOWN:
	//			rotate = true;
	//			cout << "ROT\n";
	//			break;
	//		case SDL_MOUSEBUTTONUP:
	//			rotate = false;
	//			break;
	//		case SDL_QUIT:
	//			fin = true;
	//			break;
	//		case SDL_KEYUP:
	//			switch (evento.key.keysym.sym) {
	//			case SDLK_ESCAPE:
	//				fin = true;
	//				break;
	//			case SDLK_RIGHT:
	//				break;
	//			}
	//		}
	//	}
	//	//FIN MANEJO DE EVENTOS
	//	SDL_GL_SwapWindow(win);
	//} while (!fin);
	////FIN LOOP PRINCIPAL
	// LIMPIEZA
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	FreeImage_DeInitialise();
	return 0;
}
