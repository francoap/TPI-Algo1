#include "Nivel.h"

Nivel::Nivel()
{
	_ancho = 10;
	_alto = 10;
	_turno = 0;
	_soles = 0;
	std::vector<FlorEnJuego> f;
	_flores = f;
	std::vector<VampiroEnJuego> v;
	_vampiros = v;
	std::vector<VampiroEnEspera> s;
	_spawning = s;
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
	int precio = pot(2, f.habilidadesF().size());
	_soles = _soles - precio;

	FlorEnJuego fToAdd = FlorEnJuego(f, p, f.vidaF());
	_flores.push_back(fToAdd);
}

void Nivel::pasarTurno()
{
	_soles = _soles + 1 + generarSoles();
	_turno = _turno + 1;

	// Procesamos las flores en dos pasos porque necesitamos las flores explotadas
	// para realizar correctamente el movimiento de los vampiros.
	std::vector<FlorEnJuego> fD = floresDaniadas(_flores); // <- Incluye flores muertas.
	_flores = sinFloresMuertas(fD);

	_vampiros = vampirosSpawneados(vampirosPosicionados(vampirosDaniados(_vampiros), fD));

	_spawning = nuevoSpawning();
}

bool Nivel::terminado()
{
	return (_vampiros.size() == 0 && _spawning.size() == 0) || vampirosEnCasa() > 0;
}

bool Nivel::obsesivoCompulsivo()
{
	bool res = true;
	bool stop = false;

	unsigned long i = 0;
	unsigned long j = 0;

	unsigned long cF = _flores.size();

	while(i < cF && !stop)
	{
		while(j < cF && !stop)
		{
			if(j != i && posicionMayorInmediata(i, j))
			{
				if(tieneHabilidad(_flores.at(i).flor, Atacar) != !tieneHabilidad(_flores.at(j).flor, Atacar))
				{
					res = false;
					stop = true;
				}
			}

			j++;
		}

		i++;
	}

	return res;
}

void Nivel::comprarSoles(int n)
{
	_soles = _soles + n;
}

void Nivel::Mostrar(std::ostream& os)
{
	os << "Instancia de Nivel\n";
	os << "=================\n";
	os << "Ancho: " << _ancho << "\n";
	os << "Alto: " << _alto << "\n";
	os << "Turno: " << _turno << "\n";
	os << "Soles: " << _soles << "\n";

	// FLORES
	os << "Flores: [ ";

	int i = 0;

	while(i < _flores.size())
	{
		FlorEnJuego f = _flores.at(i);

		os << "(Flor de " << f.flor.vidaF() << " de vida, que pega " << f.flor.cuantoPegaF() << ", con las siguientes habilidades: [ ";

		int j = 0;

		while(j < f.flor.habilidadesF().size())
		{
			os << nombreHabilidad(f.flor.habilidadesF().at(j)) << " ";

			++j;
		}

		os << "], en la posicion (" << f.pos.x << "," << f.pos.y << ") y con vida " << f.vida << ") ";

		i++;
	}

	os << "]";
	// FLORES - END

	os << "\n";

	// VAMPIROS
	os << "Vampiros: [ ";

	i = 0;

	while(i < _vampiros.size())
	{
		VampiroEnJuego v = _vampiros.at(i);

		os << "(Vampiro de clase " << nombreClase(v.vampiro.claseV()) << ", de vida " << v.vampiro.vidaV() << ", que pega " << v.vampiro.cuantoPegaV();
		os << ", en la posicion (" << v.pos.x << "," << v.pos.y << ") y con vida " << v.vida << ") ";

		i++;
	}

	os << "]";
	// VAMPIROS - END

	os << "\n";

	// SPAWNING
	os << "Spawning: [ ";

	i = 0;

	while(i < _spawning.size())
	{
		VampiroEnEspera v = _spawning.at(i);

		os << "(Vampiro de clase " << nombreClase(v.vampiro.claseV()) << ", de vida " << v.vampiro.vidaV() << ", que pega " << v.vampiro.cuantoPegaV();
		os <<" y va a aparecer en la fila " << v.fila << " del turno " << v.turno << ") ";

		i++;
	}

	os << "]";
	// SPAWNING - END

	os << "\n";
}

