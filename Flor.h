#pragma once
#include "Types.h"
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

	// Agrego esto como publico porque lo necesitamos en los metodos de entrada/salida de otras clases
	// sino hay que reescribir codigo de forma innecesaria. Espero que no les moleste.
	std::string nombreHabilidad(Habilidad h);


private:

	Vida _vida;
	std::vector<Habilidad> _habilidades;
	int _cuantoPega;
};
