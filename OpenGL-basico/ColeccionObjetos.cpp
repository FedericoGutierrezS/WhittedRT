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
	cantEsferas = 0;
	cantCilindros = 0;
	cantPlanos = 0;
	cantMallas = 0;
}

Esfera** ColObjetos::getColEsferas() {
	return esferas;
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