void Nivel::Guardar(std::ostream& os)
{
	os << "{ N " << _ancho << " " << _alto << " " << _turno << " " << _soles << " ";

	// FLORES
	os << "[ ";

	int i = 0;

	while(i < _flores.size())
	{
		FlorEnJuego f = _flores.at(i);

		os << "( { F " << f.flor.vidaF() << " " << f.flor.cuantoPegaF() << " [ ";

		int j = 0;

		while(j < f.flor.habilidadesF().size())
		{
			os << nombreHabilidad(f.flor.habilidadesF().at(j)) << " ";

			j++;
		}

		os << "] } ";

		os << "( " << f.pos.x << " " << f.pos.y << " ) " << f.vida << " ) ";

		i++;
	}

	os << "] ";
	// FLORES - END


	// VAMPIROS
	os << "[ ";

	i = 0;

	while(i < _vampiros.size())
	{
		VampiroEnJuego v = _vampiros.at(i);

		os << "( { V " << nombreClase(v.vampiro.claseV()) << " " << v.vampiro.vidaV() << " " << v.vampiro.cuantoPegaV() << " } ";
		os << "( " << v.pos.x << " " << v.pos.y << " ) " << v.vida << " ) ";

		i++;
	}

	os << "] ";
	// VAMPIROS - END


	// SPAWNING
	os << "[ ";

	i = 0;

	while(i < _spawning.size())
	{
		VampiroEnEspera v = _spawning.at(i);

		os << "( { V " << nombreClase(v.vampiro.claseV()) << " " << v.vampiro.vidaV() << " " << v.vampiro.cuantoPegaV() << " } ";
		os << v.fila << " " << v.turno << " ) ";

		i++;
	}

	os << "] }";
	// SPAWNING - END

}

