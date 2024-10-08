#ifndef OBSTACULO_FACIL_HPP
#define OBSTACULO_FACIL_HPP

#include "Obstaculo.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "ElementosGraficos/ObjetoEstatico.hpp"

const int ESPINHO_HEIGHT = 16;

class Espinho : public Obstaculo
{
private:
  int dano;

public:
  Espinho(int px, int py);
  ~Espinho();
  void executar();
  void lidarColisao(sf::Vector2f intersecao, Entidade *other);
  Json::Value gravar();
  int getDano();
};

#endif // OBSTACULO_FACIL_HPP