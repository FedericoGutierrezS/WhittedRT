#pragma once
#include "sphere.h"

class ColObjetos {
private:
	Esfera** esferas;
	static ColObjetos* instancia;
	int cantEsferas;
	int cantPlanos;
	int cantCilindros;
	int cantMallas;
	ColObjetos();
public:
	static ColObjetos* getInstance();
	Esfera** getColEsferas();
	void inicializarCol(int, int, int, int);
	int getCantEsferas();
	int getCantPlanos();
	int getCantCilindros();
	int getCantMallas();
	void agregarEsfera(Esfera*);
};