void Nivel::Cargar(std::istream& is)
{
	using namespace std;

	is.ignore(2);

	string tipo = "";
	getline(is, tipo, ' ');

	if(tipo == "N")
	{

		string ancho = "";
		getline(is, ancho, ' ');
		_ancho = atoi(ancho.c_str());

		string alto = "";
		getline(is, alto, ' ');
		_alto = atoi(alto.c_str());

		string turno = "";
		getline(is, turno, ' ');
		_turno = atoi(turno.c_str());

		string soles = "";
		getline(is, soles, ' ');
		_soles = atoi(soles.c_str());

		is.ignore(2);

		// FLORES
		vector<FlorEnJuego> floresNuevas;
		string noCargoFlores = "";
		string noHayMasFlores = "";
		noCargoFlores = is.peek();
		
		if (noCargoFlores == "]")
		{
			noHayMasFlores== "]";
			_flores = floresNuevas;
		}

		else
		{
			while(noHayMasFlores != "]")
			{
				is.ignore(2);

				Flor f;
				Posicion p;
				FlorEnJuego fej = FlorEnJuego(f, p, f.vidaF());

				f.Cargar(is);
				fej.flor = f;

				is.ignore(4);
			
				string posX = "";
				getline(is,posX,' ');
				fej.pos.x = atoi(posX.c_str());
			
				string posY = "";
				getline(is,posY,' ');
				fej.pos.y = atoi(posY.c_str());

				is.ignore(2);

				string vf = "";
				getline(is,vf,' ');
				fej.vida = atoi (vf.c_str());
			
				floresNuevas.push_back(fej);

				is.ignore(2);
			
				noHayMasFlores = is.peek();
			}

			_flores = floresNuevas;
		}	
		// FLORES - END

		is.ignore(4);

		// VAMPIROS
		vector<VampiroEnJuego> vampirosNuevos;
		string noCargoVampiros = "";
		string noHayMasVampiros = "";
		noCargoVampiros = is.peek();
		
		if (noCargoVampiros == "]")
		{
			noHayMasVampiros== "]";
			_vampiros = vampirosNuevos;
		}
		
		else
		{
			while(noHayMasVampiros != "]")
			{
				is.ignore(2);

				Vampiro v;
				Posicion p;
				VampiroEnJuego vej = VampiroEnJuego(v, p, v.vidaV());
			
				v.Cargar(is);
				vej.vampiro = v;

				is.ignore (4);
			
				string posX = "";
				getline(is,posX,' ');
				vej.pos.x = atoi(posX.c_str());
			
				string posY = "";
				getline(is,posY,' ');
				vej.pos.y = atoi(posY.c_str());

				is.ignore(2);

				string vv = "";
				getline(is,vv,' ');
				vej.vida = atoi (vv.c_str());
			
				vampirosNuevos.push_back(vej);

				is.ignore(2);
			
				noHayMasVampiros = is.peek();
			}

			_vampiros = vampirosNuevos;
		}
		
		// VAMPIROS - END
		
		is.ignore(4);

		// SPAWNING
		vector<VampiroEnEspera> spawningNuevo;
		string noCargoSpawning = "";
		string noHayMasSpawning = "";
		noCargoSpawning = is.peek();
		
		if (noCargoSpawning == "]")
		{
			noHayMasSpawning== "]";
			_spawning = spawningNuevo;
		}
		
		else
		{
			while(noHayMasSpawning != "]")
			{
				is.ignore(2);

				Vampiro v;
				int f, t;
				VampiroEnEspera vee = VampiroEnEspera(v, f, t);
			
				v.Cargar(is);
				vee.vampiro = v;

				is.ignore (2);
			
				string fila3 = "";
				getline(is,fila3,' ');
				vee.fila = atoi(fila3.c_str());
			
				string turno3 = "";
				getline(is,turno3,' ');
				vee.turno = atoi(turno3.c_str());
			
				spawningNuevo.push_back(vee);

				is.ignore(2);
			
				noHayMasSpawning = is.peek();
			}
		}

		_spawning = spawningNuevo;
		// SPAWNING - END
	}

}

bool Nivel::sinColisiones(Posicion p)
{
	bool res = true;

	unsigned long i = 0;

	unsigned long cF = _flores.size();

	while(i < cF)
	{
		FlorEnJuego f = _flores.at(i);

		if (posicionesIguales(f.pos, p))
		{
			res = false;
			i = cF;
		}

		i++;
	}

	return res;
}

bool Nivel::existeFlorEnPos(Posicion p)
{
	bool res = false;

	unsigned long i = 0;

	while(i < _flores.size())
	{
		FlorEnJuego f = _flores.at(i);

		if(posicionesIguales(f.pos, p))
		{
			res = true;
			i = _flores.size();
		}
		else
		{
			i++;
		}
	}

	return res;
}

bool Nivel::florExploto(Posicion p, std::vector<FlorEnJuego> flores)
{
	bool res = false;

	unsigned long i = 0;

	while(i < _flores.size())
	{
		FlorEnJuego f = _flores.at(i);

		if(f.vida <= 0 && florExplota(f))
		{
			res = true;
			i = _flores.size();
		}
	
		else
		{
			i++;
		}
	}

	return res;
}

std::vector<VampiroEnEspera> Nivel::nuevoSpawning()
{
	std::vector<VampiroEnEspera> res;

	unsigned long i = 0;

	while(i < _spawning.size())
	{
		if(_spawning.at(i).turno > _turno)
		{
			res.push_back(_spawning.at(i));
		}

		i++;
	}

	return res;
}

std::vector<VampiroEnJuego> Nivel::vampirosSpawneados(std::vector<VampiroEnJuego> vampiros)
{
	unsigned long i = 0;

	std::vector<VampiroEnEspera> spawnean = nuevosVampiros();

	while(i < spawnean.size())
	{
		VampiroEnEspera s = spawnean.at(i);
		VampiroEnJuego vJuego(s.vampiro, Posicion(0, s.fila), s.vampiro.vidaV());
		vampiros.push_back(vJuego);
		i++;
	}

	return vampiros;
}

