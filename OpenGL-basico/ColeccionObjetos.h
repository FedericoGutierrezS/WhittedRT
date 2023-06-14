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
	static ColObjetos* instancia;
	int cantEsferas;
	int cantPlanos;
	int cantCilindros;
	int cantTriangulos;
	int cantEsferasTot;
	int cantPlanosTot;
	int cantCilindrosTot;
	int cantTriangulosTot;
	ColObjetos();
public:
	static ColObjetos* getInstance();
	Esfera** getColEsferas();
	Plano** getColPlanos();
	Triangulo** getColTriangulos();
	Cilindro** getColCilindros();
	void inicializarCol(int, int, int, int);
	int getCantEsferas();
	int getCantPlanos();
	int getCantCilindros();
	int getCantTriangulos();
	int getCantEsferasTot();
	int getCantPlanosTot();
	int getCantCilindrosTot();
	int getCantTriangulosTot();
	void agregarEsfera(Esfera*);
	void agregarPlano(Plano*);
	void agregarTriangulo(Triangulo*);
	void agregarCilindro(Cilindro*);
};