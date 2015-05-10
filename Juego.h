#pragma once
#include <vector>

#include <iostream>
#include <fstream>

#include "Flor.h"
#include "Vampiro.h"
#include "Nivel.h"
#include "Types.h"

class Juego
{
private:

	std::vector<Flor> _flores;
	std::vector<Vampiro> _vampiros;
	std::vector<Nivel> _niveles;
	int _nivelActual;

public:

	Juego();
	Juego(std::vector<Flor>& flores, std::vector<Vampiro>& vamps);
	int nivelActual();
	void pasarNivel();
	std::vector<Flor>& floresJ();
	std::vector<Vampiro>& vampirosJ();
	std::vector<Nivel>& nivelesJ();
	void agregarNivel(Nivel& n);
	std::vector<Nivel> estosSaleFacil();
	void altoCheat(int n);
	bool muyDeExactas();

	void Mostrar(std::ostream& os);
	void Guardar(std::ostream& os);
	void Cargar(std::iostream& is);

};
