#include "Flor.h"

Flor::Flor()
{
	std::vector<Habilidad> a;
	_vida = 0;
	_cuantoPega = 0;
	a.push_back(Generar);
	_habilidades = a;
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

std::string Flor::nombreHabilidad(Habilidad h)
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

void Flor::Mostrar(std::ostream& os)
{
	os << "Instancia de Flor\n";
	os << "=================\n";
	os << "Vida: " << _vida << "\n";
	os << "Habilidades: ";

	int i = 0;
	while(i < _habilidades.size())
	{
		if (i == _habilidades.size() - 1)
		{
			os << nombreHabilidad(_habilidades.at(i)) << "\n";
		}
		else
		{
			os << nombreHabilidad(_habilidades.at(i)) << ", ";
		}

		i++;
	}

	os << "Pega: " << _cuantoPega << "\n";

}

void Flor::Guardar(std::ostream& os)
{
	os << "{ F " << _vida << " " << _cuantoPega << " [ ";

	int i = 0;

	while(i < _habilidades.size())
	{
		os << nombreHabilidad(_habilidades.at(i)) << " ";

		i++;
	}

	os << "] }";

}

void Flor::Cargar(std::istream& is)
{
	using namespace std;

	is.ignore(2);
	string tipo = "";
	getline(is, tipo, ' ');

	if (tipo == "F")
	{
		string vida = "";
		getline(is, vida, ' ');
		_vida = atoi(vida.c_str());

		string cuantoPega = "";
		getline(is, cuantoPega, ' ');
		_cuantoPega = atoi(cuantoPega.c_str());

		is.ignore(2);

		vector<Habilidad> habilidades;
		string h = "";
		while(h != "]")
		{
			getline(is, h, ' ');

			if (h == "Generar")
			{
				habilidades.push_back(Generar);
			}

			if (h == "Atacar")
			{
				habilidades.push_back(Atacar);
			}

			if (h == "Explotar")
			{
				habilidades.push_back(Explotar);
			}

		}
		_habilidades = habilidades;
	}

}
