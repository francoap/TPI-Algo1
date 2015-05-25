#pragma once

#include "Flor.h"
#include "Vampiro.h"
#include "Auxiliares.h"

#include <tuple>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

struct FlorEnJuego
{
	FlorEnJuego(Flor f, Posicion p, Vida v)
	{
		flor = f;
		pos = p;
		vida = v;
	}

	Flor flor;
	Posicion pos;
	Vida vida;
};

struct VampiroEnJuego
{
	VampiroEnJuego(Vampiro v, Posicion p, Vida vd)
	{
		vampiro = v;
		pos = p;
		vida = vd;
	}
	Vampiro vampiro;
	Posicion pos;
	Vida vida;
};

struct VampiroEnEspera
{
	Vampiro vampiro;
	int fila;
	int turno;

	VampiroEnEspera(Vampiro v, int f, int t)
	{
		vampiro = v;
		fila = f;
		turno = t;
	}

};

class Nivel
{
public:

	Nivel();
	Nivel(int ancho, int alto, int soles, std::vector<VampiroEnEspera>& spawninglist);
	int anchoN();
	int altoN();
	int turnoN();
	int solesN();
	std::vector<FlorEnJuego>& floresN();
	std::vector<VampiroEnJuego>& vampirosN();
	std::vector<VampiroEnEspera>& spawningN();
	void agregarFlor(Flor f, Posicion p);
	void pasarTurno();
	bool terminado();
	bool obsesivoCompulsivo();
	void comprarSoles(int n);


	void Mostrar(std::ostream& os);
	void Guardar(std::ostream& os);
	void Cargar(std::istream& is);


private:

	int _ancho;
	int _alto;
	int _turno;
	int _soles;

	std::vector<FlorEnJuego> _flores;
	std::vector<VampiroEnJuego> _vampiros;
	std::vector<VampiroEnEspera> _spawning;


	bool sinColisiones(Posicion p);
	bool existeFlorEnPos(Posicion p);
	bool florExploto(Posicion p, std::vector<FlorEnJuego> flores);
	std::vector<VampiroEnEspera> nuevoSpawning();
	std::vector<VampiroEnJuego> vampirosSpawneados(std::vector<VampiroEnJuego> vampiros);
	std::vector<VampiroEnEspera> nuevosVampiros();
	std::vector<VampiroEnJuego> vampirosPosicionados(std::vector<VampiroEnJuego> vampiros, std::vector<FlorEnJuego> flores);
	void moverVampiro(VampiroEnJuego& vampiro, std::vector<FlorEnJuego> flores);
	void avanzar(VampiroEnJuego& vampiro);
	void desviar(VampiroEnJuego& vampiro);
	void retroceder(VampiroEnJuego& vampiro);
	std::vector<VampiroEnJuego> vampirosDaniados(std::vector<VampiroEnJuego> vampiros);
	void daniarVampiro(VampiroEnJuego& vampiro);
	int dmgDaniarVampiro(VampiroEnJuego vampiro);
	bool enMira(VampiroEnJuego v, FlorEnJuego f);
	bool enLineaDeVision(VampiroEnJuego v, FlorEnJuego f);
	std::vector<FlorEnJuego> floresDaniadas(std::vector<FlorEnJuego> flores);
	std::vector<FlorEnJuego> sinFloresMuertas(std::vector<FlorEnJuego> flores);
	void daniarFlor(FlorEnJuego& flor);
	bool florMuerta(FlorEnJuego flor);
	int generarSoles();
	bool florGenera(FlorEnJuego f);
	bool florExplota(FlorEnJuego f);
	int vampirosEnCasa();
	bool posicionMayorInmediata(int a, int b);
	bool posicionMayor(Posicion a, Posicion b);
	bool posicionMenor(Posicion a, Posicion b);
	bool posicionesIguales(Posicion a, Posicion b);
	bool tieneHabilidad(Flor f, Habilidad h);
	int pot(int a, int b);
};