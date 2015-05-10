#include "Flor.h"


Flor::Flor(){

}

Flor::Flor(Vida v, int cP, std::vector<Habilidad> hs)
{
	_vida = v;
	_cuantoPega = cP;
	_habilidades = hs;
}

Vida Flor::vidaF()
{
	return _vida;
}

int Flor::cuantoPegaF()
{
	return _cuantoPega;
}

std::vector<Habilidad>& Flor::habilidadesF()
{
	return _habilidades;
}

void Flor::Mostrar(std::ostream& os)
{
}

void Flor::Guardar(std::ostream& os)
{
}

void Flor::Cargar(std::istream& is)
{
}
