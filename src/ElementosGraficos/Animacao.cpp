#include <cstring>
#include "ElementosGraficos/Animacao.hpp"

Animacao::Animacao() : trilhas(), trilhaAtual(NULL)
{
  trilhas.clear();
}

Animacao::~Animacao()
{
  map<const char *, TrilhaAnimacao *>::iterator it;
  for (it = trilhas.begin(); it != trilhas.end(); it++)
  {
    delete (it->second);
  }
}

void Animacao::addTrilha(const char *key, TrilhaAnimacao *trilha)
{
  map<const char *, TrilhaAnimacao *>::iterator it;
  for (it = trilhas.begin(); it != trilhas.end(); it++)
  {
    if (!strcmp(it->first, key))
      return;
  }
  trilhas.insert(pair<const char *, TrilhaAnimacao *>(key, trilha));
}

void Animacao::setTrilha(const char *key)
{
  map<const char *, TrilhaAnimacao *>::iterator it;
  for (it = trilhas.begin(); it != trilhas.end(); it++)
  {
    if (!strcmp(it->first, key))
    {
      trilhaAtual = it->second;
      trilhaAtual->reset();
      return;
    }
  }

  cout << "Trilha Not Found" << endl;
}

void Animacao::update()
{
  if (trilhaAtual)
  {
    trilhaAtual->update();
  }
}

void Animacao::setPosition(int px, int py)
{
  if (trilhaAtual)
  {
    trilhaAtual->setPosition(px, py);
  }
}

void Animacao::setScale(float sx, float sy)
{
  if (trilhaAtual)
  {
    trilhaAtual->setScale(sx, sy);
  }
}

void Animacao::desenhar()
{
  if (trilhaAtual)
  {
    trilhaAtual->desenhar();
  }
}

sf::Vector2f Animacao::getCenter()
{
  return trilhaAtual->getCenter();
}

sf::FloatRect Animacao::getSize()
{
  return trilhaAtual->getSize();
}