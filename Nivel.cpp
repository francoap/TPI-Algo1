#include "Nivel.h"

Nivel::Nivel()
{
}

Nivel::Nivel(int ancho, int alto, int soles, std::vector<VampiroEnEspera>& spawninglist)
{
	_ancho = ancho;
	_alto = alto;
	_soles = soles;
	_spawning = spawninglist;

	std::vector<FlorEnJuego> f;
	std::vector<VampiroEnJuego> v;

	_flores = f;
	_vampiros = v;

	_turno = 0;

}

int Nivel::anchoN()
{
	return _ancho;
}

int Nivel::altoN()
{
	return _alto;
}

int Nivel::turnoN()
{
	return _turno;
}

int Nivel::solesN()
{
	return _soles;
}

std::vector<FlorEnJuego>& Nivel::floresN()
{
	return _flores;
}

std::vector<VampiroEnJuego>& Nivel::vampirosN()
{
	return _vampiros;
}

std::vector<VampiroEnEspera>& Nivel::spawningN()
{
	return _spawning;
}

void Nivel::agregarFlor(Flor f, Posicion p)
{
	FlorEnJuego fToAdd = FlorEnJuego(f, p, f.vidaF());

	_flores.push_back(fToAdd);

}

void Nivel::pasarTurno()
{
	if (!terminado())
	{
		_turno = _turno + 1;
		_soles = _soles + 1 + generarSoles();
		_flores = floresDaniadas(_flores);
		_vampiros = vampirosSpawneados(vampirosPosicionados(vampirosDaniados(_vampiros)));
		// TODO:  mover y spawnear vampiros, alterar spawning
	}
}

std::vector<VampiroEnJuego> Nivel::vampirosSpawneados(std::vector<VampiroEnJuego> vampiros)
{
	std::vector<VampiroEnJuego> res;

	return res;
}

std::vector<VampiroEnJuego> Nivel::vampirosPosicionados(std::vector<VampiroEnJuego> vampiros)
{
	std::vector<VampiroEnJuego> res;

	return res;
}

std::vector<VampiroEnJuego> Nivel::vampirosDaniados(std::vector<VampiroEnJuego> vampiros)
{
	std::vector<VampiroEnJuego> res;

	return res;
}

std::vector<FlorEnJuego> Nivel::floresDaniadas(std::vector<FlorEnJuego> flores)
{
	std::vector<FlorEnJuego> res;

	unsigned int i = 0;

	while (i < flores.size())
	{
		FlorEnJuego f = flores.at(i);

		daniarFlor(f);

		if (!florMuerta(f))
		{
			res.push_back(f);
		}

		i++;
	}

	return res;
}

void Nivel::daniarFlor(FlorEnJuego& flor)
{

	unsigned int i = 0;

	while(i < _vampiros.size())
	{
		VampiroEnJuego v = _vampiros.at(i);

		if (v.pos.y == flor.pos.y)
		{
			flor.vida = flor.vida - v.vampiro.cuantoPegaV();
		}
		else
		{
			if(v.pos.y == flor.pos.y && v.pos.x == flor.pos.x && florExplota(flor))
			{
				flor.vida = -1;
			}
		}
	}

}

bool Nivel::florMuerta(FlorEnJuego flor)
{
	bool res = false;

	if (flor.vida < 0)
	{
		res = true;
	}

	return res;
}

int Nivel::generarSoles()
{
	int res = 0;

	unsigned int i = 0;

	while(i < _flores.size())
	{
		if(florGenera(_flores.at(i)))
		{
			res++;
		}

		i++;
	}

	return res;

}

bool Nivel::florGenera(FlorEnJuego f)
{
	bool res = false;

	unsigned int i = 0;

	while(i < f.flor.habilidadesF().size())
	{
		if (f.flor.habilidadesF().at(i) == Generar)
		{
			res = true;
			break;
		}

		i++;
	}

	return res;
}

bool Nivel::florExplota(FlorEnJuego f)
{
	bool res = false;

	unsigned int i = 0;

	while(i < f.flor.habilidadesF().size())
	{
		if (f.flor.habilidadesF().at(i) == Explotar)
		{
			res = true;
			break;
		}

		i++;
	}

	return res;
}

bool Nivel::terminado()
{
	return (_vampiros.size() == 0 && _spawning.size() == 0) || vampirosEnCasa() > 0;
}

int Nivel::vampirosEnCasa()
{
	int res = 0;

	unsigned int i = 0;

	while(i < _vampiros.size())
	{
		if (_vampiros.at(i).pos.y == 0)
		{
			res++;
		}

		i++;
	}

	return res;

}

bool Nivel::obsesivoCompulsivo()
{

}

void Nivel::Mostrar(std::ostream& os)
{

}

void Nivel::Guardar(std::ostream& os)
{

}

void Nivel::Cargar(std::istream& is)
{

}
