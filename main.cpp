#include "Juego.h"
#include "Auxiliares.h"
#include <iostream>

#include <string>
#include <sstream>

using namespace std;

int main(){
  
	cout << " Trabajo practico Flores vs Vampiros" << endl;

	vector<Habilidad> hab;
	hab.push_back(Atacar);

	vector<Habilidad> hab2;
	hab2.push_back(Atacar);
	hab2.push_back(Generar);

	vector<Habilidad> hab3;
	hab3.push_back(Explotar);
	hab3.push_back(Generar);

	Flor f(25,0,hab3);

	cout << f.vidaF() << ' ' << f.cuantoPegaF() << endl;

	Vampiro v(Caminante,50,50);

	cout << v.vidaV() << ' ' << v.cuantoPegaV() << endl;

	vector<VampiroEnEspera> spawn;
	spawn.push_back(VampiroEnEspera(v,2,2));

	Nivel n(5,5,100,spawn);
	cout << n.solesN() << endl;
	n.agregarFlor(f, Posicion(2,2));
	cout << n.solesN() << endl;
	n.pasarTurno();
	cout << n.solesN() << endl;
	cout << n.terminado() << ' ' << n.obsesivoCompulsivo() << endl;



	vector<Flor> fs;
	fs.push_back(f);

	vector<Vampiro> vs;
	vs.push_back(v);


	Juego j(fs,vs);
  
	j.agregarNivel(n,0);

  
	cout << j.muyDeExactas() << endl;

	/* PROBANDO ENTRADA/SALIDA */
    /* Esto lo usamos con el proposito de "probar" los metodo mostrar, guardar y cargar de las clases
    cout << "Probando mostrar: " << endl << endl;

    // Mostramos las instancias
    f.Mostrar(cout); cout << endl;
    v.Mostrar(cout); cout << endl;
    n.Mostrar(cout); cout << endl;
    j.Mostrar(cout); cout << endl;

    cout << "Probando guardado y carga: " << endl << endl;

    // Probamos guardado y carga
    cout << "-------------------------------------------------------------" << endl;
    cout << "\"Guardamos\" la flor en el ostream de la consola. Se guardo: ";
    f.Guardar(cout);
    cout << endl  << "Cargamos el siguiente istream: { F 30 10 [ Generar Atacar ] }" << endl;
    istringstream inF("{ F 30 10 [ Generar Atacar ] }");
    f.Cargar(inF);
    cout << "Volvemos a mostrar la instancia luego de la carga: " << endl;
    f.Mostrar(cout);
    cout << "-------------------------------------------------------------" << endl;

    cout << "-------------------------------------------------------------" << endl;
    cout << "\"Guardamos\" el vampiro en el ostream de la consola. Se guardo: ";
    v.Guardar(cout);
    cout << endl  << "Cargamos el siguiente istream: { V Desviado 45 60 }" << endl;
    istringstream inV("{ V Desviado 45 60 }");
    v.Cargar(inV);
    cout << "Volvemos a mostrar la instancia luego de la carga: " << endl;
    v.Mostrar(cout);
    cout << "-------------------------------------------------------------" << endl;

    cout << "-------------------------------------------------------------" << endl;
    cout << "\"Guardamos\" el nivel en el ostream de la consola. Se guardo: ";
    n.Guardar(cout);
    cout << endl  << "Cargamos el siguiente istream: { N 5 5 3 56 [ ( { F 33 6 [ Atacar Explotar ] } ( 2 3 ) 10 ) ( { F 33 0 [ Generar Explotar ] } ( 2 5 ) 33 ) ] [ ( { V Desviado 50 8 } ( 4 5 ) 10 ) ] [ ( { V Caminante 30 7 } 2 5 ) ] } " << endl;
    istringstream inN("{ N 5 5 3 56 [ ( { F 33 6 [ Atacar Explotar ] } ( 2 3 ) 10 ) ( { F 33 0 [ Generar Explotar ] } ( 2 5 ) 33 ) ] [ ( { V Desviado 50 8 } ( 4 5 ) 10 ) ] [ ( { V Caminante 30 7 } 2 5 ) ] }");
    n.Cargar(inN);
    cout << "Volvemos a mostrar la instancia luego de la carga: " << endl;
    n.Mostrar(cout);
    cout << "-------------------------------------------------------------" << endl;

    cout << "-------------------------------------------------------------" << endl;
    cout << "\"Guardamos\" el juego en el ostream de la consola. Se guardo: ";
    j.Guardar(cout);
    cout << endl  << "Cargamos el siguiente istream: { J [ ] [ ] [ { N 5 5 3 56 [ ( { F 33 6 [ Atacar Explotar ] } ( 2 3 ) 10 ) ( { F 33 0 [ Generar Explotar ] } ( 2 5 ) 33 ) ] [ ( { V Desviado 50 8 } ( 4 5 ) 10 ) ] [ ( { V Caminante 30 7 } 2 5 ) ] } ] }" << endl;
    istringstream inJ("{ J [ { F 30 10 [ Generar Atacar ] } { F 30 10 [ Generar Atacar ] } ] [ { V Desviado 45 60 } { V Desviado 45 60 } ] [ { N 5 5 3 56 [ ( { F 33 6 [ Atacar Explotar ] } ( 2 3 ) 10 ) ( { F 33 0 [ Generar Explotar ] } ( 2 5 ) 33 ) ] [ ( { V Desviado 50 8 } ( 4 5 ) 10 ) ] [ ( { V Caminante 30 7 } 2 5 ) ] } { N 5 5 3 56 [ ( { F 33 6 [ Atacar Explotar ] } ( 2 3 ) 10 ) ( { F 33 0 [ Generar Explotar ] } ( 2 5 ) 33 ) ] [ ( { V Desviado 50 8 } ( 4 5 ) 10 ) ] [ ( { V Caminante 30 7 } 2 5 ) ] } ] }");
    //istringstream inJ("{ J [ ] [ ] [ ] }");
    j.Cargar(inJ);
    cout << "Volvemos a mostrar la instancia luego de la carga: " << endl;
    j.Mostrar(cout);
    cout << "-------------------------------------------------------------" << endl;
    */
	/* PROBANDO ENTRADA/SALIDA - END*/

}
