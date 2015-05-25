#pragma once

#include "Types.h"
#include "Auxiliares.h"

#include <vector>
#include <iostream>
#include <string>

class Flor
{
public:

	Flor();
	Flor(Vida v, int cP, std::vector<Habilidad> hs);
	Vida vidaF();
	int cuantoPegaF();
	std::vector<Habilidad>& habilidadesF();

	void Mostrar(std::ostream& os);
	void Guardar(std::ostream& os);
	void Cargar(std::istream& is);


private:

	Vida _vida;
	std::vector<Habilidad> _habilidades;
	int _cuantoPega;
};