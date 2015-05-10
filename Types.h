#pragma once
#include <tuple>

enum Habilidad {Generar, Atacar, Explotar};
enum ClaseVampiro {Caminante, Desviado};
typedef int Vida;

struct Posicion
{
	Posicion()
	{
		x = 0;
		y = 0;
	}
	Posicion(int ax, int ay)
	{
		x = ax;
		y = ay;
	}

	int x;
	int y;
};

