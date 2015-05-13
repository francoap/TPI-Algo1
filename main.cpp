#include "Juego.h"
#include <iostream>

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
  
  j.agregarNivel(n);
  
  cout << j.muyDeExactas() << endl;

}
