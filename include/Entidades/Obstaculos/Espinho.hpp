#ifndef OBSTACULO_FACIL_HPP
#define OBSTACULO_FACIL_HPP

#include "Obstaculo.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "ElementosGraficos/ObjetoEstatico.hpp"

const int ESPINHO_HEIGHT = 16;

class Espinho : public Obstaculo
{
private:
  ObjetoEstatico visual;

public:
  Espinho(int px, int py);
  ~Espinho();
  void executar();
  void desenhar();
  sf::Vector2f getCenter();
  sf::FloatRect getSize();
  void lidarColisao(sf::Vector2f intersecao, Entidade *other);
};

#endif // OBSTACULO_FACIL_HPP