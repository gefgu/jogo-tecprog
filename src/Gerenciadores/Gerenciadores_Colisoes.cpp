#include "Gerenciadores/Gerenciador_Colisoes.hpp"
#include <math.h>

Gerenciador_Colisoes::Gerenciador_Colisoes() : entidades_estaticas(), entidades_moveis()
{
  entidades_estaticas.clear();
  entidades_moveis.clear();
}

Gerenciador_Colisoes::~Gerenciador_Colisoes()
{
  entidades_estaticas.clear();
  entidades_moveis.clear();
}

void Gerenciador_Colisoes::incluirEntidadeEstatica(Entidade *pE)
{
  entidades_estaticas.push_back(pE);
}

void Gerenciador_Colisoes::incluirEntidadeMovel(Entidade *pE)
{
  entidades_moveis.push_back(pE);
}

bool Gerenciador_Colisoes::verificaColisao(sf::FloatRect size1, sf::FloatRect size2)
{
  return size1.intersects(size2);
}

sf::Vector2f Gerenciador_Colisoes::getIntersection(sf::Vector2f origem1, sf::FloatRect size1, sf::Vector2f origem2, sf::FloatRect size2)
{
  float minX1 = origem1.x - size1.width / 2.f;
  float maxX1 = origem1.x + size1.width / 2.f;
  float minY1 = origem1.y - size1.height / 2.f;
  float maxY1 = origem1.y + size1.height / 2.f;

  float minX2 = origem2.x - size2.width / 2.f;
  float maxX2 = origem2.x + size2.width / 2.f;
  float minY2 = origem2.y - size2.height / 2.f;
  float maxY2 = origem2.y + size2.height / 2.f;

  // Calculate the overlap on the X axis
  float intersectX = std::max(0.f, std::min(maxX1, maxX2) - std::max(minX1, minX2));

  // Calculate the overlap on the Y axis
  float intersectY = std::max(0.f, std::min(maxY1, maxY2) - std::max(minY1, minY2));

  return sf::Vector2f(intersectX, intersectY);
}

void Gerenciador_Colisoes::executar()
{
  // colisão entre moveis e estaticos
  int i, j;
  for (i = 0; i < entidades_moveis.size(); i++)
  {
    if (!entidades_moveis[i]->getAtivo())
      continue;
    for (j = 0; j < entidades_estaticas.size(); j++)
    {
      if (verificaColisao(entidades_moveis[i]->getSize(), entidades_estaticas[j]->getSize()))
      {
        sf::Vector2f intersection = getIntersection(entidades_moveis[i]->getCenter(), entidades_moveis[i]->getSize(), entidades_estaticas[j]->getCenter(), entidades_estaticas[j]->getSize());
        entidades_moveis[i]->lidarColisao(intersection, entidades_estaticas[j]);
        entidades_estaticas[j]->lidarColisao(intersection, entidades_moveis[i]);
      }
    }
  }

  // colisão entre moveis e moveis
  for (i = 0; i < entidades_moveis.size(); i++)
  {
    if (!entidades_moveis[i]->getAtivo())
      continue;
    for (j = i + 1; j < entidades_moveis.size(); j++)
    {
      if (!entidades_moveis[j]->getAtivo())
        continue;
      if (verificaColisao(entidades_moveis[i]->getSize(), entidades_moveis[j]->getSize()))
      {
        sf::Vector2f intersection = getIntersection(entidades_moveis[i]->getCenter(), entidades_moveis[i]->getSize(), entidades_moveis[j]->getCenter(), entidades_moveis[j]->getSize());
        entidades_moveis[i]->lidarColisao(intersection, entidades_moveis[j]);
        entidades_moveis[j]->lidarColisao(intersection, entidades_moveis[i]);
      }
    }
  }
}