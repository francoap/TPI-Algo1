#pragma once
#include "Types.h"
#include <vector>
#include <iostream>
#include <string>

class Flor
{
private:

	Vida _vida;
	std::vector<Habilidad> _habilidades;
	int _cuantoPega;

public:
	Flor();
	Flor(Vida v, int cP, std::vector<Habilidad> hs);
	Vida vidaF();
	int cuantoPegaF();
	std::vector<Habilidad>& habilidadesF();


	void Mostrar(std::ostream& os);
	void Guardar(std::ostream& os);
	void Cargar(std::istream& is);

};
