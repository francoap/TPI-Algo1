#include "Juego.h"

Juego::Juego()
{
	std::vector<Flor> flores;
	_flores = flores;
	std::vector<Vampiro> vampiros;
	_vampiros = vampiros;
	std::vector<Nivel> niveles;
	_niveles = niveles;
}

Juego::Juego(std::vector<Flor>& flores, std::vector<Vampiro>& vamps)
{
    _flores = flores;
    _vampiros = vamps;

    std::vector<Nivel> niveles;
    _niveles = niveles;

}

int Juego::nivelActual()
{
    return _nivelActual;
}

void Juego::pasarNivel()
{

}

std::vector<Flor>& Juego::floresJ()
{
    return _flores;
}

std::vector<Vampiro>& Juego::vampirosJ()
{
    return _vampiros;
}

std::vector<Nivel>& Juego::nivelesJ()
{
    return _niveles;
}

void Juego::agregarNivel(Nivel& n, int i)
{
if(i >= 0 && i <= _niveles.size() /*&& n.floresN().size() == 0 && n.vampirosN().size() == 0 && n.turnoN() == 0*/)
	{
		std::vector<Nivel> nivelesnuevos;
		
		int j=0;
		
		while (j<i)
		{
			nivelesnuevos.push_back(_niveles[j]);
			++j;
		}
		
		nivelesnuevos.push_back(n);
		
		while (j< _niveles.size())
		{
			nivelesnuevos.push_back(_niveles[j]);
			++j;
		}
		
		_niveles=nivelesnuevos;
	}
}

void Juego::jugarNivel(Nivel& n, int i)
{

}

std::vector<Nivel> Juego::estosSaleFacil()
{
    return maxFlores(maxSoles(_niveles));
}

void Juego::altoCheat(int n)
{
    Nivel nivel = _niveles.at(n);

    unsigned long i = 0;

    while(i < nivel.vampirosN().size())
    {
        nivel.vampirosN().at(i).vida = nivel.vampirosN().at(i).vida / 2;
    }
}

bool Juego::muyDeExactas()
{
    bool res = true;

	if (nivelesGanados().size() == 1)
	{
		res = (nivelesGanados()[0] == 1);
	}

	if (nivelesGanados().size() == 2)
	{
		res = (nivelesGanados()[0] == 1 && nivelesGanados()[1] == 2);
	}

	if (nivelesGanados().size() > 2)
	{
	    if (nivelesGanados()[0] != 1 || nivelesGanados()[1] != 2)
	    {
	    	res = false;
	    }
            else
            {
		int i = 0;

		while (i < nivelesGanados().size() && nivelesGanados()[i] >= 3 && res == true)
		{
			if (nivelesGanados()[i] != nivelesGanados()[i-1] + nivelesGanados()[i-2])
			{
				res = false;
			}
			i++;
		}
            }

        }

	return res;
}

void Juego::Mostrar(std::ostream& os)
{
	os << "Instancia de Juego\n";
	os << "=================\n";
	os << "\n";

    // FLORES
	os << "Flores:\n";
	os << "\n";

	int i = 0;

	while(i < _flores.size())
	{
		Flor f = _flores[i];

		f.Mostrar(os);

		i++;
	}
	// FLORES - END

	os << "\n";

	// VAMPIROS
	os << "Vampiros:\n";
	os << "\n";

	i = 0;

	while(i < _vampiros.size())
	{
		Vampiro v = _vampiros[i];

	    v.Mostrar(os);

		i++;
	}
    // VAMPIROS - END

	os << "\n";

	// NIVELES
	os << "Niveles:\n";
	os << "\n";

	i = 0;

	while(i < _niveles.size())
    {
    	Nivel n = _niveles[i];

    	n.Mostrar(os);

    	i++;
    }
	// NIVELES - END
}

void Juego::Guardar(std::ostream& os)
{
	os << "{ J [ ";

    // FLORES
	int i = 0;

	while(i < _flores.size())
	{
		Flor f = _flores[i];

		f.Guardar(os);
        
        os << " ";

		i++;
	}	
	// FLORES - END

	os << "] [ ";
    
    // VAMPIROS
	i = 0;

	while(i < _vampiros.size())
	{
		Vampiro v = _vampiros[i];

		v.Guardar(os);

		os << " ";

		i++;
	}
    // VAMPIROS - END

	os << "] [ ";

    // NIVELES
    i = 0;

    while(i < _niveles.size())
    {
    	Nivel n = _niveles[i];

    	n.Guardar(os);

    	os << " ";

    	i++;
    }
    // NIVELES - END

    os <<"] }";
}

