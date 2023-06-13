#pragma once
#include "sphere.h"
#include "plane.h"

class ColObjetos {
private:
	Esfera** esferas;
	Plano** planos;
	static ColObjetos* instancia;
	int cantEsferas;
	int cantPlanos;
	int cantCilindros;
	int cantMallas;
	ColObjetos();
public:
	static ColObjetos* getInstance();
	Esfera** getColEsferas();
	Plano** getColPlanos();
	void inicializarCol(int, int, int, int);
	int getCantEsferas();
	int getCantPlanos();
	int getCantCilindros();
	int getCantMallas();
	void agregarEsfera(Esfera*);
	void agregarPlano(Plano*);
};