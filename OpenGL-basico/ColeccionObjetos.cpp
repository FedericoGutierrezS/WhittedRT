#include "ColeccionObjetos.h"

ColObjetos* ColObjetos::instancia = NULL;

ColObjetos::ColObjetos() {
	instancia = NULL;
}

ColObjetos* ColObjetos::getInstance() {
	if (instancia == NULL) instancia = new ColObjetos();
	else return instancia;
}

void ColObjetos::inicializarCol(int cantEsfera, int cantCilindro, int cantPlano, int cantMalla) {
	esferas = new Esfera * [cantEsferas];
	planos = new Plano * [cantPlano];
	cantEsferas = 0;
	cantCilindros = 0;
	cantPlanos = 0;
	cantMallas = 0;
}

Esfera** ColObjetos::getColEsferas() {
	return esferas;
}

Plano** ColObjetos::getColPlanos() {
	return planos;
}

int ColObjetos::getCantEsferas() {
	return cantEsferas;
}
int ColObjetos::getCantPlanos() {
	return cantPlanos;
}
int ColObjetos::getCantCilindros() {
	return cantCilindros;
}
int ColObjetos::getCantMallas() {
	return cantMallas;
}

void ColObjetos::agregarEsfera(Esfera* obj) {
	esferas[cantEsferas] = obj;
	cantEsferas++;
}

void ColObjetos::agregarPlano(Plano* obj) {
	planos[cantPlanos] = obj;
	cantPlanos++;
}