std::vector<VampiroEnEspera> Nivel::nuevosVampiros()
{
	std::vector<VampiroEnEspera> res;

	unsigned long i = 0;

	while(i < _spawning.size())
	{
		VampiroEnEspera v = _spawning.at(i);
		
		if(v.turno == _turno)
		{
			res.push_back(v);
		}
		i++;
	}

	return res;
}

std::vector<VampiroEnJuego> Nivel::vampirosPosicionados(std::vector<VampiroEnJuego> vampiros, std::vector<FlorEnJuego> flores)
{
	unsigned long i = 0;

	while(i < vampiros.size())
	{
		moverVampiro(vampiros.at(i), flores);
		i++;
	}

	return vampiros;
}

void Nivel::moverVampiro(VampiroEnJuego &vampiro, std::vector<FlorEnJuego> flores)
{
	// Aqui verificamos la existencia de una flor en la posicion del vampiro.
	// La busqueda se hace en _flores y en esta instancia _flores deberia tener
	// solamente flores vivas, por eso no pedimos que no este muerta.
	if(!existeFlorEnPos(vampiro.pos))
	{
		// No hay una flor bloqueandonos, asi que intentamos mover el vampiro.
		// Tenemos que ver si aqui habia una flor que exploto
		// y dado el caso el vampiro debe retroceder.
		if (florExploto(vampiro.pos, flores))
		{
			retroceder(vampiro);
		}
		
		else
		{
			// Como no exploto una flor intentamos avanzar.
			avanzar(vampiro);
		}

	}
}

void Nivel::avanzar(VampiroEnJuego &vampiro)
{
	// Avanzamos una columna.
	vampiro.pos.x = vampiro.pos.x - 1;

	// Si el vampiro es desviado se desvia una fila.
	if (vampiro.vampiro.claseV() == Desviado && vampiro.pos.y > 1)
	{
		desviar(vampiro);
	}
}

void Nivel::desviar(VampiroEnJuego &vampiro)
{
	vampiro.pos.y = vampiro.pos.y - 1;
}

void Nivel::retroceder(VampiroEnJuego &vampiro)
{
	if (vampiro.pos.x < _ancho)
	{
		vampiro.pos.x = vampiro.pos.x + 1;
	}
}

std::vector<VampiroEnJuego> Nivel::vampirosDaniados(std::vector<VampiroEnJuego> vampiros)
{
	std::vector<VampiroEnJuego> res;

	unsigned long i = 0;

	while(i < vampiros.size())
	{
		VampiroEnJuego v = vampiros.at(i);
		daniarVampiro(v);
		if (v.vida > 0)
		{
			res.push_back(v);
		}
		
		i++;
	}

	return res;
}

void Nivel::daniarVampiro(VampiroEnJuego& vampiro)
{
	vampiro.vida = vampiro.vida - dmgDaniarVampiro(vampiro);
}

int Nivel::dmgDaniarVampiro(VampiroEnJuego vampiro)
{
	unsigned int dmg = 0;
	unsigned long i = 0;

	while (i < _flores.size())
	{
		if (enMira(vampiro, _flores.at(i)))
		{
			dmg = dmg + _flores.at(i).flor.cuantoPegaF();
		}

		i++;
	}

	return dmg;
}

bool Nivel::enMira(VampiroEnJuego v, FlorEnJuego f)
{
	return (f.pos.y == v.pos.y) && (f.pos.x <= v.pos.x) && enLineaDeVision(v, f);
}

