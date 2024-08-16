#ifndef GERENCIADOR_COLISOES_HPP
#define GERENCIADOR_COLISOES_HPP

#include <vector>
#include "Entidades/Personagens/Inimigo.hpp"
#include "Entidades/Obstaculos/Obstaculo.hpp"

using namespace std;

class Gerenciador_Colisoes
{
private:
  vector<Entidade *> entidades_estaticas;
  vector<Entidade *> entidades_moveis;

  bool verificaColisao(sf::FloatRect size1, sf::FloatRect size2);
  sf::Vector2f getIntersection(sf::Vector2f origem1, sf::FloatRect size1, sf::Vector2f origem2, sf::FloatRect size2);

public:
  Gerenciador_Colisoes();
  ~Gerenciador_Colisoes();
  void incluirEntidadeEstatica(Entidade *pE);
  void incluirEntidadeMovel(Entidade *pE);
  void executar();
};

#endif // GERENCIADOR_COLISOES_HPP