void Juego::Cargar(std::istream& is)
{
	using namespace std;

	is.ignore(2);

	string tipo = "";
	getline(is, tipo, ' ');

	if(tipo == "J")

	// FLORES
	{
		is.ignore(2);
		
		vector<Flor> floresjuego;
		string nocargoflores = "";
		string nohaymasflores = "";
		nocargoflores = is.peek();
		
		if (nocargoflores == "]")

		{
					
			nohaymasflores== "]";
			_flores = floresjuego;
		}
		
		else
		
		{

			while(nohaymasflores != "]")
			{
				Flor f;
			
				string fs = "";
				getline(is,fs,'}');
				istringstream fs2(fs);
				f.Cargar(fs2);

				floresjuego.push_back(f);

				is.ignore(1);
			
				nohaymasflores = is.peek();
			}

			_flores = floresjuego;
		}
	// FLORES - END
	
		is.ignore(4);

	// VAMPIROS		
		vector<Vampiro> vampirosjuego;
		string nocargovampiros = "";
		string nohaymasvampiros = "";
		nocargovampiros = is.peek();
		
		if (nocargovampiros == "]")

		{
					
			nohaymasvampiros== "]";
			_vampiros = vampirosjuego;
		}
		
		else
		
		{

			while(nohaymasvampiros != "]")
			{
				Vampiro v;
			
				string vs = "";
				getline(is,vs,'}');
				istringstream vs2(vs);
				v.Cargar(vs2);

				vampirosjuego.push_back(v);

				is.ignore(1);
			
				nohaymasvampiros = is.peek();
			}

			_vampiros = vampirosjuego;
		}
	// VAMPIROS - END
	
		is.ignore(4);

	// NIVELES
		vector<Nivel> nivelesjuego;
		string nocargoniveles = "";
		string nohaymasniveles = "";
		nocargoniveles = is.peek();
		
		if (nocargoniveles == "]")

		{
					
			nohaymasniveles== "]";
			_niveles = nivelesjuego;
		}
		
		else
		
		{

			while(nohaymasniveles != "]")
			{
				Nivel n;
				getline(is,ns,'}');
				istringstream ns2(ns);
				//n.Cargar(ns2);

				nivelesjuego.push_back(n);

				is.ignore(1);
			
				nohaymasniveles = is.peek();
			}

			_niveles = nivelesjuego;
		}	
	// NIVELES - END

	 }
}



std::vector<Nivel> Juego::maxSoles(std::vector<Nivel> niveles)
{
    std::vector<Nivel> res;

    unsigned long i = 0;

    while(i < niveles.size())
    {
        // bool add define si el nivel va a ser agregado a la lista de maximos
        // para empezar suponemos que el nivel i-esimo es un maximo
        bool add = true;

        unsigned long j = 0;

        while(j < niveles.size())
        {
            // verificamos que sea un maximo comparado con cada nivel j-esimo
            if (niveles.at(i).solesN() < niveles.at(j).solesN())
            {
                // como no es maximo comparado con el nivel j-esimo dado
                // no queremos agregarlo a la lista de maximos
                add = false;
            }

            j++;
        }

        // si el nivel i-esimo es maximo lo agregamos a la lista de maximos
        if(add)
        {
            res.push_back(niveles.at(i));
        }

        i++;
    }
    return res;
}

std::vector<Nivel> Juego::maxFlores(std::vector<Nivel> niveles)
{
    std::vector<Nivel> res;

    unsigned long i = 0;

    while(i < niveles.size())
    {
        unsigned long j = 0;
        bool add = true;

        while(j < niveles.size())
        {
            if (niveles.at(i).floresN().size() < niveles.at(j).floresN().size())
            {
                add = false;
            }

            j++;
        }

        if(add)
        {
            res.push_back(niveles.at(i));
        }

        i++;
    }
    return res;
}

std::vector<int> Juego::nivelesGanados()
{
    std::vector<int> res;

    int i = 0;

    while(i < _niveles.size())
    {
        Nivel n = _niveles.at(i);

        if (n.spawningN().size() == 0 && n.vampirosN().size() == 0)
        {
            res.push_back(i);
        }

        i++;
    }
    return res;
}