bool Nivel::enLineaDeVision(VampiroEnJuego v, FlorEnJuego f)
{
	bool res = false;

	if (v.pos.y == f.pos.y)
	{
		// Estan en la misma fila -> si no hay un vampiro intermedio devolvemos true.
		res = true;

		unsigned long cV = _vampiros.size();
		unsigned long i = 0;

		while (i < cV)
		{
			if (f.pos.x <= _vampiros.at(i).pos.x < v.pos.x)
			{
				// Encontramos un vampiro intermedio, devolvemos false.
				res = false;
				i = cV; // Dejamos de iterar porque ya tenemos lo que buscabamos.
			}
			else
			{
				i++;
			}

		}

	}

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

		// Mantenemos las flores muertas porque las necesitamos para verificar
		// las flores que explotaron durante la etapa en la que movemos los vampiros.
		// Debemos entonces limpiar la lista de flores luego de procesar la lista de vampiros.
		res.push_back(f);

		i++;
	}

	return res;
}

std::vector<FlorEnJuego> Nivel::sinFloresMuertas(std::vector<FlorEnJuego> flores)
{
	std::vector<FlorEnJuego> res;

	unsigned int i = 0;

	while (i < flores.size())
	{
		FlorEnJuego cF = flores.at(i);

		if (!florMuerta(cF))
		{
			res.push_back(cF);
		}

		i++;
	}

	return res;
}

void Nivel::daniarFlor(FlorEnJuego& flor)
{
	unsigned long i = 0;

	while(i < _vampiros.size())
	{
		VampiroEnJuego v = _vampiros.at(i);

		// Este if/else nos permite parar el ciclo si la flor ya esta muerta.
		if (!florMuerta(flor))
		{
			if (posicionesIguales(v.pos, flor.pos))
			{
				// Vemos si la flor tiene la habilidad explotar.
				if(florExplota(flor))
				{
					// La flor explota por lo que seteamos su vida en 0 (muerta).
					flor.vida = 0;
				}
				
				else
				{
					// La flor no explota -> le restamos el danio del vampiro.
					flor.vida = flor.vida - v.vampiro.cuantoPegaV();
				}
			}

			i++;
		}
		
		else
		{
			i = _vampiros.size();
		}
	}
}

bool Nivel::florMuerta(FlorEnJuego flor)
{
	bool res = false;

	// Decidimos que la flor esta muerta si su vida no es mayor a cero.
	if (!(flor.vida > 0))
	{
		res = true;
	}

	return res;
}

int Nivel::generarSoles()
{
	unsigned int res = 0;

	unsigned int i = 0;

	// Iteramos por todas las FlorEnJuego.
	while(i < _flores.size())
	{
		// Si la flor tiene la habilidad Generar sumamos uno al resultado.
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

int Nivel::vampirosEnCasa()
{
	unsigned int res = 0;

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

bool Nivel::posicionMayorInmediata(int a, int b)
{
	bool r = true;
	bool stop = false;

	unsigned long i = 0;

	while(i < _flores.size() && !stop)
	{
		if(i != a && i != b && (posicionMayor(_flores.at(i).pos, _flores.at(b).pos) && posicionMenor(_flores.at(i).pos, _flores.at(a).pos)))
		{
			r = false;
			stop = true;
		}

		i++;
	}

	return posicionMayor(_flores.at(a).pos, _flores.at(b).pos) && r;
}

bool Nivel::posicionMayor(Posicion a, Posicion b)
{
	return a.y > b.y || (a.y == b.y && a.x > b.x);
}

bool Nivel::posicionMenor(Posicion a, Posicion b)
{
	return !posicionesIguales(a, b) && !posicionMayor(a, b);
}

bool Nivel::posicionesIguales(Posicion a, Posicion b)
{
	return a.x == b.x && a.y == b.y;
}

bool Nivel::tieneHabilidad(Flor f, Habilidad h)
{
	bool res = false;
	bool stop = false;

	unsigned long i = 0;

	while(i < f.habilidadesF().size() && !stop)
	{
		if (f.habilidadesF().at(i) == h)
		{
			res = true;
			stop = true;
		}

		i++;
	}

	return res;
}
// elevar a potencia > 0
int Nivel::pot(int a, int b)
{
	int i = 1;
	int res = a;

	while(i < b)
	{
		res = res*a;
		i++;
	}

	return res;
}