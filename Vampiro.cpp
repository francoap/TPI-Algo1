#include "Vampiro.h"

Vampiro::Vampiro()
{
}

Vampiro::Vampiro(ClaseVampiro cv, Vida v, int cP)
{
	_clase = cv;
	_vida = v;
	_cuantoPega = cP;
}

Vida Vampiro::vidaV()
{
	return _vida;
}

ClaseVampiro Vampiro::claseV()
{
	return _clase;
}

int Vampiro::cuantoPegaV()
{
	return _cuantoPega;
}

void Vampiro::Mostrar(std::ostream& os)
{
}

void Vampiro::Guardar(std::ostream& os)
{
}

void Vampiro::Cargar(std::istream& is)
{
}
