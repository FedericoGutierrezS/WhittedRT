#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "cylinder.h"

class ColObjetos {
private:
	Esfera** esferas;
	Plano** planos;
	Triangulo** triangulos;
	Cilindro** cilindros;
	Light** luces;
	static ColObjetos* instancia;
	int cantEsferas;
	int cantPlanos;
	int cantCilindros;
	int cantTriangulos;
	int cantLuces;
	int cantEsferasTot;
	int cantPlanosTot;
	int cantCilindrosTot;
	int cantTriangulosTot;
	int cantLucesTot;
	ColObjetos();
public:
	static ColObjetos* getInstance();
	Esfera** getColEsferas();
	Plano** getColPlanos();
	Triangulo** getColTriangulos();
	Cilindro** getColCilindros();
	Light** getColLuces();
	void inicializarCol(int, int, int, int, int);
	int getCantEsferas();
	int getCantPlanos();
	int getCantCilindros();
	int getCantTriangulos();
	int getCantLuces();
	int getCantEsferasTot();
	int getCantPlanosTot();
	int getCantCilindrosTot();
	int getCantTriangulosTot();
	int getCantLucesTot();
	void agregarEsfera(Esfera*);
	void agregarPlano(Plano*);
	void agregarTriangulo(Triangulo*);
	void agregarCilindro(Cilindro*);
	void agregarLuz(Light*);
};