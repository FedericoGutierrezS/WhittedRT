#include "ColeccionObjetos.h"

ColObjetos* ColObjetos::instancia = NULL;

ColObjetos::ColObjetos() {
	instancia = NULL;
}

ColObjetos* ColObjetos::getInstance() {
	if (instancia == NULL) instancia = new ColObjetos();
	else return instancia;
}

void ColObjetos::inicializarCol(int cantEsfera, int cantPlano, int cantCilindro, int cantTriangulo) {
	esferas = new Esfera * [cantEsferas];
	planos = new Plano * [cantPlano];
	triangulos = new Triangulo * [cantTriangulo];
	cantEsferas = 0;
	cantPlanos = 0;
	cantCilindros = 0;
	cantTriangulos = 0;
	cantEsferasTot = cantEsfera;
	cantPlanosTot = cantPlano;
	cantCilindrosTot = cantCilindro;
	cantTriangulosTot = cantTriangulo;
}

Esfera** ColObjetos::getColEsferas() {
	return esferas;
}

Plano** ColObjetos::getColPlanos() {
	return planos;
}

Triangulo** ColObjetos::getColTriangulos() {
	return triangulos;
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
int ColObjetos::getCantTriangulos() {
	return cantTriangulos;
}
int ColObjetos::getCantEsferasTot() {
	return cantEsferasTot;
}
int ColObjetos::getCantPlanosTot() {
	return cantPlanosTot;
}
int ColObjetos::getCantCilindrosTot() {
	return cantCilindrosTot;
}
int ColObjetos::getCantTriangulosTot() {
	return cantTriangulosTot;
}


void ColObjetos::agregarEsfera(Esfera* obj) {
	esferas[cantEsferas] = obj;
	cantEsferas++;
}

void ColObjetos::agregarPlano(Plano* obj) {
	planos[cantPlanos] = obj;
	cantPlanos++;
}

void ColObjetos::agregarTriangulo(Triangulo* obj) {
	triangulos[cantTriangulos] = obj;
	cantTriangulos++;
}