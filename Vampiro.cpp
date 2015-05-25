#include "Vampiro.h"

Vampiro::Vampiro()
{
    _vida = 0;
    _cuantoPega = 0;
    _clase = Caminante;
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
	os << "Instancia de Vampiro\n";
	os << "=================\n";
	os << "Clase: " << nombreClase(_clase) << "\n";
	os << "Vida: " << _vida << "\n";
	os << "Pega: " << _cuantoPega << "\n";
}

void Vampiro::Guardar(std::ostream& os)
{
	os << "{ V " << nombreClase(_clase) << " " << _vida << " " << _cuantoPega << " }";
}

void Vampiro::Cargar(std::istream& is)
{
	using namespace std;

	is.ignore(2);

	string tipo = "";
	getline(is, tipo, ' ');

	if(tipo == "V")
	{
		string clase = "";
		getline(is, clase, ' ');
		if (clase == "Caminante")
		{
			_clase = Caminante;
		}
		if (clase == "Desviado")
		{
			_clase = Desviado;
		}

		string vida = "";
		getline(is, vida, ' ');
		_vida = atoi(vida.c_str());

		string cuantoPega = "";
		getline(is, cuantoPega, ' ');
		_cuantoPega = atoi(cuantoPega.c_str());
	}

}