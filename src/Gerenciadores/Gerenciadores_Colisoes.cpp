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
  float x_dis = fabs(origem1.x - origem2.x);
  float x_intersect = x_dis - ((size1.width / 2.0) + (size2.width / 2.0));
  float y_dis = fabs(origem1.y - origem2.y);
  float y_intersect = y_dis - ((size1.height / 2.0) + (size2.height / 2.0));
  return sf::Vector2f(x_intersect, y_intersect);
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