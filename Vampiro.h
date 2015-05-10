#pragma once
#include "Types.h"
#include <vector>
#include <iostream>
#include <string>

class Vampiro
{

	Vida _vida;
	int _cuantoPega;
	ClaseVampiro _clase;

public:

	Vampiro();
	Vampiro(ClaseVampiro cv, Vida v, int cP);
	Vida vidaV();
	ClaseVampiro claseV();
	int cuantoPegaV();


	void Mostrar(std::ostream& os);
	void Guardar(std::ostream& os);
	void Cargar(std::istream& is);

};
