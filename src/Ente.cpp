#include "Ente.hpp"

int Ente::cont(0);
Gerenciador_Grafico *Ente::pGG(NULL);

void Ente::setGerenciadorGrafico(Gerenciador_Grafico *pGerenciador)
{
  pGG = pGerenciador;
}

Ente::Ente() : id(cont++), textura(), sprite()
{
  sprite.setPosition(60, 60);
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

sf::Sprite Ente::getSprite()
{
  return sprite;
}

void Ente::carregaTextura(string textura_path)
{
  if (!textura.loadFromFile(textura_path))
  {
    cout << "Erro carregando textura: " << textura_path << endl;
  }
}
