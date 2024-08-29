#pragma once

#include "Obstaculo.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "ElementosGraficos/ObjetoEstatico.hpp"

const int LIXO_HEIGHT = 26;

class Lixo : public Obstaculo
{
private:
  float fator_de_impedimento;

public:
  Lixo(int px, int py);
  ~Lixo();
  void executar();
  void lidarColisao(sf::Vector2f intersecao, Entidade *other);
  Json::Value gravar();
};