#include "Flor.h"
#include "Vampiro.h"
#include "Types.h"
#include "Auxiliares.h"

std::string nombreHabilidad(Habilidad h)
{
	std::string res = "";

	if (h == Generar)
	{
		res = "Generar";
	}

	if (h == Atacar)
	{
		res = "Atacar";
	}

	if (h == Explotar)
	{
		res = "Explotar";
	}

	return res;
}

std::string nombreClase(ClaseVampiro c)
{
	std::string res = "";

	if (c == Caminante)
	{
		res = "Caminante";
	}

	if (c == Desviado)
	{
		res = "Desviado";
	}

	return res;
}