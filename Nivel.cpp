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
		_soles = _soles + 1 + generarSoles();
		_turno = _turno + 1;
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

		// Este if/else nos permite parar el ciclo si la flor ya esta muerta
		if (!florMuerta(flor))
		{
			if (v.pos.x == flor.pos.x && v.pos.y == flor.pos.y)
			{
				// Vemos si la flor tiene la habilidad explotar
				if(florExplota(flor))
				{
					// La flor explota por lo que seteamos su vida en 0 (muerta)
					flor.vida = 0;
				}
				else
				{
					// La flor no explota -> le restamos el danio del vampiro
					flor.vida = flor.vida - v.vampiro.cuantoPegaV();
				}
			}

			i++;
		}
		else
		{
			i = _vampiros.size(); // hago esto para no usar break, luego consultamos si se puede usar break
		}

	}

}

bool Nivel::florMuerta(FlorEnJuego flor)
{
	bool res = false;

	// Decidimos que la flor esta muerta si su vida no es mayor a CERO
	if (!flor.vida > 0)
	{
		res = true;
	}

	return res;
}

int Nivel::generarSoles()
{
	int res = 0;

	unsigned int i = 0;

	// Iteramos por todas las FlorEnJuego
	while(i < _flores.size())
	{
		// Si la flor tiene la habilidad Generar sumamos uno al resultado
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
	return tieneHabilidad(f.flor, Generar);
}

bool Nivel::florExplota(FlorEnJuego f)
{
	return tieneHabilidad(f.flor, Explotar);
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

bool Nivel::tieneHabilidad(Flor f, Habilidad h)
{
	bool res = false;

	unsigned int i = 0;

	while(i < f.habilidadesF().size())
	{
		if (f.habilidadesF().at(i) == h)
		{
			res = true;
			i = f.habilidadesF().size(); // para no usar break, la gracia de esto es parar de iterar cuando ya no es necesario
		}
		else
		{
			i++;
		}
	}

	return res;
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
