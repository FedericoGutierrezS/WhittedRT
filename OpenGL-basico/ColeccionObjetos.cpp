#include "ColeccionObjetos.h"
#include <iostream>

ColObjetos* ColObjetos::instancia = NULL;

ColObjetos::ColObjetos() {
	instancia = NULL;
	esferas = NULL;
	planos = NULL;
	triangulos = NULL;
	luces = NULL;
}

ColObjetos* ColObjetos::getInstance() {
	if (instancia == NULL) {
		instancia = new ColObjetos();
		return instancia;
	}
	else return instancia;
}

void ColObjetos::inicializarCol(int cantEsfera, int cantPlano, int cantCilindro, int cantTriangulo, int cantLuz) {
	this->esferas = new Esfera * [cantEsfera];
	this->planos = new Plano * [cantPlano];
	this->cilindros = new Cilindro * [cantCilindro];
	this->triangulos = new Triangulo * [cantTriangulo];
	this->luces = new Light * [cantLuz];
	cantEsferas = 0;
	cantPlanos = 0;
	cantCilindros = 0;
	cantTriangulos = 0;
	cantLuces = 0;
	cantEsferasTot = cantEsfera;
	cantPlanosTot = cantPlano;
	cantCilindrosTot = cantCilindro;
	cantTriangulosTot = cantTriangulo;
	cantLucesTot = cantLuz;
}

int ColObjetos::getProf() {
	return prof;
}

void ColObjetos::setProf(int palt) {
	prof = palt;
}

Esfera** ColObjetos::getColEsferas() {
	return esferas;
}

Plano** ColObjetos::getColPlanos() {
	return planos;
}

Cilindro** ColObjetos::getColCilindros() {
	return cilindros;
}

Triangulo** ColObjetos::getColTriangulos() {
	return triangulos;
}

Light** ColObjetos::getColLuces() {
	return luces;
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
int ColObjetos::getCantLuces() {
	return cantLuces;
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
int ColObjetos::getCantLucesTot() {
	return cantLucesTot;
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

void ColObjetos::agregarCilindro(Cilindro* obj) {
	cilindros[cantCilindros] = obj;
	cantCilindros++;
}

void ColObjetos::agregarLuz(Light* obj) {
	luces[cantLuces] = obj;
	cantLuces++;
}