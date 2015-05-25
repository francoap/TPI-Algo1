#pragma once

#include "Types.h"
#include "Auxiliares.h"

#include <vector>
#include <iostream>
#include <string>

class Vampiro
{
public:

	Vampiro();
	Vampiro(ClaseVampiro cv, Vida v, int cP);
	Vida vidaV();
	ClaseVampiro claseV();
	int cuantoPegaV();

	void Mostrar(std::ostream& os);
	void Guardar(std::ostream& os);
	void Cargar(std::istream& is);


private:

	Vida _vida;
	int _cuantoPega;
	ClaseVampiro _clase;
};