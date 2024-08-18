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
  float overlapX = std::min(origem1.x + size1.width, origem2.x + size2.width) - std::max(origem1.x, origem2.x);
  float overlapY = std::min(origem1.y + size1.height, origem2.y + size2.height) - std::max(origem1.y, origem2.y);

  sf::Vector2f movement(0.0f, 0.0f);

  if (origem1.x < origem2.x)
  {
    movement.x = -overlapX; // Move left
  }
  else
  {
    movement.x = overlapX; // Move right
  }

  if (origem1.y < origem2.y)
  {
    movement.y = -overlapY; // Move up
  }
  else
  {
    movement.y = overlapY; // Move down
  }

  return movement;
}

void Gerenciador_Colisoes::executar()
{
  // colisão entre moveis e estaticos
  int i, j;
  for (i = 0; i < entidades_moveis.size(); i++)
  {
    for (j = 0; j < entidades_estaticas.size(); j++)
    {
      if (verificaColisao(entidades_moveis[i]->getSize(), entidades_estaticas[j]->getSize()))
      {
        sf::Vector2f intersection = getIntersection(entidades_moveis[i]->getCenter(), entidades_moveis[i]->getSize(), entidades_estaticas[j]->getCenter(), entidades_estaticas[j]->getSize());
        entidades_moveis[i]->lidarColisao(intersection, entidades_estaticas[j]);
      }
    }
  }
}