#pragma once

#include "Flor.h"
#include "Vampiro.h"
#include "Nivel.h"
#include "Types.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Juego
{

public:

	Juego();
	Juego(std::vector<Flor>& flores, std::vector<Vampiro>& vamps);
	int nivelActual();
	void pasarNivel();
	std::vector<Flor>& floresJ();
	std::vector<Vampiro>& vampirosJ();
	std::vector<Nivel>& nivelesJ();
	void agregarNivel(Nivel& n, int i);
	void jugarNivel(Nivel& n, int i);
	std::vector<Nivel> estosSaleFacil();
	void altoCheat(int n);
	bool muyDeExactas();

	void Mostrar(std::ostream& os);
	void Guardar(std::ostream& os);
	void Cargar(std::istream& is);

private:

	std::vector<Flor> _flores;
	std::vector<Vampiro> _vampiros;
	std::vector<Nivel> _niveles;
	int _nivelActual;


	std::vector<Nivel> maxFlores(std::vector<Nivel> niveles);
	std::vector<Nivel> maxSoles(std::vector<Nivel> niveles);
	std::vector<int> nivelesGanados();

};
