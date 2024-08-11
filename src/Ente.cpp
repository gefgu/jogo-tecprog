#include "Ente.hpp"
#include <iostream>

using namespace std;

int Ente::cont(0);
Gerenciador_Grafico *Ente::pGG(NULL);

void Ente::setGerenciadorGrafico(Gerenciador_Grafico *pGerenciador)
{
  pGG = pGerenciador;
}

Ente::Ente() : id(cont++)
{
  // sprite.setPosition(20, 20);
}

Ente::~Ente() {}

void Ente::desenhar()
{
  if (pGG)
  {
    pGG->desenharEnte(this);
  }
  else
  {
    cout << "Gerenciador Gráfico não encontrado em Ente" << endl;
  }
}

// sf::Sprite Ente::getSprite()
// {
//   return sprite;
// }
